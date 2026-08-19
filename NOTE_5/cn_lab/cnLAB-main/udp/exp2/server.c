#include <stdio.h>      // Standard input/output functions
#include <string.h>     // String handling functions
#include <arpa/inet.h>  // Internet address structures and functions
#include <unistd.h>     // close() function

// Define the port number on which the server will listen
#define PORT 12345

int main() {

    // Socket descriptor for the UDP socket
    int sockfd;

    // Buffer to store the received message
    char buffer[1024];

    // Structure to store the server's address and client's address
    struct sockaddr_in server_addr, client_addr;

    // socklen_t is a socket library data type used to store the size of a socket address structure.
    // Why do we use 'len'? recvfrom() expects a pointer to a variable (&len), not a constant value
    // like sizeof(client_addr). Before calling recvfrom(), len is initialized with the size of
    // client_addr. After the call, the operating system updates len with the actual size of the
    // client's address.
    socklen_t len;

    // --------------- Step 1: Create a UDP socket ---------------

    // AF_INET : IPv4 addressing
    // SOCK_DGRAM : UDP socket
    // 0        : Default UDP protocol

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // --------------- Step 2: Configure the server address ---------------

    // Specify IPv4
    server_addr.sin_family = AF_INET;

    // Accept connections on any available network interface
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Convert port number from host byte order to network byte order
    server_addr.sin_port = htons(PORT);

    // --------------- Step 3: Bind the socket ---------------
    // Associates the socket with the server's IP address and port number

    bind(sockfd,
         (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    printf("UDP Server is running...\n");

    // Initialize the client address length
    len = sizeof(client_addr);

    // --------------- Step 4: Receive a message from the client ---------------

    // recvfrom() receives the message and stores the sender's
    // IP address and port number in client_addr.

    recvfrom(sockfd,
             buffer,
             sizeof(buffer),
             0,
             (struct sockaddr *)&client_addr,
             &len);

    // Display the received message
    printf("Message received from Client: %s\n", buffer);

    // --------------- Step 5: Prepare the response ---------------

    char *msg = "Hello from UDP Server";

    // --------------- Step 6: Send the response ---------------
    // sendto() sends the reply to the client whose address is stored
    // in client_addr.

    sendto(sockfd,
           msg,
           strlen(msg) + 1,  // +1 sends the null character '\0'
           0,
           (struct sockaddr *)&client_addr,
           len);

    printf("Response sent to the client.\n");

    // --------------- Step 7: Close the socket ---------------

    // Releases the socket resource.
    close(sockfd);

    printf("Server socket closed.\n");

    return 0;
}