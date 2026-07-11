#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server waiting for connection...\n");
    client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    printf("Client connected!\n");

    while(1) {
        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, 1024);
        if(strcmp(buffer, "exit\n") == 0) break;
        printf("Client: %s", buffer);

        char reply[1024];
        printf("Server reply: ");
        fgets(reply, sizeof(reply), stdin);
        send(client_fd, reply, strlen(reply), 0);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
