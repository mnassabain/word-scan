/**
 * \file arbeq.h
 *
 * Fichier qui contient les structures et prototypes de l'arbre binaire
 * de recherche équilibré.
 *
 */


#ifndef __ARBEQ_H__
#define __ARBEQ_H__

#include <stdbool.h>
#include "abr.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

bool isBalanced(SearchTree st);

int getHeight (SearchTree st);

int getAverageDepth (SearchTree st);

SearchTree rotateLeft(SearchTree st);

SearchTree rotateRight(SearchTree st);

SearchTree rotateLeftRight(SearchTree st);

SearchTree rotateRightLeft(SearchTree st);

SearchTree balance(SearchTree st);

// construction
int getEq(SearchTree st);

SearchTree construction_arbre(char * filename);

SearchTree insavl(SearchTree st, char * mot, int index);

#endif
