#include "erreur.h"

void raler(int syserr, char * message)
{
    if(syserr)
    {
        perror(message);
    }
    else
    {
        fprintf(stderr, "%s", message);
    }

    exit(EXIT_FAILURE);
}
