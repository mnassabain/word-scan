/**
 * \file more.c
 * 
 * Fichier qui contient des fonction générales utiles 
 * 
 */

#include "more.h"

/* =====    FONCTIONS    ===== */

/**
 * \brief Fonction qui affiche les messages d'erreur
 * 
 * Fait appel à perror si nécessaire ou affiche le message d'erreur
 * 
 * \param syserr 1 si l'erreur change errno, 0 sinon
 * \param fmt Format d'affichage
 * 
 */
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


/**
 * \brief Enlève l'accent de la lettre
 *
 * Transforme le short en char en enlèvant l'accent.
 *
 * \param c Lettre à transformer.
 *
 * \return Caractère sans accent sous forme de char
 *
 */
char transformer_utf8(int c)
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

        default:
            resultat='x';
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


/**
 * \brief Fonction interne: transforme un entier en string (char *)
 *
 * \param nombre Entier à transformer en string
 *
 * \return Le nombre sous forme de string
 *
 */
char* int_to_string(int nombre)
{
	static char buf[32] = {0};

	int i;
	for(i = 30; nombre > 0 && i > 0 ; --i, nombre /= 10)
	{
		buf[i] = "0123456789abcdef"[nombre % 10];
	}

	return &buf[i+1];
}


/**
 * \brief Comparaison de deux chaînes de caractères.
 *
 * \param mot1
 * \param mot2
 *
 * \return  Résultat de la comparaison.
 *
 */
int comp(char *mot1, char *mot2)
{
    return strcmp(mot1, mot2);
}


/**
 * \brief Traiter les argument donnée lors l'appel au programme
 * 
 * \param argc
 * \param argv
 * 
 * \return
 * 
 */
char * traiter_arguments(int argc, char * const argv[])
{
    prog = argv[0];

    if (argc != 2 && argc != 3 && argc != 4 && argc != 5 && argc != 6)
    {
        raler(0, "Usage: %s fichier", prog);
    }

    int opt;
    while((opt = getopt(argc, argv, "aehput")) != -1)
    {
        switch(opt)
        {
            case 'a':
                flag_A = true;
                break;
            case 'e':
                flag_E = true;
                break;

            case 'h':
                flag_H = true;
                break;

            case 'p':
                flag_P = true;
                break;

            case 'u':
                flag_U = true;
                break;

            case 't':
                flag_T = true;
                break;

            default:
                raler(0, "Option invalide");
        }
    }

    if (argc - optind == 0 && (!flag_A && !flag_T))
    {
        raler(0, "Usage: %s fichier", prog);
    }

    return argv[optind];
}