#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define DEFAULT_TIMEOUT 30

void sig_handler( int sig )
{
    printf( "Received signal %d ...\n", sig );
}

int main( int argc, char *argv[] )
{
    unsigned int timeout = DEFAULT_TIMEOUT;
    struct sigaction act;
    int ec;

    /*  install signal handlers */
    memset( &act, 0, sizeof(act) );

    act.sa_handler = sig_handler;
    ec = sigaction( SIGTERM, &act, NULL );
    if ( ec != 0 )
    {
        fprintf( stderr, "Could not install signal handler: %s\n", strerror(errno) );
        return EXIT_FAILURE;
    }
    printf( "Installed signal handler ...\n" );

    /*  do things   */
    if ( argc > 1 )
    {
        timeout = strtoul( argv[1], NULL, 10 );
    }

    printf( "Sleeping for %u seconds now ...\n", timeout );

    sleep( timeout );

    printf( "Bye.\n" );

    return EXIT_SUCCESS;
}
