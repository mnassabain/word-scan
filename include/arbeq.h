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

/** Flag qui indique si le mode UTF-8 est activé **/
extern bool flag_U;


/** \brief Détermine si l'arbre est équilibré où non **/
bool isBalanced(SearchTree st);


/** \brief La profondeur moyenne de chaque noeud de l'arbre **/
double getAverageDepth (SearchTree st);


/** \brief Longueur de cheminement interne **/
double lci (SearchTree st, int hauteur);


/** \brief Rotation gauche **/
SearchTree rotateLeft(SearchTree st);


/** \brief Rotation droite **/
SearchTree rotateRight(SearchTree st);


/** \brief Rotation gauche droite **/
SearchTree rotateLeftRight(SearchTree st);


/** \brief Rotation droite gauche **/
SearchTree rotateRightLeft(SearchTree st);


/** \brief Equilibre l'arbre **/
SearchTree balance(SearchTree st);

/** Construction d'un arbre binaire équilibré **/

/** \brief Renvoie l'équilibre d'un noeud **/
int getEq(SearchTree st);


/** \brief Construction de l'arbre binaire de recherché équilibré à partir
 * d'un fichier. **/
SearchTree construction_arbre(char * filename);


/** \brief Insère un mot dans un AVL **/
SearchTree insavl(SearchTree st, char * mot, int index);

#endif
