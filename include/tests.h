/**
 * \file tests.h
 * 
 * Fichier qui contient les prototypes des fonctions de test
 * 
 */

#ifndef __TESTS_H__
#define __TESTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* =====    FONCTIONS    ===== */

/** \brief Fonction qui démarre les tests et appele les tests **/
void tests();


/** \brief Jeu de tests pour un ensemble ordonné **/
void testOrderedSet();


/** \brief Jeu de tests pour un arbre binaire de recherche **/
void testABR();


/** \brief Jeu de tests pour la construction de l'arbre **/
void testConstruction();


/** \brief Jeu de tests pour tester l'arbre AVL **/
void testAVL();


/** \brief Jeu de tests pour tester les accents et séparateurs **/
void testAccEtSep();


#endif
