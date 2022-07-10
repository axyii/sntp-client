#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "sntp.h"

void usage();

static char* host = "1.pool.ntp.org";

int 
main(int argc, char** argv){
    int ch;
    time_t mytime;
    if( argc == 1){
        mytime = get_time(host);
        printf( "%s\n", ctime( ( const time_t* ) &mytime ) );
        exit(EXIT_SUCCESS);

    }
    while (( ch = getopt(argc, argv, "ruh")) != -1){
        switch(ch){
            case 'r':
                mytime = get_time(host);
                printf( "%s\n", ctime( ( const time_t* ) &mytime ) );
                break;
            case 'u':
                mytime = get_time(host);
                printf( "%llu\n", (unsigned long long) mytime);
                break;
            case 'h':
                usage(EXIT_SUCCESS);
                break;
            default:
                usage(EXIT_FAILURE);
                break;

        }

    }

    return(0);
}


void
usage(int status){

    (void)fprintf(stdout, "%s\n%s\n%s\n%s\n",
            "usage: time <flag>",
            "       time [-r :time in regular format]",
            "       time [-u :time in unix format]",
            "       time [-h :help]");
    exit(status);
}
