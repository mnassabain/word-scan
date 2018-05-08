/**
 * \file more.h
 *
 * Fichier qui contient des fonctions générales utiles
 */

#ifndef __MORE_H__
#define __MORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <unistd.h>
#include "accents.h"


/* =====    MACROS    ===== */

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


/* =====    VARIABLES GLOBALES    ===== */

/** Nom du programme pour l'affichage des erreurs **/
extern char *prog;

extern bool flag_A;    // affiche l'aide
extern bool flag_E;    // isBalanced
extern bool flag_H;    // height
extern bool flag_P;    // avgdepth
extern bool flag_U;    // support UTF-8
extern bool flag_T;    // lancement des jeux de test


/* =====    FONCTIONS    ===== */

/** \brief Gestion des messages d'erreur **/
noreturn void raler (int syserr, const char *fmt, ...);


/** \brief Enlève l'accent de la lettre **/
char transformer_utf8(int c);


/** \brief Teste si le mot contient le caractère x **/
bool contient(char x, char * mot);


/** \brief Fonction interne: transforme un entier en string (char *) **/
char* int_to_string(int nombre);


/** \brief Comparaison de deux chaînes de caractères. **/
int comp(char * mot1, char * mot2);


/** \brief Traiter les arguments données lors l'appel au programme **/
char * traiter_arguments(int argc, char * const argv[]);


#endif
