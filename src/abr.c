#include "abr.h"

SearchTree initBinarySearchTree()
{
    return (SearchTree)NULL;
}

void freeBinarySearchTree(SearchTree st)
{
    if (vide(st))
    {
        return;
    }

    freeBinarySearchTree(st->fg);
    freeBinarySearchTree(st->fd);

    free(st->mot);
    freeOrderedSet(st->positions);

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
    if (vide(st))
    {
        return 0;
    }

    int nb = getTotalNumberString(st->fg) + getTotalNumberString(st->fd);
    return nb + getNumberElt(st->positions);
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
        if (i!=1) freeOrderedSet(indices);
        indices = new_indices;
    }

    return indices;
}


#define GAUCHE 1
#define DROIT  2


char * slash;
char * backslash;
char * tiret;
char * lignel;


typedef char* String;


void printBinarySearchTree(SearchTree st)
{
    if (vide(st))
    {
        return;
    }

    slash = malloc(2);
    strcpy(slash, "/");

    backslash = malloc(2);
    strcpy(backslash, "\\");

    tiret = malloc(2);
    strcpy(tiret, "-");

    lignel = malloc(2);
    strcpy(lignel, "|");


    int nb_lignes = getNumberString(st);

    String ** display = (String**)malloc(nb_lignes * sizeof(String*));
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        display[i] = (String*)malloc(nb_lignes * sizeof(String));
        int j;
        for (j = 0; j < nb_lignes; j++)
        {
            display[i][j] = NULL;
        }
    }
    int ligne = 0;
    printBinarySearchTreeAux(st, 0, 0, display, &ligne);

    /** liens **/

    int j;
    for (i = 0; i < nb_lignes - 1; i++)
    {
        for (j = 0; j < nb_lignes; j++)
        {
            if (display[i][j] == slash && display[i + 1][j] == NULL)
            {
                int k;
                for (k = i + 1; display[k][j] == NULL; k++)
                {
                    display[k][j] = lignel;
                }
            }
        }
    }

    for (i = 1; i < nb_lignes; i++)
    {
        for (j = 0; j < nb_lignes; j++)
        {
            if (display[i][j] == backslash && display[i - 1][j] == NULL)
            {
                int k;
                for (k = i - 1; display[k][j] == NULL; k--)
                {
                    display[k][j] = lignel;
                }
            }
        }
    }

    /** affichage **/
    for (i = 0; i < nb_lignes; i++)
    {
        for (j = 0; j < nb_lignes; j++)
        {
            if (display[i][j] == NULL)
            {
                printf(" ");
            }
            else
            {
                printf("%s", display[i][j]);
            }
        }
        printf("\n");
    }

    free(lignel);
    free(slash);
    free(backslash);
    free(tiret);

    for (i = 0; i < nb_lignes; i++)
    {
        free(display[i]);
    }
    free(display);

}

// fonctions supplémentaires

bool vide(SearchTree st)
{
    return st == NULL;
}


void printBinarySearchTreeAux(SearchTree st, int niveau, int position, String ** display, int * ligne)
{
    if (vide(st))
    {
        return;
    }

    printBinarySearchTreeAux(st->fd, niveau + 1, DROIT, display, ligne);


    if (niveau == 0)
    {
        display[*ligne][0] = st->mot;
        // display[*ligne][1] = to_string(st->positions);
    }
    else
    {
        if (position == DROIT)
        {
            display[*ligne][3*niveau - 3] = slash;
        }
        else
        {
            display[*ligne][3*niveau - 3] = backslash;
        }

        display[*ligne][3*niveau - 2] = tiret;
        display[*ligne][3*niveau - 1] = tiret;
        display[*ligne][3*niveau] = st->mot;
    }

    (*ligne)++;

    printBinarySearchTreeAux(st->fg, niveau + 1, GAUCHE, display, ligne);
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
