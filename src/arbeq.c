/**
 * \file arbeq.c
 *
 * Fichier qui implémente les fonctions d'équilibrage de l'arbre, les rotaions
 * et des calculs de hauteur. Il implémente aussi la fonction qui construit
 * l'arbre à partir d'un fichier et l'insertion dans un arbre binaire de
 * recherche équilibré, c'est à dire un AVL.
 *
 */

#include "arbeq.h"


#define ABS(x) ((x)<0 ? -(x) : (x))

/**
 * \brief Détermine si l'arbre est équilibré où non
 *
 * Vérifie si pour chacun des noeuds de l'arbre, le facteur d'équilibrage
 * vaut 1, 0 ou -1.
 *
 * \param st AVL
 *
 * \return Booléen qui vaut true si l'arbre est équilibré, false sinon
 *
 */
bool isBalanced(SearchTree st)
{
    if (vide(st))
        return true;

    if (getEq(st) != 0 && getEq(st) != 1 && getEq(st) != -1)
    {
        return false;
    }

    if (!isBalanced(st->fg))
    {
        return false;
    }

    if (!isBalanced(st->fd))
    {
        return false;
    }

    return true;
}

/**
 * \brief Renvoie l'équilibre d'un noeud
 *
 * Renvoie le facteur d'équilibrage d'un noeud.
 *
 * \param st AVL
 *
 * \return Facteur d'équilibrage du noeud
 *
 */
int getEq(SearchTree st)
{
    if (st == NULL)
    {
        return 0;
    }

    return st->eq;
}


/**
 * \brief La profondeur moyenne de chaque noeud de l'arbre
 *
 * Calcule la profondeur moyenne de chaque noeud en divisant la longeur de
 * cheminement interne avec le nombre de noeuds.
 *
 * \param st Arbre binaire
 *
 * \return La profondeur moyenne de chaque noeud de l'arbre binaire
 *
 */
double getAverageDepth(SearchTree st)
{
    return lci(st, 1) / getNumberString (st);
}

/**
 * \brief Longueur de cheminement interne
 *
 * Calcule la longueur de cheminement interne de l'arbre passé en argument.
 *
 * \param st AVL
 * \param hauteur La hauteur du noeud courrant
 *
 * \return Longueur de cheminement interne de l'arbre
 *
 */
double lci (SearchTree st, int hauteur)
{
    if (vide (st))
    {
        return 0;
    }
    if (vide (st->fg) && vide (st->fd))
    {
        return hauteur;
    }
    return hauteur + lci (st->fg, hauteur+1) + lci (st->fd, hauteur + 1);
}



/**
 * \brief Rotation droite
 *
 * Effectue une rotation simple droite de l'arbre passé en argument.
 * \pre Le fils gauche de l'arbre ne doit pas être vide
 * \param st AVL
 *
 * \return Arbre ayant subit une rotation simple droite
 *
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
 * \brief Rotation gauche
 *
 * Effectue une rotation simple gauche de l'arbre passé en argument.
 * \pre Le fils droit de l'arbre ne doit pas être vide
 * \param st AVL
 *
 * \return Arbre ayant subit une rotation simple gauche
 *
 */
SearchTree rotateLeft(SearchTree st)
{
    SearchTree new_st = enraciner(st->fd->mot, st->fd->positions,
        enraciner(st->mot, st->positions, st->fg, st->fd->fg), st->fd->fd);

    free(st->fd);
    free(st);

    return new_st;
}

/**
 * \brief Rotation gauche droite
 *
 * Effectue une rotation double gauche-droite de l'arbre passé en argument.
 * \pre Le fils gauche de l'arbre ne doit pas être vide, et le fils droit du
 * fils gauche non plus
 * \param st AVL
 *
 * \return Arbre ayant subit une rotation double gauche-droite
 *
 */
SearchTree rotateLeftRight(SearchTree st)
{
    SearchTree new_st = rotateRight(enraciner(st->mot, st->positions,
        rotateLeft(st->fg), st->fd));

    free(st);

    return new_st;
}

