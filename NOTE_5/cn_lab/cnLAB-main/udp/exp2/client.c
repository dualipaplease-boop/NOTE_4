#include <stdio.h>      // Standard input/output functions
#include <string.h>     // String handling functions
#include <arpa/inet.h>  // Internet address structures and functions
#include <unistd.h>     // close() function

// Define the server port number
#define PORT 12345

int main() {

    // Socket descriptor for the client's UDP socket
    int sockfd;

    // Buffer to store the response received from the server
    char buffer[1024];

    // Structure to store the server's IP address and port number
    struct sockaddr_in server_addr;

    // socklen_t is a socket library data type used to store
    // the size of a socket address structure.
    // recvfrom() expects a pointer to this variable (&len)
    // so that it can update the actual address size.
    socklen_t len;

    // --------------- Step 1: Create a UDP socket ---------------

    // AF_INET : IPv4
    // SOCK_DGRAM : UDP socket
    // 0 : Use the default UDP protocol

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // --------------- Step 2: Configure the server address ---------------

    // Specify IPv4
    server_addr.sin_family = AF_INET;

    // Convert the port number to network byte order
    server_addr.sin_port = htons(PORT);

    // Convert the IP address from text format to binary format.
    // 127.0.0.1 represents the localhost (same computer).
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Message to be sent to the server
    char *msg = "Hello from UDP client";

    // --------------- Step 3: Send the message ---------------
    // sendto() sends the message to the specified server address.
    // strlen(msg)+1 includes the null character ('\0').
    // sizeof(server_addr) specifies the size of the destination address.

    sendto(sockfd, msg, strlen(msg) + 1, 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Initialize len with the size of the server address structure.
    // recvfrom() uses this variable to return the actual address size.

    len = sizeof(server_addr);

    // --------------- Step 4: Receive the response ---------------

    // Receives the response from the server and stores it in buffer.
    // The server's address is stored in server_addr.

    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server_addr, &len);

    // Display the response received from the server
    printf("Server: %s\n", buffer);

    // --------------- Step 5: Close the socket ---------------

    // Releases the client's socket.
    close(sockfd);

    return 0;
}