#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int main()
{
    int sockfd;

    char buffer[100];

    struct sockaddr_in server, client;

    socklen_t len = sizeof(client);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Time Server is Running...\n");

    while(1)
    {
        // Receive request from client
        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client, &len);

        // Get current system time
        time_t t = time(NULL);

        // Convert time to string
        // ctime() converts the numeric time into a readable string.
        // strcpy() copies one string into another.
        strcpy(buffer, ctime(&t));

        // Send time to client
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client, len);
    }

    close(sockfd);

    return 0;
}