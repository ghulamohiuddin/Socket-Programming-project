
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    printf("Server waiting for connection...\n");

    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    printf("Client connected.\n\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        recv(client_fd, buffer, sizeof(buffer), 0);

        if(strcmp(buffer,"exit")==0)
        {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client : %s\n", buffer);

        printf("Server : ");
        fgets(buffer,sizeof(buffer),stdin);

        buffer[strcspn(buffer,"\n")] = '\0';

        send(client_fd,buffer,strlen(buffer),0);

        if(strcmp(buffer,"exit")==0)
            break;
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
