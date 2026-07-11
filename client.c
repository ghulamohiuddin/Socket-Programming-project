#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);

    connect(sock,(struct sockaddr *)&server,sizeof(server));

    printf("Connected to server.\n\n");

    while(1)
    {
        printf("Client : ");
        fgets(buffer,sizeof(buffer),stdin);

        buffer[strcspn(buffer,"\n")] = '\0';

        send(sock,buffer,strlen(buffer),0);

        if(strcmp(buffer,"exit")==0)
            break;

        memset(buffer,0,sizeof(buffer));

        recv(sock,buffer,sizeof(buffer),0);

        if(strcmp(buffer,"exit")==0)
        {
            printf("Server disconnected.\n");
            break;
        }

        printf("Server : %s\n\n",buffer);
    }

    close(sock);

    return 0;
}
