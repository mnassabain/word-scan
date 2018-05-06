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

/**
 * 
 * 
 */
noreturn void raler (int syserr, const char *fmt, ...);


/**
 * \brief Enlève l'accent de la lettre
 * 
 * Transforme le short en char en enlèvant l'accent.
 * 
 * \param c Lettre à transformer.
 * 
 * \return Caractère sans accent sous forme de char
 * 
 */
char transformer_utf8(short c);


/**
 * 
 * 
 */
bool contient(char x, char * mot);



#endif