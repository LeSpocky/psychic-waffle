#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#define DEFAULT_TIMEOUT 30

static bool m_signal_received = false;

void sig_handler( int sig )
{
    printf( "Received signal %d ...\n", sig );
    m_signal_received = true;
}

int main( int argc, char *argv[] )
{
    unsigned int time_left, timeout = DEFAULT_TIMEOUT;
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

    /*  report useful information   */
    printf( "My PID is %u ...\n", getpid() );

    /*  do things   */
    if ( argc > 1 )
    {
        timeout = strtoul( argv[1], NULL, 10 );
    }

    printf( "Sleeping for %u seconds now ...\n", timeout );

    time_left = sleep( timeout );
    if ( time_left > 0 )
    {
        printf( "Sleep interrupted, %u seconds left ...\n", time_left );
    }

    if ( m_signal_received )
    {
        printf( "Sleeping for another %u seconds ...\n", timeout );
        time_left = sleep( timeout );
        if ( time_left > 0 )
        {
            printf( "Sleep interrupted, %u seconds left ...\n", time_left );
        }
    }

    printf( "Bye.\n" );

    return EXIT_SUCCESS;
}
