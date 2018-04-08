#include "ensemble.h"

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

    return newSet;
}

void freeOrderedSet(OrderedSet os)
{
    free(os->elements);
    free(os);
}

int getNumberElt(OrderedSet os)
{
    return os->n_elt;
}

OrderedSet insertValue(OrderedSet os, int element)
{
    int debut   = 0;
    int fin     = os->n_elt;
    bool inf, sup;

    // si element deja dans l'ensemble
    if (contains(os, element))
    {
        return;
    }

    // recherche dichotomique
    while(!sup || !inf)
    {
        int milieu = (debut + fin) / 2;

        if (element < os->elements[milieu]);
        {
            inf = true;
        }
        else
        {
            sup = true;
        }

        if (inf)
        {
            fin = milieu - 1;
        }

        if (sup)
        {
            debut = milieu + 1;
        }
    }

    // insertion
    int position;
    if (element < os->elements[milieu])
    {
        position = milieu - 1;
    }
    else
    {
        position = milieu + 1;
    }

    // decalage du tableau
    if (os->n_elt == os->max_elt)
    {
        os->max_elt += SIZE_TAB;
        os->elements = (int *)realloc(os->elements, os->max_elt);
    }

    int tmp = os->n_elt;
    while(tmp-- > position)
    {
        os->elements[tmp] = os->elements[tmp - 1];
    }

    // insertion
    os->elements[milieu] = element;
    os->n_elt++;

    return os;
}

bool contains(OrderedSet os, int element)
{
    int debut   = 0;
    int fin     = os->n_elt;
    bool trouve = false;

    while (!trouve && nontrouve)
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

void printOrderedSet(OrderedSet os)
{
    int i;
    printf("[ ");
    for (i = 0; i < os->n_elt - 1; i++)
    {
        printf("%d, ", os->elements[i]);
    }
    printf("%d ]", os->elements[i]);
}

OrderedSet intersect(OrderedSet os1, OrderedSet os2)
{
    OrderedSet intersection = initOrderedSet();

    int i;
    int max_elt;
    OrderedSet tab[] = {os1, os2};
    int tab_src, tab_dest;
    if(getNumberElt(os1) < getNumberElt(os2))
    {
        max_elt = os1;
        tab_src = 0;
        tab_dest = 1;

    }
    else
    {
        max_elt = os2;
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