/**
 * \brief Rotation droite gauche
 *
 * Effectue une rotation double droite-gauche de l'arbre passé en argument.
 * \pre Le fils droit de l'arbre ne doit pas être vide, et le fils gauche du
 * fils droit non plus
 * \param st AVL
 *
 * \return Arbre ayant subit une rotation double droite-gauche
 *
 */
SearchTree rotateRightLeft(SearchTree st)
{
    st->fd = rotateRight(st->fd);

    SearchTree new_st = enraciner(st->mot, st->positions, st->fg, st->fd);

    new_st = rotateLeft(new_st);


    free(st);

    return new_st;
}

/**
 * \brief Equilibre l'arbre
 *
 * Equilibre l'arbre passé en argument en effectuant les rotations nécessaires
 * \param st AVL
 *
 * \return Arbre équilibré
 *
 */
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

    int d = getEq(st);

    if (d == 0 || ABS(d) == 1)
    {
        st->fg = balance(st->fg);
        st->fd = balance(st->fd);
    }

    int dg = getEq(st->fg);
    int dd = getEq(st->fd);

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


/**
 * \brief Construction de l'arbre binaire de recherché équilibré à partir
 * d'un fichier.
 *
 * Lit le fichier passé en argument et sépare chaque mot pour le stocker
 * dans un arbre binaire de recherche équilibré. Un équilibrage est effectué
 * après chaque insertion si nécéssaire.
 * On considère qu'on mot a été trouvé quand on rencontre un des séparateurs
 * suivants : ",:;!?()" ou un espace.
 * \param filename un nom de fichier
 *
 * \return Arbre binaire de recherche équilibré
 *
 */
SearchTree construction_arbre(char * filename)
{
    /** Séparateurs utilisés lors de la lecture du fichier **/
    char separateurs[] = ",:;!?()";
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

    int phrase = 1;
    while(fgets(buffer, LINE_MAX, fichier) != NULL)
    {
        /** Traitement des accents **/
        if (flag_U)
        {
            int k, l = 0;
            for (k = 0; buffer[k] != '\0';)
            {
               if (buffer[k] >= 0)
               {
                   buffer[l++] = buffer[k++];
               }
               else
               {
                   int new_char = buffer[k] + buffer[k + 1];
                   char char_c = transformer_utf8(new_char);
                   buffer[l++] = char_c;
                   k += 2; 
               }
            }

            buffer[l] = '\0';
        }

        /** Pointeur sur le buffer **/
        char *ptBuf = buffer;

        /** Compteur pour la boucle **/
        int i = 0;
        while(buffer[i] != '\0')
        {
            int longueur_mot = 0;
            char *mot;

            for (; buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '.'
                && !contient(buffer[i], separateurs); i++)
            {
                if (buffer[i] == '\'')
                {
                    ptBuf += longueur_mot + 1;
                    longueur_mot = 0;
                    continue;
                }
                else if (buffer[i] >= 'A' && buffer[i] <= 'Z')
                {
                    buffer[i] += 'a'-'A';
                }
                longueur_mot++;
            }

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
            if (buffer[i] == '.')
                phrase++;
            i++;
        }
    }

    if (fclose(fichier) == -1)
    {
        raler(1, "Erreur fclose %s", filename);
    }

    return st;
}

/**
 * \brief Insère un mot dans un AVL
 *
 * Insère un mot à la bonne position dans un AVL s'il n'y est pas déjà et crée
 * un ensemble ordonné qui contient le numéro de la phrase dans laquelle le mot
 * a été trouvé. Si le mot était déjà dans l'arbre alors le numéro de la phrase
 * contenant le mot est rajouté dans l'ensemble ordonné des numéros de phrase.
 * \param st AVL
 * \param mot Le mot que l'on veut insérer dans l'arbres
 * \param index Le numéro de phrase dans laquelle se trouve le mot
 *
 * \return Arbre binaire de recherche équilibré
 *
 */
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
