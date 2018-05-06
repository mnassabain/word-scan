/**
 * \file ensemble.h
 *
 * Fichier qui définit la structure d'ensemble ordonné
 * et les prototypes des fonctions sur cette structure
 *
 */

#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include "erreur.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/**
 * Nombre d'éléments d'un ensemble par défaut.
 * Si débordement, on rajoute de la place pour encore SIZE_TAB éléments
 */
#define SIZE_TAB 10

/**
 * Structure d'ensemble ordonné OrderedSet
 */
typedef struct s_set
{
    int * elements; /**< tableau contenant les éléments de l'ensemble */
    int max_elt;    /**< nombre maximum d'éléments dans le tableau
                        ce n'est pas une limite, cette variable sert
                        à faire attention aux débordements
                     */
    int n_elt;      /**< nombre d'éléments dans le tableau */

} * OrderedSet;     // pour eviter copie de données

// fonctions
OrderedSet initOrderedSet();

void freeOrderedSet(OrderedSet os);

int getNumberElt(OrderedSet os);

OrderedSet insertValue(OrderedSet os, int element);

bool contains(OrderedSet os, int element);

void printOrderedSet(OrderedSet os);

OrderedSet intersect(OrderedSet os1, OrderedSet os2);

// pour l'affichage
char * to_string(OrderedSet os);


#endif
