/**
 * \file ensemble.c
 * définition des fonctions pour la structure des ensembles ordonnées
 */

#include "ensemble.h"


/**
 * \brief Initialise un ensemble ordonné.
 *
 * Alloue la zone de mémoire nécessaire pour l'ensemble
 * On reserve SIZE_TAB entiers au début, et si on a besoin de plus
 * de place on fait realloc de encore SIZE_TAB entiers.
 * Gère les erreurs d'allocation de mémoire.
 *
 * \return nouvelle instance d'ensemble ordonné vide.
 *
 */
OrderedSet initOrderedSet()
{
    OrderedSet newSet = (OrderedSet)malloc(sizeof(struct s_set));
    if (newSet == NULL)
    {
        raler(1, "Erreur lors malloc");
    }

    newSet->max_elt = SIZE_TAB;
    newSet->n_elt   = 0;
    newSet->elements = (int *)malloc(SIZE_TAB * sizeof(int));
    if (newSet->elements == NULL)
    {
        raler(1, "Erreur lors malloc");
    }

    memset(newSet->elements, 0, sizeof(int) * SIZE_TAB);

    return newSet;
}


/**
 * \brief Libération de mémoire occupé par l'ensemble ordonné
 *
 * \param os Ensemble ordonné dont la mémoire on veut liberer
 *
 */
void freeOrderedSet(OrderedSet os)
{
    free(os->elements);
    free(os);
}


/**
 * \brief Renvoie le nombre d'éléments dans l'ensemble.
 *
 * Consulte le champ n_elt qui contient le nombre d'éléments actuel
 * au lieu de faire un parcours de complexité n
 *
 * \param os Ensemble ordonné dont on veut savoir la taille
 *
 * \return Le cardinal de l'ensemble passé en argument
 *
 */
int getNumberElt(OrderedSet os)
{
    return os->n_elt;
}


/**
 * \brief Insere l'élément element dans l'ensemble os
 *
 * Cherche la position par recherche dichotomique.
 * Teste s'il y a débordement de mémoire, si oui fait une reallocation.
 * Teste si l'élément est déjà dans le tableau.
 * Fait decalage du tableau pour rajouter l'élément au bon endroit.
 *
 * \param os Ensemble où on veut rajouter l'élément
 * \param element L'élément qu'on veut ajouter dans l'ensemble
 *
 * \return Ensemble ordonnée après l'ajout
 *
 */
OrderedSet insertValue(OrderedSet os, int element)
{
    int debut   = 0;
    int fin     = os->n_elt - 1;

    if(os->n_elt == 0)
    {
        os->elements[0] = element;
        os->n_elt++;

        return os;
    }

    // si element deja dans l'ensemble
    if (contains(os, element))
    {
        return os;
    }

    int milieu;

    while(debut <= fin)
    {
        milieu = (debut + fin) / 2;

        if (element < os->elements[milieu])
        {
            fin = milieu - 1;
        }
        else
        {
            debut = milieu + 1;
        }
    }

    int position;
    if (element < os->elements[milieu])
    {
        position = milieu;
    }
    else
    {
        position = milieu + 1;
    }


    // decalage du tableau
    if (os->n_elt == os->max_elt)
    {
        int rempli = os->max_elt;
        os->max_elt += SIZE_TAB;
        os->elements = (int *)realloc(os->elements, os->max_elt * sizeof(int));
        if (os->elements == NULL)
        {
            raler(1, "Erreur lors realloc");
        }

        memset(os->elements + rempli, 0, sizeof(int) * SIZE_TAB);
    }

    int tmp = os->n_elt;
    for(; tmp > position; tmp--)
    {
        os->elements[tmp] = os->elements[tmp - 1];
    }

    // insertion
    os->elements[position] = element;
    os->n_elt++;

    return os;
}


