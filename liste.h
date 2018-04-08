#ifndef __LISTE_H__
#define __LISTE_H__

#include <stdbool.h>
#include <stdlib.h>

// structure
typdef struct s_elt {
    int val;
    struct s_elt * suiv;
} elemListe;

typedef struct s_OrderedSet {
    elemListe * first;
    int n_elt;
} *OrderedSet;

// fonctions
OrderedSet initOrderedSet();

void freeOrderedSet(OrderedSet os);

int getNumberElt(OrderedSet os);

OrderedSet insertValue(OrderedSet os, int element);

bool contains(OrderedSet os, int element);

void printOrderedSet(OrderedSet os);

OrderedSet intersect(OrderedSet os1, OrderedSet os2);

OrderedSet searchPos(OrderedSet os, int element);

#endif
