/* A simple "Hello" server using TCP */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define SERVER_TCP_PORT 3000    /* well-known port */

void serve_client(int);

int main(int argc, char **argv)
{
    int sd, new_sd, client_len, port;
    struct sockaddr_in server, client;

    switch (argc)
    {
    case 1:
        port = SERVER_TCP_PORT;
        break;
    case 2:
        port = atoi(argv[1]);
        break;
    default:
        fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        exit(1);
    }

    /* Create a stream socket  */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "Can't create a socket\n");
        exit(1);
    }

    /* Bind an address to the socket  */
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        fprintf(stderr, "Can't bind name to socket\n");
        exit(1);
    }

    /* Queue up to 5 connect requests  */
    listen(sd, 5);

    while (1)
    {
        client_len = sizeof(client);
        new_sd = accept(sd, (struct sockaddr *)&client, &client_len);
        if (new_sd < 0)
        {
            fprintf(stderr, "Can't accept client \n");
            exit(1);
        }

        serve_client(new_sd);
        close(new_sd); // Close the connection to the client
    }
}

/* Serve a "Hello" message to the client */
void serve_client(int sd)
{
    char hello_message[] = "Hello\n";

    // Send the "Hello" message to the client
    write(sd, hello_message, sizeof(hello_message) - 1);

    // Close the connection to the client
    close(sd);
}
