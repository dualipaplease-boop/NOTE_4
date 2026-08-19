#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(sock, (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    printf("Connected to server\n");

    // Send message
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);

    send(sock, buffer, strlen(buffer) + 1, 0);

    // Receive response
    recv(sock, buffer, sizeof(buffer), 0);

    printf("Server: %s\n", buffer);

    close(sock);

    return 0;
}