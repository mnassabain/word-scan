#include "abr.h"

SearchTree initBinarySearchTree()
{
    return (SearchTree)NULL;
}

void freeBinarySearchTree(SearchTree st)
{
    if (st == NULL)
    {
        return;
    }

    free(st->mot);
    freeOrderedSet(st->positions);

    freeBinarySearchTree(st->fg);
    freeBinarySearchTree(st->fd);

    free(st);
}

int getNumberString(SearchTree st)
{
    if (vide(st))
    {
        return 0;
    }

    int nb = getNumberString(st->fg) + getNumberString(st->fd);
    return nb + 1;
}

int getTotalNumberString(SearchTree st)
{
    (void) st;
    return 0;
}

SearchTree insert(SearchTree st, char *mot, int index)
{
    OrderedSet mot_os;
    if (st == NULL)
    {
        st = (SearchTree) malloc (sizeof(struct s_arbre));
        if (st == NULL)
        {
            raler(1, "Erreur lors malloc");
        }

        st->mot = mot;
        st->positions = initOrderedSet();
        st->positions = insertValue(st->positions, index);

        return st;
    }

    if ((mot_os = find(st, mot)) == NULL)
    {
        SearchTree g, d;
        g = d = NULL;
        coupure(st, mot, g, d);
        OrderedSet os = initOrderedSet();
        os = insertValue(os, index);
        enraciner(mot, os, g, d);
    }
    else
    {
        mot_os = insertValue (mot_os, index);
    }

    return st;
}

int comp(char *mot1, char *mot2)
{
    return strcmp(mot1, mot2);
}

OrderedSet find(SearchTree st, char *mot)
{
    if (vide(st))
    {
        return NULL;
    }

    int comparaison = comp(mot, st->mot);
    if (comparaison == 0)
    {
        return st->positions;
    }
    else if (comparaison < 0)
    {
        return find(st->fg, mot);
    }
    else
    {
        return find(st->fd, mot);
    }
}

OrderedSet findCooccurrences(SearchTree st, char ** mots, int nbMots)
{
    OrderedSet indices = find (st, mots[0]);
    int i;
    for (i = 1; i < nbMots; i++)
    {
        OrderedSet new_indices = intersect (indices, find (st, mots[i]));
        freeOrderedSet(indices);
        indices = new_indices;
    }

    return indices;
}


void printBinarySearchTree(SearchTree st)
{
    printBinarySearchTreeAux(st, 0);
}

// fonctions supplémentaires

bool vide(SearchTree st)
{
    return st == NULL;
}


void printBinarySearchTreeAux(SearchTree st, int niveau)
{
    if (vide(st))
        return;

    printf("%*s%s ", niveau, "", st->mot);
    printOrderedSet(st->positions);
    printf("\n");

    printBinarySearchTreeAux(st->fg, niveau + 1);
    printBinarySearchTreeAux(st->fd, niveau + 1);
}


SearchTree enraciner(char *mot, OrderedSet positions, SearchTree st1, SearchTree st2)
{
    SearchTree racine = (SearchTree)malloc(sizeof(*racine));

    racine->mot = mot;
    racine->positions = positions;

    racine->fg = st1;
    racine->fd = st2;

    return racine;
}


void coupure(SearchTree st, char *mot, SearchTree g, SearchTree d)
{
    if (vide(st))
    {
        g = d = NULL;
        return;
    }

    int comparaison = comp(mot, st->mot);
    if (comparaison == 0)
    {
        g = enraciner(mot, st->positions, st->fg, initBinarySearchTree());
        d = st->fd;
    }
    else if(comparaison < 0)
    {
        coupure(st->fg, mot, g, d);
        d = enraciner(st->mot, st->positions, d, st->fd);
    }
    else
    {
        coupure(st->fd, mot, g, d);
        g = enraciner(st->mot, st->positions, st->fg, g);
    }
}
