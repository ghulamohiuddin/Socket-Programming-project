#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Connected to server!\n");

    while(1) {
        char message[1024];
        printf("You: ");
        fgets(message, sizeof(message), stdin);
        send(sock_fd, message, strlen(message), 0);
        if(strcmp(message, "exit\n") == 0) break;

        memset(buffer, 0, sizeof(buffer));
        read(sock_fd, buffer, 1024);
        printf("Server: %s", buffer);
    }

    close(sock_fd);
    return 0;
}
