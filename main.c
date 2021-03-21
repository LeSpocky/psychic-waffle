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

static bool m_sigterm_received = false;

void handler_sigkill( int sig )
{
    printf( "Received SIGKILL (%d) ...\n", sig );
}

void handler_sigterm( int sig )
{
    printf( "Received SIGTERM (%d) ...\n", sig );
    m_sigterm_received = true;
}

int main( int argc, char *argv[] )
{
    unsigned int time_left, timeout = DEFAULT_TIMEOUT;
    struct sigaction act;
    int ec;

    /*  install signal handlers */
    memset( &act, 0, sizeof(act) );
    act.sa_handler = handler_sigkill;
    ec = sigaction( SIGKILL, &act, NULL );
    if ( ec != 0 )
    {
        fprintf( stderr, "Could not install SIGKILL handler: %s\n",
                 strerror(errno) );
    }
    else
    {
        printf( "Installed SIGKILL handler ...\n" );
    }

    memset( &act, 0, sizeof(act) );
    act.sa_handler = handler_sigterm;
    ec = sigaction( SIGTERM, &act, NULL );
    if ( ec != 0 )
    {
        fprintf( stderr, "Could not install SIGTERM handler: %s\n",
                 strerror(errno) );
        return EXIT_FAILURE;
    }
    printf( "Installed SIGTERM handler ...\n" );

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

    if ( m_sigterm_received )
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