/**
 * \brief Teste si un ensemble contient un élément
 *
 * Recherche l'élément par recherche dichotomique
 *
 * \param os L'ensemble ordonné
 * \param element L'élément qu'on cherche
 *
 * \return vrai si l'élément est présent dans l'ensemble, faux sinon
 *
 */
bool contains(OrderedSet os, int element)
{
    int debut   = 0;
    int fin     = os->n_elt;
    bool trouve = false;

    while (!trouve)
    {
        int milieu = (debut + fin) / 2;
        int eltMilieu = os->elements[milieu];

        if (eltMilieu == element)
        {
            trouve = true;
        }
        else
        {
            if (element > eltMilieu)
            {
                debut = milieu + 1;
            }
            else
            {
                fin = milieu - 1;
            }
        }

        // debordement
        if (debut > fin)
        {
            break;
        }
    }

    return trouve;

}


/**
 * \brief Affiche un ensemble ordonné
 *
 * Parcours linéaire pour afficher chaque élément
 *
 * \param os Ensemble ordonné
 *
 */
void printOrderedSet(OrderedSet os)
{
    int i;
    printf("[ ");
    for (i = 0; i < os->n_elt - 1; i++)
    {
        printf("%d, ", os->elements[i]);
    }
    printf("%d ]\n", os->elements[i]);
}


/**
 * \brief Cherche l'intersection de deux ensembles
 *
 * Parcours linéaire du tableau avec le plus petit cardinal
 * puis teste si ces éléments sont présents dans le deuxième
 * ensemble.
 *
 * \param os1 Premier ensemble ordonné
 * \param os2 Deuxième ensemble ordonné
 *
 * \return  Intersection des deux ensembles passés en argument
 *
 */
OrderedSet intersect(OrderedSet os1, OrderedSet os2)
{
    OrderedSet intersection = initOrderedSet();

    int i;
    int max_elt;
    OrderedSet tab[] = {os1, os2};
    int tab_src, tab_dest;
    if(getNumberElt(os1) < getNumberElt(os2))
    {
        max_elt = os1->max_elt;
        tab_src = 0;
        tab_dest = 1;

    }
    else
    {
        max_elt = os2->max_elt;
        tab_src = 1;
        tab_dest = 0;
    }


    for (i = 0; i < max_elt; i++)
    {
        //tab[tab_src]->elements[i] dans tab[tab_dest] ?
        if (contains(tab[tab_dest], tab[tab_src]->elements[i]))
        {
            intersection = insertValue(intersection, tab[tab_src]->elements[i]);
        }
    }

    return intersection;
}

#define MAX_BUFFER 128

char* int_to_string(int nombre)
{
	static char buf[32] = {0};

	int i;
	for(i = 30; nombre > 0 && i > 0 ; --i, nombre /= 10)
	{
		buf[i] = "0123456789abcdef"[nombre % 10];
	}

	return &buf[i+1];
}


char * to_string(OrderedSet os)
{
    int max_buffer = MAX_BUFFER;
    int buffer_size = 0;
    char * buffer = malloc(max_buffer);

    buffer[0] = '[';
    buffer[1] = ' ';

    int i, n_elt = getNumberElt(os);
    int pt = 2;
    for (i = 0; i < n_elt; i++)
    {
        char * nb = int_to_string(os->elements[i]);
        int nb_size = strlen(nb);

        int new_buffer_size = buffer_size + nb_size;
        if (new_buffer_size >= max_buffer)
        {
            max_buffer += MAX_BUFFER;
            buffer = realloc(buffer, max_buffer);
        }

        int j;
        for (j = 0; nb[j] != '\0'; j++, pt++)
        {
            buffer[pt] = nb[j];
        }

        buffer[pt++] = ',';
        buffer[pt++] = ' ';

        buffer_size = new_buffer_size;
    }

    buffer = realloc(buffer, max_buffer + 2);

    buffer[pt - 2] = ' ';
    buffer[pt - 1] = ']';
    buffer[pt] = '\0';
    //buffer[pt-1] = ' ';

    return buffer;
}














////////////
