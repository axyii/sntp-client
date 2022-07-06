#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "sntp.h"

static const char* PORT = "123";

time_t 
get_time(const char* host){
    int sockfd;
    int status;
    struct addrinfo hints, *result, *p;
    sntp_packet packet = {0,0,0,0,0,0,0,0,0,0,0};
    //Zeroing the packet
    memset(&packet,0,sizeof(packet));

    packet.li_vn_mode = LI_VN_MODE;

    memset(&hints,0,sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_flags = AI_PASSIVE;

    if(( status = getaddrinfo(host,PORT,&hints,&result)) != 0){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);

    }
    for(p = result; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                        p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        exit(EXIT_FAILURE);
    }

    int n;
    n = write( sockfd, ( char* ) &packet, sizeof(sntp_packet ) );

    if (n < 0){
        fprintf(stderr, "client: error writing to socket\n");
        exit(EXIT_FAILURE);
    }

    n = read(sockfd, ( char* ) &packet, sizeof(sntp_packet));

    if (n < 0){
        fprintf(stderr, "client: error reading from socket\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);
    packet.trantim = ntohl( packet.trantim ); // converting from network byte order to host byte order

    time_t actual_time = ( time_t ) ( packet.trantim - NTP_TIMESTAMP_DELTA );

    return actual_time;
}
