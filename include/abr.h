#ifndef __ABR_H__
#define __ABR_H__

#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "ensemble.h"

// structure

typedef struct s_arbre
{
    char * mot; // char mot[MAX_MOT]
    OrderedSet positions;

    int eq; // indicateur de équilibre

    struct s_arbre *fg, *fd;

} Noeud, *SearchTree;

// prototypes

SearchTree initBinarySearchTree();

void freeBinarySearchTree(SearchTree st);

int getNumberString(SearchTree st);

int getTotalNumberString(SearchTree st);

OrderedSet find(SearchTree st, char *mot);

OrderedSet findCooccurrences(SearchTree st, char ** mots, int nbMots);

void printBinarySearchTree(SearchTree st);

// fonction supplémentaires
void printBinarySearchTreeAux(SearchTree st, int niveau, int position, char *** mot, int * ligne);

bool vide(SearchTree st);

SearchTree enraciner(char *mot, OrderedSet positions, SearchTree st1, SearchTree st2);

int comp(char * mot1, char * mot2);

#endif
