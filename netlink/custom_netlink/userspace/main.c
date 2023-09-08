#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define NETLINK_USER 31

int main() {
    struct sockaddr_nl src_addr, dest_addr;
    struct nlmsghdr *nlh = NULL;
    int sock_fd;
    char *hello = "Hello from user!";
    char buffer[1024];

    // Create socket
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid(); // Self pid

    bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0; // For Linux Kernel
    dest_addr.nl_groups = 0; // Unicast

    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(strlen(hello)));
    memset(nlh, 0, NLMSG_SPACE(strlen(hello)));
    nlh->nlmsg_len = NLMSG_SPACE(strlen(hello));
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    strcpy(NLMSG_DATA(nlh), hello);

    send(sock_fd, nlh, nlh->nlmsg_len, 0);
    printf("Message sent to kernel: %s\n", hello);

    memset(nlh, 0, NLMSG_SPACE(strlen(hello)));
    recv(sock_fd, nlh, NLMSG_SPACE(strlen(hello)), 0);
    printf("Message received from kernel: %s\n", (char *)NLMSG_DATA(nlh));

    close(sock_fd);

    return 0;
}
