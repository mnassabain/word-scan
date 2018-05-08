/**
 * \file abr.h
 *
 * \brief Fichier qui contient les structures et prototypes de l'arbre binaire.
 *
 */

#ifndef __ABR_H__
#define __ABR_H__

#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "ensemble.h"

extern char * filename;

/* =====    MACROS    ===== */

/** Pour l'affichage de l'arbres **/
#define GAUCHE      1
#define DROIT       2


/* =====    STRUCTURES    ===== */


/** \typedef SearchTree Structure qui réprésente les arbres binaires. **/
typedef struct s_arbre
{
    /** Les données à stocker dans un noeud; le mot **/
    char * mot;

    /** L'ensemble ordonné de ses occurences **/
    OrderedSet positions;

    /** Facteur d'équilibrage **/
    int eq;

    /** Pointeurs vers le fils gauche et le fils droit **/
    struct s_arbre *fg, *fd;

} Noeud, *SearchTree;


/** Utile pour l'affichage **/
typedef char* String;

/* =====    VARIABLES GLOBALES    ===== */

/** Caractères pour l'affichage de l'arbre **/
char * slash;       // "/"
char * backslash;   // "\"
char * tiret;       // "-"
char * lignel;      // "|"
char * deuxpt;      // ":"

/** Variables pour l'affichage de l'arbre **/
String ** display;
String * sets;


/* =====    FONCTIONS    ===== */

/** \brief Initialise un arbre binaire de recherche. **/
SearchTree initBinarySearchTree();


/** \brief Libère un arbre binaire de recherche. **/
void freeBinarySearchTree(SearchTree st);


/** \brief Renvoie la hauteur de l'arbre **/
int getHeight (SearchTree st);


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



/* =====    FONCTIONS SUPPLÉMENTAIRES    ===== */

/** \brief Fonction auxiliaire de l'affichage **/
void printBinarySearchTreeAux(SearchTree st, int niveau, int position,
    int * ligne);


/** \brief Affiche le mot et l'équilibre. **/
void printEquilibre (SearchTree st, int niveau, int pos);



#endif
