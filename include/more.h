/**
 * \file more.h
 *
 * Fichier qui contient les fonctions et macros pour la gestion d'erreur
 */

#ifndef __MORE_H__
#define __MORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include "accents.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

/** Nom du programme pour l'affichage des erreurs **/
extern char *prog;


/** Gestion des messages d'erreur **/
noreturn void raler (int syserr, const char *fmt, ...);


/** brief Enlève l'accent de la lettre **/
char transformer_utf8(int c);


/** Teste si le mot contient le caractère x **/
bool contient(char x, char * mot);


/** \brief Fonction interne: transforme un entier en string (char *) **/
char* int_to_string(int nombre);


/** \brief Comparaison de deux chaînes de caractères. **/
int comp(char * mot1, char * mot2);


#endif
