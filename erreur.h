/**
 * \file erreur.h
 * Fichier qui contient les fonctions et macros pour la gestion d'erreur
 */

#ifndef __ERREUR_H__
#define __ERREUR_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>			// pour les msg d'erreur uniquement
#include <stdlib.h>
#include <string.h>
#include <stdnoreturn.h>		// C norme 2011
#include <sys/wait.h>
#include <errno.h>

extern char *prog;

noreturn void raler (int syserr, const char *fmt, ...);



#endif
