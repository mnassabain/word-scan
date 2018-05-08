/**
 * \file more.c
 *
 * Fichier qui contient des fonction générales utiles
 *
 */

#include "more.h"
#include "ensemble.h"
#include "abr.h"
#include "arbeq.h"
#include "tests.h"

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
        case U_MIN_CRX:
            resultat = 'u';
            break;

        case U_MAJ_GRV:
        case U_MAJ_CRX:
            resultat = 'U';
            break;

        case C_MIN_CDL:
            resultat = 'c';
            break;

        case C_MAJ_CDL:
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
 * \brief Traiter les arguments donnée lors l'appel au programme
 *
 * Extrait le nom du fichier et active les flags.
 * 
 * \param argc nombre d'arguments
 * \param argv liste d'arguments
 *
 * \return Le nom du fichier entrée par l'utilisateur
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
    while((opt = getopt(argc, argv, "aehputni")) != -1)
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

            case 'n':
                flag_N = true;
                break;

            case 'i':
                flag_I = true;
                break;

            default:
                raler(0, "Option invalide");
        }
    }

    if (argc - optind == 0 && (!flag_A && !flag_T &&!flag_I))
    {
        raler(0, "Usage: %s fichier", prog);
    }

    return argv[optind];
}


void menu()
{
    printf("Choisissez ce que vous voulez faire:\n");
    printf("1. Créer un arbre à partir d'un fichier\n");
    printf("2. Afficher l'arbre\n");
    printf("3. Afficher la hauteur de l'arbre\n");
    printf("4. Afficher la profondeur moyenne des noeuds de l'arbre\n");
    printf("5. Supprimer l'arbre\n");
    printf("q. Appuyez sur q pour quitter\n");
}


void interactif ()
{
    SearchTree st = initBinarySearchTree();
    bool existTree = false;
    printf("Mode interactif lancé.\n");
    menu ();
    char c = getchar();
    if(c != '\n' && c != EOF)
      {
         int d;
         while((d = getchar()) != '\n' && d != EOF);
    }
    while(c != 'q')
    {
        switch (c) {
            case '1':
                if (existTree)
                {
                    printf("\nVous ne pouvez pas créer d'arbre car vous en avez déjà un, veuillez supprimer le précédent.\n");
                }
                else
                {
                    printf("\nCréation de l'arbre.\n");
                    st = construction_arbre("texte/foo.txt");
                    existTree = true;
                }
                break;

            case '2':
                if (existTree)
                {
                    printf("\nAffichage de l'arbre:\n");
                    printBinarySearchTree(st);
                }
                else
                {
                    printf("\nVous n'avez pas créé d'arbre, vous ne pouvez donc pas l'afficher.\n");
                }
                break;

            case '3':
                printf("\nHauteur de l'arbre: %d\n", getHeight(st));
                break;

            case '4':
                printf("\nProfondeur moyenne des noeuds de l'arbre: %f\n", getAverageDepth(st));
                break;

            case '5':
                printf("\nSuppression de l'arbre");
                existTree = false;
                freeBinarySearchTree(st);
                break;

            default:
                printf("Option %c invalide, entrez une autre option.\n", c);
        }
        printf("\n");
        menu ();
        c = getchar();
        if(c != '\n' && c != EOF)
        {
            int d;
            while((d = getchar()) != '\n' && d != EOF);
        }
    }
    return;
}
