#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[1024];
    char message[1024];

    // Create UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    printf("UDP Client ready! Type messages:\n");

    while(1) {
        printf("You: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;

        // Send message to server
        sendto(sock_fd, message, strlen(message), 0,
               (struct sockaddr*)&server_addr, server_len);

        if(strcmp(message, "exit") == 0) break;

        // Receive reply from server
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sock_fd, buffer, 1024, 0,
                 (struct sockaddr*)&server_addr, &server_len);

        printf("Server: %s\n", buffer);
    }

    close(sock_fd);
    return 0;
}

