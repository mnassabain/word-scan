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
#include <stdnoreturn.h>
#include "accents.h"

extern char *prog;

noreturn void raler (int syserr, const char *fmt, ...);

char transformer_utf8(short c);

#endif
