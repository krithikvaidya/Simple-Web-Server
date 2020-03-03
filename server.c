#include <stdio.h>
#include <stdlib.h>  // for EXIT_FAILURE
#include <arpa/inet.h>  // for INET6_ADDRSTRLEN, inet_ntop()
#include <sys/types.h>
#include <sys/socket.h> // for socklen_t
#include "net.h" // for get_listener_socket(), get_in_addr()

#define PORT "3490" // the TCP port that the server is listening on


void handle_http_request(int fd) // TODO: add struct cache *cache parameter
{
    // TODO: implement
}


int main()
{

    int newfd;
    struct sockaddr client_sockaddr;
    char cli_ipv6[INET6_ADDRSTRLEN];

    // Get a listening socket
    int listenfd = get_listener_socket(PORT);  // PORT is a string

    if (listenfd < 0) 
    {
        fprintf(stderr, "webserver: fatal error getting listening socket. exiting...\n");
        exit(EXIT_FAILURE);
    }

    printf("webserver: waiting for connections on port %s ...\n", PORT);

    // Accept incoming connections and responds to the request. 
    // Then go back to listening mode.

    while (1) 
    {
        socklen_t sin_size = sizeof(client_sockaddr);

        // Parent process will block on the accept() call until someone
        // makes a new connection

        newfd = accept(listenfd, (struct sockaddr *)&client_sockaddr, &sin_size);

        if (newfd == -1)  // could not open socket to client
        {
            perror("accept");
            continue;
        }

        // Print out a message that we got the connection
        inet_ntop(client_sockaddr.ss_family, get_in_addr((struct sockaddr *)&client_sockaddr), cli_ipv6,
                  sizeof(cli_ipv6));
        printf("webserver: received connection from %s\n", cli_ipv6);

        // newfd is a new socket descriptor for the new connection.
        // listenfd is still listening for new connections.

        handle_http_request(newfd); // TODO: call with cache

        close(newfd);

    }

    // unreachable
    return EXIT_SUCCESS;
}