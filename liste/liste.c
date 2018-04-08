#include "liste.h"
#include "erreur.h"

OrderedSet initOrderedSet()
{
    return NULL;
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
    if (os == NULL) {
        OrderedSet newOs = (OrderedSet) malloc (sizeof(struct s_OrderedSet));
        if (newOs == NULL) raler(1, "erreur malloc newOs");
        newOs->first = (elemListe) malloc (sizeof(struct s_elt));
        if (newOs->first == NULL) raler(1, "erreur malloc newOs->first");
        newOs->first->val = element;
        newOs->first->suiv = NULL;
        newOs->n_elt = 1;
        return newOs;
    }
    if (contains(os->first, element)) return os;
    elemListe pos = searchPos(os->first, element);
    elemListe newElt = (elemListe) malloc (sizeof(struct s_elt));
    newElt->val = element;
    newElt->suiv = pos->suiv;
    pos->suiv = newElt;
    os->n_elt ++;
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
            printf("%d ",elt->val);
        else
            printf(",%d ",elt->val);
        elt = elt->suiv;
    }
    printf("]");
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
        if (contains(big, elt))
            intersection = insertOrderedSet(intersection, elt);
    }
    return intersection;
}

elemListe searchPos(elemListe liste, int element)
{
    elemListe elt = liste;
    elemListe save;
    while (elt->val < element)
    {
        save = elt;
        elt = elt->suiv;
    }
    return save;
}
