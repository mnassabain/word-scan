#ifndef __ABR_H__
#define __ABR_H__

#include <stdbool.h>
#include <string.h>
#include "ensemble.h"

// structure

typedef struct s_arbre
{
    char * mot; // char mot[MAX_MOT]
    OrderedSet positions;

    struct s_arbre *fg, *fd;

} Noeud, *SearchTree;

// prototypes

SearchTree initBinarySearchTree();

void freeBinarySearchTree(SearchTree st);

int getNumberString(SearchTree st);

int getTotalNumberString(SearchTree st);

SearchTree insert(SearchTree st, char *mot, int index);

OrderedSet find(SearchTree st, char *mot);

OrderedSet findCooccurrences(SearchTree st, char ** mots);

void printBinarySearchTree(SearchTree st);

// fonction supplémentaires
void printBinarySearchTreeAux(SearchTree st, int niveau);

bool vide(SearchTree st);

SearchTree enraciner(char *mot, OrderedSet positions, SearchTree st1, SearchTree st2);

void coupure(SearchTree st, char *mot, SearchTree g, SearchTree d);

#endif
