#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main()
{
    int sockfd;
    char buffer[1024];

    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("UDP Server is Running...\n");

    len = sizeof(client_addr);

    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client_addr, &len);

    printf("Received Sentence: %s\n", buffer);

    char result[1024] = "";
    char word[100];

    int i = 0;

    while (sscanf(buffer + i, "%s", word) == 1)
    {
        if (strcmp(word, "tbh") == 0)
            strcat(result, "to be honest");
        else if (strcmp(word, "ig") == 0)
            strcat(result, "I guess");
        else if (strcmp(word, "tbf") == 0)
            strcat(result, "to be fair");
        else if (strcmp(word, "atm") == 0)
            strcat(result, "at the moment");
        else if (strcmp(word, "irl") == 0)
            strcat(result, "in real life");
        else if (strcmp(word, "lol") == 0)
            strcat(result, "laughing out loud");
        else if (strcmp(word, "asap") == 0)
            strcat(result, "as soon as possible");
        else if (strcmp(word, "omg") == 0)
            strcat(result, "oh my God");
        else if (strcmp(word, "ttyl") == 0)
            strcat(result, "talk to you later");
        else if (strcmp(word, "idk") == 0)
            strcat(result, "I don't know");
        else if (strcmp(word, "nvm") == 0)
            strcat(result, "never mind");
        else if (strcmp(word, "idc") == 0)
            strcat(result, "I don't care");
        else
            strcat(result, word);

        strcat(result, " ");

        i = i + strlen(word) + 1;
    }

    strcpy(buffer, result);

    sendto(sockfd, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&client_addr, len);

    printf("Translated sentence sent to client.\n");

    close(sockfd);

    return 0;
}