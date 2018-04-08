#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include <stdbool.h>

// structure


// fonctions
OrderedSet initOrderedSet();

void freeOrderedSet(OrderedSet os);

int getNumberElt(OrderedSet os);

void insertValue(OrderedSet os, int element);

bool contains(OrderedSet os, int element);

void printOrderedSet(OrderedSet os);

OrderedSet intersect(OrderedSet os1, OrderedSet os2);


#endif
