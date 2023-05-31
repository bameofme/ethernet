#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 12345

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize;
    char buffer[1024];

    // Tạo socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(1);
    }

    // Thiết lập thông tin server
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Gán địa chỉ cho socket
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in bind");
        exit(1);
    }

    // Lắng nghe kết nối từ client
    if (listen(sockfd, 10) < 0) {
        perror("Error in listen");
        exit(1);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        // Chấp nhận kết nối mới
        addrSize = sizeof(clientAddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &addrSize);
        if (newsockfd < 0) {
            perror("Error in accept");
            exit(1);
        }

        // Nhận message từ client
        recv(newsockfd, buffer, sizeof(buffer), 0);
        printf("Received message: %s\n", buffer);
        // Đóng kết nối
        close(newsockfd);
    }

    // Đóng socket
    close(sockfd);

    return 0;
}