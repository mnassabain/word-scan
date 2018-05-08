/**
 * \file ensemble.h
 *
 * Fichier qui définit la structure d'ensemble ordonné
 * et les prototypes des fonctions sur cette structure
 *
 */

#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include "more.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/* =====    MACROS    ===== */

/**
 * Nombre d'éléments d'un ensemble par défaut.
 * Si débordement, on rajoute de la place pour encore SIZE_TAB éléments
 */
#define SIZE_TAB    10

/** Utilisée dans to_string(). Contrôle le dépassement du buffer. **/
#define MAX_BUFFER  128


/* =====    STRUCTURES    ===== */

/** \typedef Structure d'ensemble ordonné OrderedSet **/
typedef struct s_set
{
    /** tableau contenant les éléments de l'ensemble */
    int * elements;

    /** nombre maximum d'éléments que le tableau peut contenir sans faire une
      * reallocation **/
    int max_elt;

    /** nombre d'éléments dans le tableau */
    int n_elt;

} * OrderedSet;


/* =====    FONCTIONS    ===== */

/** \brief Initialise un ensemble ordonné. **/
OrderedSet initOrderedSet();


/** \brief Libération de mémoire occupé par l'ensemble ordonné **/
void freeOrderedSet(OrderedSet os);


/** \brief Renvoie le nombre d'éléments dans l'ensemble. **/
int getNumberElt(OrderedSet os);


/** \brief Insere l'élément element dans l'ensemble os **/
OrderedSet insertValue(OrderedSet os, int element);


/** \brief Insère un élément à la fin d'un ensemble ordonné **/
OrderedSet insertFin(OrderedSet os, int element);


/** \brief Teste si un ensemble contient un élément **/
bool contains(OrderedSet os, int element);


/** \brief Affiche un ensemble ordonné **/
void printOrderedSet(OrderedSet os);


/** \brief Cherche l'intersection de deux ensembles **/
OrderedSet intersect(OrderedSet os1, OrderedSet os2);


/** brief Transforme un ensemble ordonné en string (char *) **/
char * to_string(OrderedSet os);


#endif
