#ifndef __LISTE_H__
#define __LISTE_H__

#include <stdbool.h>

// structure
typdef struct s_elt {
    int val;
    struct s_elt * suiv;
} elemListe;

typedef struct {
    elemListe * first;
    int n_elt;
} OrderedSet;

// fonctions
OrderedSet initOrderedSet();

void freeOrderedSet(OrderedSet os);

int getNumberElt(OrderedSet os);

void insertValue(OrderedSet os, int element);

bool contains(OrderedSet os, int element);

void printOrderedSet(OrderedSet os);

OrderedSet intersect(OrderedSet os1, OrderedSet os2);

#endif
