/**
 * \file main.c
 * 
 * Fichier qui porte la fonction main du programme.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "ensemble.h"
#include "abr.h"
#include "arbeq.h"
#include "tests.h"
#include <stdbool.h>
#include <unistd.h>


/* =====    VARIABLES GLOBALES    ===== */

char * prog;

bool flag_A = false;    // affiche l'aide
bool flag_E = false;    // isBalanced
bool flag_H = false;    // height
bool flag_P = false;    // avgdepth
bool flag_U = false;    // support UTF-8
bool flag_T = false;    // lancement des jeux de test
bool flag_N = false;    // nombre de noeuds
bool flag_I = false;    // mode interactif


/* =====    LE MAIN    ===== */

int main(int argc, char * const argv[])
{
    char * filename = traiter_arguments(argc, argv);

    if (flag_A)
    {
        aide();
        return 0;
    }

    if (flag_T && !flag_I)
    {
        tests();
        return 0;
    }

    if (flag_I)
    {
        interactif();
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

    if (flag_N)
    {
        int n = getNumberString(st);
        printf("Le nombre de noeuds dans l'arbre est %d\n", n);
    }

    freeBinarySearchTree(st);

    return 0;
}
