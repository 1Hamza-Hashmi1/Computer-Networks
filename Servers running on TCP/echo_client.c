/* A simple "Hello" client using TCP */
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#define SERVER_TCP_PORT 3000 /* well-known port */
#define BUFLEN 256           /* buffer length */

int main(int argc, char **argv)
{
    int n, i, bytes_to_read;
    int sd, port;
    struct hostent *hp;
    struct sockaddr_in server;
    char *host, rbuf[BUFLEN], sbuf[BUFLEN];

    switch (argc)
    {
    case 2:
        host = argv[1];
        port = SERVER_TCP_PORT;
        break;
    case 3:
        host = argv[1];
        port = atoi(argv[2]);
        break;
    default:
        fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
        exit(1);
    }

    /* Create a stream socket  */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "Can't create a socket\n");
        exit(1);
    }

    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (hp = gethostbyname(host))
        bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    else if (inet_aton(host, (struct in_addr *)&server.sin_addr))
    {
        fprintf(stderr, "Can't get server's address\n");
        exit(1);
    }

    /* Connecting to the server */
    if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        fprintf(stderr, "Can't connect \n");
        exit(1);
    }

    printf("Received: ");

    // Read and display the "Hello" message from the server
    while ((n = read(sd, rbuf, BUFLEN - 1)) > 0)
    {
        rbuf[n] = '\0'; // Null-terminate the received message
        printf("%s", rbuf);
    }

    printf("\n");

    close(sd); // Close the client socket
    return 0;
}
