/**
 * \file abr.h
 *
 * Fichier qui contient les structures et prototypes de l'arbre binaire.
 *
 */

#ifndef __ABR_H__
#define __ABR_H__

#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "ensemble.h"

/**
 * \typedef SearchTree Structure qui réprésente les arbres binaires.
 *
 */
typedef struct s_arbre
{
    /** \{ **/
    /** Les données à stocker dans un noeud; le mot **/
    char * mot;

    /** L'ensemble ordonné de ses cooccurences **/
    OrderedSet positions;

    /** Facteur d'équilibre **/
    int eq;

    /** Pointeurs vers le fils gauche et le fils droit **/
    struct s_arbre *fg, *fd;
    /** \} **/

} Noeud, *SearchTree;

/** PROTOTYPES **/

/** \brief Intialise un arbre binaire de recherche. **/
SearchTree initBinarySearchTree();


/** \brief Libère un arbre binaire de recherche. **/
void freeBinarySearchTree(SearchTree st);


/** \brief Trouver le nombre de mots dans l'arbre (noeuds) **/
int getNumberString(SearchTree st);


/** \brief Cherche le nombre de mots total dans l'arbre **/
int getTotalNumberString(SearchTree st);


/*\brief Cherche un mot dans un arbre binaire de recherche **/
OrderedSet find(SearchTree st, char *mot);


/** \brief Cherche les positions communes des mots données en argument **/
OrderedSet findCooccurrences(SearchTree st, char ** mots, int nbMots);


/** \brief Affiche l'arbre binaire donné **/
void printBinarySearchTree(SearchTree st);


/** \brief Teste si l'arbre binaire est vide **/
bool vide(SearchTree st);


/** \brief Constructeur de base de l'arbre binaire **/
SearchTree enraciner(char *mot, OrderedSet positions, SearchTree st1,
    SearchTree st2);



/** FONCTION SUPPLÉMENTAIRES **/

/** \brief Fonction auxiliaire de l'affichage **/
void printBinarySearchTreeAux(SearchTree st, int niveau, int position,
    char *** mot, int * ligne);


/** \brief Affiche le mot et l'équilibre. **/
void printEquilibre (SearchTree st, int niveau, int pos);


/** \brief Comparaison de deux chaînes de caractères. **/
int comp(char * mot1, char * mot2);



#endif
