#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#define MAX_PAYLOAD 4096

// Function to parse and print the link information
void parse_and_print_link_info(struct nlmsghdr *nlh) {
    struct ifinfomsg *ifinfo;
    struct rtattr *attr;
    int len;

    ifinfo = (struct ifinfomsg *)NLMSG_DATA(nlh);
    len = NLMSG_PAYLOAD(nlh, sizeof(struct ifinfomsg));

    for (attr = IFLA_RTA(ifinfo); RTA_OK(attr, len); attr = RTA_NEXT(attr, len)) {
        if (attr->rta_type == IFLA_IFNAME) {
            printf("Interface Name: %s\n", (char *)RTA_DATA(attr));
        }
    }
    printf("\n");
}

int main() {
    int sockfd;
    struct sockaddr_nl src_addr, dest_addr;
    struct nlmsghdr *nlh;
    char buffer[MAX_PAYLOAD];

    // Create a Netlink socket
    sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the source address
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid(); // PID of the sending process

    // Bind the socket to the source address
    if (bind(sockfd, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Prepare the destination address
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0; // Kernel PID
    dest_addr.nl_groups = 0; // Not in a multicast group

    // Initialize the Netlink message header
    nlh = (struct nlmsghdr *)buffer;
    nlh->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtgenmsg));
    nlh->nlmsg_type = RTM_GETLINK; // Request to get link info
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    nlh->nlmsg_seq = 1;

    // Initialize the rtgenmsg structure
    struct rtgenmsg *rtmsg = (struct rtgenmsg *)NLMSG_DATA(nlh);
    rtmsg->rtgen_family = AF_UNSPEC;

    // Send the Netlink request to the kernel
    if (sendto(sockfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive and process the Netlink response
    ssize_t len;
    while ((len = recv(sockfd, buffer, MAX_PAYLOAD, 0)) > 0) {
        struct nlmsghdr *nlmsg;
        for (nlmsg = (struct nlmsghdr *)buffer; NLMSG_OK(nlmsg, len); nlmsg = NLMSG_NEXT(nlmsg, len)) {
            parse_and_print_link_info(nlmsg);
        }
    }

    // Close the socket
    close(sockfd);

    return 0;
}
