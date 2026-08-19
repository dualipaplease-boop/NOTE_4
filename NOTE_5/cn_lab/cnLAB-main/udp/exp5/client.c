#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sockfd;

    char buffer[100] = "TIME";

    struct sockaddr_in server;

    socklen_t len = sizeof(server);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send request
    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&server, len);

    // Receive current time
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server, &len);

    // Display time
    printf("Server Time : %s", buffer);

    close(sockfd);

    return 0;
}