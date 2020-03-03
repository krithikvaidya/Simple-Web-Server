#include <stdio.h>
#include <stdlib.h>  // for EXIT_FAILURE
#include <arpa/inet.h>  // for INET6_ADDRSTRLEN
#include "net.h" // for get_listener_socket()

#define PORT "3490" // the TCP port that the server is listening on

int main()
{

    int newfd;
    struct sockaddr client_sockaddr;
    char cli_ipv6[INET6_ADDRSTRLEN];

    // Get a listening socket
    int listenfd = get_listener_socket(PORT);

    if (listenfd < 0) 
    {
        fprintf(stderr, "webserver: fatal error getting listening socket. exiting...\n");
        exit(EXIT_FAILURE);
    }

}