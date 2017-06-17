#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "roman.h"

int build_socket(int port_modifier);
char *buf_strip(char *buf);
void kill_children(int signum)
{
    kill(0,SIGTERM);
}

int main(void)
{
    
    char buf[256];
    struct sockaddr_storage client;
    socklen_t client_sz = sizeof(client);

    struct sigaction close_forks = {0};
    close_forks.sa_handler = kill_children;
    sigaction(SIGINT, &close_forks, NULL);
    

    int sock;
    int sock_1k;
    int sock_2k;

    
    if(fork()==0)
    {
        sock = build_socket(2000);
        
        for(;;)
        {
            
            ssize_t received = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *) &client, 
            &client_sz);
            
            buf[received] = '\0';
            if (received < 0 )
            {
                perror("problem receiving");
            }
            int retval = roman(buf);

            char *send_buf = malloc(100 * sizeof(int));
            memset(send_buf, '\0', sizeof(send_buf));
            snprintf(send_buf, sizeof(send_buf), "0x%x", retval);

            sendto(sock, send_buf, strlen(send_buf), 0, 
                  (struct sockaddr *)&client, client_sz); 

            free(send_buf);

            

        }

                  
    }

    if(fork()==0)
    {
        sock_1k = build_socket(1000);
        
        for(;;)
        {
            ssize_t received = recvfrom(sock_1k, buf, sizeof(buf), 0, (struct sockaddr *) &client, 
            &client_sz);
            
            buf[received] = '\0';
            if (received < 0 )
            {
                perror("problem receiving");
            }
            printf("Connected\n");

        }
    }        

    if(fork()==0)
    {
        sock_2k = build_socket(3000);
        for(;;)
        {
            
            ssize_t received = recvfrom(sock_2k, buf, sizeof(buf), 0, (struct sockaddr *) &client, 
            &client_sz);
            
            buf[received] = '\0';
            if (received < 0 )
            {
                perror("problem receiving");
            }
            printf("Connected\n");
   
        }    
   
    }
    
    waitpid(-1, NULL, 0); 
}

int build_socket(int port_modifier)
{
    
    char port_num[8];

    snprintf(port_num, sizeof(port_num), "%hd", getuid() + port_modifier);
        
    struct addrinfo *results;
    struct addrinfo hints = {0};
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    int err = getaddrinfo("127.0.0.1", port_num, &hints, &results);
    if(err != 0)
    {
        fprintf(stderr, "Could not parse address: %s\n", gai_strerror(err));
        return 2;
    }

    
    int sd = socket(results->ai_family, results->ai_socktype, 0);
    if(sd < 0 )
    {
        perror("Could not create socket");
        freeaddrinfo(results);
        return 3;
    }
    
    int set = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));

    err = bind(sd, results->ai_addr, results->ai_addrlen);
    if(err < 0)
    {
        perror("Could not create bind");
        close(sd);
        freeaddrinfo(results);
        return 4;
    }
    
    freeaddrinfo(results);
    return sd;
}  

char *buf_strip(char * buf)
{
    char *buffer = malloc(strlen(buf)+1);
    printf("%s\n", buf);
    
    
    strncpy(buffer, buf, strlen(buf)+1);
   
    free(buffer); 
    return buffer;
}
