/**
 * \file erreur.h
 * Fichier qui contient les fonctions et macros pour la gestion d'erreur
 */

#ifndef __ERREUR_H__
#define __ERREUR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdnoreturn.h>

extern char *prog;

noreturn void raler (int syserr, const char *fmt, ...);

#endif
