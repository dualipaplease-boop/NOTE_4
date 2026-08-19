#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen
    listen(server_fd, 5);

    printf("Server is running...\n");

    while(1)
    {
        // Accept client
        new_socket = accept(server_fd,
                            (struct sockaddr *)&address,
                            (socklen_t *)&addrlen);

        printf("Client connected\n");

        // Create a child process for the client
        if(fork() == 0)
        {
            close(server_fd);

            // Receive message
            recv(new_socket, buffer, sizeof(buffer), 0);

            printf("Client: %s\n", buffer);

            // Send response
            char *message = "Hello from server";

            send(new_socket, message, strlen(message) + 1, 0);

            close(new_socket);

            return 0;
        }

        close(new_socket);
    }

    return 0;
}