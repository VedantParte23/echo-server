#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char const *argv[])
{

    struct addrinfo hints, *res;
    int sockfd, status;
    

    struct sockaddr_storage their_storage;
    socklen_t addr_size;
    addr_size = sizeof(their_storage);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0)
    {
        printf("Error");
    }

    // socket
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // bind
    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    bind(sockfd, res->ai_addr, res->ai_addrlen);

    // listen
    listen(sockfd, 10);

    // accept
    int accept_fd;
    accept_fd = accept(sockfd, (struct sockaddr *)&their_storage, &addr_size);
    while (1)
    {
        
    
    
    
        //recv
        char recv_buff[1024]; 
        ssize_t recv_bytes;
    
        recv_bytes = recv(accept_fd, recv_buff, sizeof(recv_buff) - 1, 0);
    
        if (recv_bytes > 0)
        {
            recv_buff[recv_bytes] = '\0'; // null-terminate
            printf("%s\n",recv_buff);
        }
    
    
        // send section
        ssize_t  byte_send;
    
        ssize_t len = sizeof(recv_buff);
    
        byte_send = send(accept_fd, recv_buff, recv_bytes, 0);
    
        
    }    
    close(accept_fd);
    
    return 0;
}
