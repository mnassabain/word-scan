#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include "erreur.h"
#include <stdbool.h>

// structure
#define SIZE_TAB 10

typedef struct s_set
{
    int * elements;
    int max_elt;    // nombre max d'elements
    int n_elt;      // nombre d'elements

} * OrderedSet;     // pour eviter copie de données

// fonctions
OrderedSet initOrderedSet();

void freeOrderedSet(OrderedSet os);

int getNumberElt(OrderedSet os);

void insertValue(OrderedSet os, int element);

bool contains(OrderedSet os, int element);

void printOrderedSet(OrderedSet os);

OrderedSet intersect(OrderedSet os1, OrderedSet os2);


#endif
