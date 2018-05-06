#include "more.h"

noreturn void raler (int syserr, const char *fmt, ...)
{
    va_list ap ;

    va_start (ap, fmt) ;
    fprintf (stderr, "%s: ", prog) ;
    vfprintf (stderr, fmt, ap) ;
    fprintf (stderr, "\n") ;
    va_end (ap) ;
    if (syserr)
	perror ("") ;

    exit (1) ;
}


char transformer_utf8(short c)
{
    char resultat;

    switch(c)
    {
        case E_MIN_EGU:
        case E_MIN_GRV:
        case E_MIN_CRX:
            resultat = 'e';
            break;

        case E_MAJ_EGU:
        case E_MAJ_GRV:
        case E_MAJ_CRX:
            resultat = 'E';
            break;

        case A_MIN_GRV:
        case A_MIN_CRX:
            resultat = 'a';
            break;

        case A_MAJ_GRV:
        case A_MAJ_CRX:
            resultat = 'A';
            break;

        case I_MIN_CRX:
        case I_MIN_TRM:
            resultat = 'i';
            break;

        case I_MAJ_CRX:
        case I_MAJ_TRM:
            resultat = 'I';
            break;

        case O_MIN_CRX:
            resultat = 'o';
            break;

        case O_MAJ_CRX:
            resultat = 'O';
            break;

        case U_MIN_GRV:
            resultat = 'u';
            break;

        case U_MAX_GRV:
            resultat = 'U';
            break;

        case C_MIN_CDL:
            resultat = 'c';
            break;

        case C_MAX_CDL:
            resultat = 'C';
            break;
    }

    return resultat;
}


/**
 * \brief Teste si un mot contient un caractère
 *
 * Teste si la chaine de caractères mot contient le caractère x
 * \param x un caractère
 * \param mot une chaine de caractères
 *
 * \return Booléen qui vaut true si la chaine contient le caractère x,
 * false sinon
 *
 */
bool contient(char x, char * mot)
{
    int i;
    for (i = 0; mot[i] != '\0'; i++)
    {
        if (x == mot[i])
        {
            return true;
        }
    }

    return false;
}
