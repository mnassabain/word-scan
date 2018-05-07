#include <stdio.h>
#include <stdlib.h>

#include "ensemble.h"
#include "abr.h"
#include "arbeq.h"
#include "tests.h"
#include <stdbool.h>
#include <unistd.h>

char * prog;

bool flag_A = false;    // affiche l'aide
bool flag_E = false;    // isBalanced
bool flag_H = false;    // height
bool flag_P = false;    // avgdepth
bool flag_U = false;    // support UTF-8
bool flag_T = false;    // lancement des jeux de test

char * traiter_arguments(int argc, char * const argv[]);


int main(int argc, char * const argv[])
{
    char * filename = traiter_arguments(argc, argv);

    if (flag_A)
    {
        printf("aide = uaeibfozebf\n");
    }

    if (flag_T)
    {
        tests();
        return 0;
    }

    SearchTree st = construction_arbre(filename);
    printBinarySearchTree(st);

    if (flag_E)
    {
        bool b = isBalanced(st);
        printf("L'arbre est-il équilibré? %s\n", (b) ? "oui" : "non");
    }

    if (flag_H)
    {
        int h = getHeight(st);
        printf("La hauteur de l'arbre est: %d\n", h);
    }

    if (flag_P)
    {
        int p = getAverageDepth(st);
        printf("La profondeur moyenne des noeuds est: %d\n", p);
    }

    freeBinarySearchTree(st);

    return 0;
}




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

    return argv[optind];
}
