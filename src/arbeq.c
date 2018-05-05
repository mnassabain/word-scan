#include "arbeq.h"

#include <wchar.h>


#define ABS(x) ((x)<0 ? -(x) : (x))


bool isBalanced(SearchTree st)
{
    if (vide(st))
        return true;
    return (st->eq == 0 || st->eq == -1 || st->eq == 1) && isBalanced(st->fg) && isBalanced (st->fd);
}

int deseq(SearchTree st)
{
    if (st == NULL)
    {
        return 0;
    }

    return st->eq;
}

int getHeight (SearchTree st)
{
    if (vide (st)) return 0;
    int hauteurFg, hauteurFd;
    hauteurFg = getHeight(st->fg);
    hauteurFd = getHeight(st->fd);
    return MAX(hauteurFg, hauteurFd) + 1;
}

/**
 * prec: fg non vide
 */
 SearchTree rotateRight(SearchTree st)
 {
     SearchTree new_st = enraciner(st->fg->mot, st->fg->positions, st->fg->fg,
         enraciner(st->mot, st->positions, st->fg->fd, st->fd));

     free(st->fg);
     free(st);

     return new_st;
 }

/**
 * prec: fd non vide
 */
SearchTree rotateLeft(SearchTree st)
{
    SearchTree new_st = enraciner(st->fd->mot, st->fd->positions, enraciner(st->mot, st->positions, st->fg, st->fd->fg),
        st->fd->fd);

    free(st->fd);
    free(st);

    return new_st;
}


SearchTree rotateLeftRight(SearchTree st)
{
    SearchTree new_st = rotateRight(enraciner(st->mot, st->positions,
        rotateLeft(st->fg), st->fd));

    free(st);

    return new_st;
}

SearchTree rotateRightLeft(SearchTree st)
{
    st->fd = rotateRight(st->fd);

    SearchTree new_st = enraciner(st->mot, st->positions, st->fg, st->fd);

    new_st = rotateLeft(new_st);


    free(st);

    return new_st;
}


SearchTree balance(SearchTree st)
{
    if (st == NULL)
    {
        return NULL;
    }

    if (vide(st->fg) && vide(st->fd))
    {
        return st;
    }

    int d = deseq(st);

    if (d == 0 || ABS(d) == 1)
    {
        st->fg = balance(st->fg);
        st->fd = balance(st->fd);
    }

    int dg = deseq(st->fg);
    int dd = deseq(st->fd);

    if (d == 2 && dg == 1)
    {
        if (!vide(st->fg))
        {
            st = rotateRight(st);
        }
    }
    else if (d == 2 && dg == -1)
    {
        if (!vide(st->fg) && !vide(st->fg->fd))
        {
            st = rotateLeftRight(st);
        }
    }
    else if (d == -2 && dd == 1)
    {
        if (!vide(st->fd) && !vide(st->fd->fg))
        {
            st = rotateRightLeft(st);
        }
    }
    else if (d == -2 && dd == -1)
    {
        if (!vide(st->fd))
        {
            st = rotateLeft(st);
        }
    }

    return st;
}

// CONSTRUCTION DE L'ARBRE À PARTIR D'UN FICHIER

char separateurs[] = ",:;!?()";

bool contient(char x, char * mot)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (x == mot[i])
        {
            return true;
        }
    }

    return false;
}

#define E_ACC_EGU '\303'

SearchTree construction_arbre(char * filename)
{
    /** Ouverture du fichier **/
    FILE * fichier = fopen(filename, "r");
    if (fichier == NULL)
    {
        raler (1, "erreur fopen %s", filename);
    }

    /** Initlisation de l'arbre de recherche **/
    SearchTree st = initBinarySearchTree();

    /** Parcours du fichier **/
    char buffer[LINE_MAX];
    //short* pt = (short*) buffer;
    short buffer_short[LINE_MAX];
    int phrase = 1;
    while(fgets(buffer, LINE_MAX, fichier) != NULL)
    {

        int k;
        for (k = 0; buffer[k] != '\0'; k++)
        {
            if (buffer[k] >= 0)
            {
                buffer_short[k] = buffer[k];
            }
            else
            {
                short * tmp = (short*) &buffer[k];
                buffer_short[k] = tmp[0];
                k++;
            }
        }
        buffer_short[k] = '\0';

        //char a[2] = "é";
        //printf("%d\n", a[0]);
        //printf("%d\n", a[1]);


        for (k = 0; buffer[k] != '\0'; k++)
        {
            if (buffer[k] == E_ACC_EGU)
            {
                buffer[k] = 'e';
            }
        }

        for (k = 0; buffer_short[k] != '\0'; k++)
        {
            buffer[k] = buffer_short[k];
        }

        int i = 0;
        char *ptBuf = buffer; // pointeur sur le buffer
        while(buffer[i] != '\0')
        {
            int longueur_mot = 0;
            char *mot;

            for (; buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '.'
                && !contient(buffer[i], separateurs); i++)
            {
                if (buffer[i] >= 'A' && buffer[i] <= 'Z')
                {
                    buffer[i] += 32;
                }
                longueur_mot++;
            }
            if (buffer[i] == '.')
                phrase++;

            if (longueur_mot == 0)
            {
                i++;
                ptBuf ++;
                continue;
            }

            mot = (char*) malloc (longueur_mot + 1);
            strncpy(mot, ptBuf, longueur_mot);
            mot[longueur_mot] = '\0';

            st = insavl(st, mot, phrase);
            ptBuf += longueur_mot+1;
            i++;
        }
    }

    if (fclose(fichier) == -1)
    {
        raler(1, "Erreur fclose %s", filename);
    }

    return st;
}


SearchTree insavl(SearchTree st, char * mot, int index)
{
    if (vide(st))
    {
        st = enraciner(mot, insertValue(initOrderedSet(), index), NULL, NULL);
        return st;
    }

    int comparaison = comp(mot, st->mot);
    if (comparaison == 0)
    {
        st->positions = insertValue(st->positions, index);
        free(mot);
    }
    else if (comparaison < 0)
    {
        st->fg = insavl(st->fg, mot, index);
        st->fg->eq = getHeight (st->fg->fg) - getHeight (st->fg->fd);
        st->eq++;
        st = balance(st);
        st->eq = getHeight (st->fg) - getHeight (st->fd);
    }
    else
    {
        st->fd = insavl(st->fd, mot, index);
        st->fd->eq = getHeight (st->fd->fg) - getHeight (st->fd->fd);
        st->eq--;
        st = balance(st);
        st->eq = getHeight (st->fg) - getHeight (st->fd);
    }

    return st;
}
