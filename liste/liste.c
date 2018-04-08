#include "liste.h"
#include "erreur.h"

OrderedSet initOrderedSet()
{
    OrderedSet newOs = (OrderedSet) malloc (sizeof(struct s_OrderedSet));
    if (newOs == NULL) raler(1, "erreur malloc newOs");
    newOs->first = NULL;
    newOs->n_elt = 0;
    return newOs;
}

void freeOrderedSet(OrderedSet os)
{
    // libération de la liste
    elemListe elt = os->first;
    elemListe save;
    while (elt != NULL)
    {
        save = elt;
        elt = elt->suiv;
        free(save);
    }
    //libération de l'ensemble ordonné
    free(os);
}

int getNumberElt(OrderedSet os)
{
    return os->n_elt;
}

OrderedSet insertValue(OrderedSet os, int element)
{
    if (os->first == NULL) {
        os->first = (elemListe) malloc (sizeof(struct s_elt));
        if (os->first == NULL) raler(1, "erreur malloc newOs->first");
        os->first->val = element;
        os->first->suiv = NULL;
        os->n_elt ++;
        return os;
    }
    if (contains(os, element)) return os;
    elemListe pos = searchPos(os->first, element);
    elemListe newElt = (elemListe) malloc (sizeof(struct s_elt));
    newElt->val = element;
    newElt->suiv = pos->suiv;
    pos->suiv = newElt;
    os->n_elt ++;
    return os;
}

bool contains(OrderedSet os, int element)
{
    elemListe elt = os->first;
    int i;
    for (i = 0; i < os->n_elt; i++, elt=elt->suiv)
    {
        if (elt->val == element)
            return true;
    }
    return false;
}

void printOrderedSet(OrderedSet os)
{
    elemListe elt = os->first;
    bool first = true;
    printf("[");
    while (elt != NULL)
    {
        if (first)
        {
            printf("%d",elt->val);
            first = false;
        }
        else
        {
            printf(", %d",elt->val);
        }
        elt = elt->suiv;
    }
    printf("]\n");
}

OrderedSet intersect(OrderedSet os1, OrderedSet os2)
{
    OrderedSet intersection = initOrderedSet();
    OrderedSet small, big;
    if (os1->n_elt < os2->n_elt)
    {
        small = os1;
        big = os2;
    }
    else
    {
        small = os2;
        big = os1;
    }
    elemListe elt = big->first;
    int i;
    for (i = 0; i < big->n_elt; i++, elt=elt->suiv)
    {
        if (contains(small, elt->val))
            intersection = insertValue(intersection, elt->val);
    }
    return intersection;
}

elemListe searchPos(elemListe liste, int element)
{
    elemListe elt = liste;
    elemListe save = elt;
    while ((elt != NULL) && (elt->val < element))
    {
        save = elt;
        elt = elt->suiv;
    }
    return save;
}
