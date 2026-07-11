#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("UDP Server waiting for messages...\n");

    while(1) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(server_fd, buffer, 1024, 0,
                 (struct sockaddr*)&client_addr, &client_len);

        if(strcmp(buffer, "exit") == 0) break;
        printf("Client: %s\n", buffer);

        char reply[1024];
        printf("Server reply: ");
        fgets(reply, sizeof(reply), stdin);
        reply[strcspn(reply, "\n")] = 0;

        sendto(server_fd, reply, strlen(reply), 0,
               (struct sockaddr*)&client_addr, client_len);
    }

    close(server_fd);
    return 0;
}
