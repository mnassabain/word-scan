/**
 * \file abr.c
 *
 * Fichier qui implémente les fonctions basiques pour la structure de l'arbre
 * binaire de recherche.
 *
 */

#include "abr.h"

extern char * filename;

/**
 * \brief Intialise un arbre binaire de recherche.
 *
 * \return  Arbre binaire vide.
 *
 */
SearchTree initBinarySearchTree()
{
    return (SearchTree)NULL;
}


/**
 * \brief Libère un arbre binaire de recherche.
 *
 * Parcours l'arbre binaire et ses fils pour libérer la mémoire occupée par eux.
 *
 * \param st Arbre binaire à libérer.
 *
 */
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


/**
 * \brief Renvoie la hauteur de l'arbre
 *
 * Renvoie la hauteur de l'arbre passé en argument.
 * \param st AVL
 *
 * \return Hauteur de l'arbre
 *
 */
int getHeight (SearchTree st)
{
    if (vide (st)) return 0;
    int hauteurFg, hauteurFd;
    hauteurFg = getHeight(st->fg);
    hauteurFd = getHeight(st->fd);
    return MAX(hauteurFg, hauteurFd) + 1;
}


/**
 * \brief Trouver le nombre de mots dans l'arbre (noeuds)
 *
 * Fonction récursive qui calcule le nombre de mots en comptant les noueds de
 * l'arbre.
 *
 * \param st Arbre binaire dont on veut savoir le nombre de mots
 *
 * \return  Nombre de mots contenus dans l'arbre binaire.
 *
 */
int getNumberString(SearchTree st)
{
    if (vide(st))
    {
        return 0;
    }

    int nb = getNumberString(st->fg) + getNumberString(st->fd);
    return nb + 1;
}


/**
 * \brief Cherche le nombre de mots total dans l'arbre
 *
 * Parcours l'arbre et compte le nombre de mots ainsi que leur nombre
 * d'occurences pour calculer le nombre de mots dans le texte source.
 *
 * \param st Arbre binaire
 *
 * \return  Nombre de mots total dans l'arbre binaire
 *
 */
int getTotalNumberString(SearchTree st)
{
    if (vide(st))
    {
        return 0;
    }

    int nb = getTotalNumberString(st->fg) + getTotalNumberString(st->fd);
    return nb + getNumberElt(st->positions);
}


/**
 * \brief Comparaison de deux chaînes de caractères.
 *
 * \param mot1
 * \param mot2
 *
 * \return  Résultat de la comparaison.
 *
 */
int comp(char *mot1, char *mot2)
{
    return strcmp(mot1, mot2);
}


/**
 * \brief Cherche un mot dans un arbre binaire de recherche
 *
 * Parcours l'arbre binaire de recherche. Si on trouve le mot on renvoie un
 * pointeur sur son ensemble ordonné de positions. Si on ne le trouve pas la
 * fonction renvoie NULL.
 *
 * \param st Arbre binaire
 * \param mot Mot qu'on cherche dans l'arbre binaire
 *
 * \return Ensemble de positions de l'élément si trouvé, NULL sinon.
 *
 */
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


/**
 * \brief Cherche les positions communes des mots données en argument
 *
 * Parcours l'arbre binaire pour trouver le mots cherchés. Pour chaque mot
 * trouvé fait l'intersection de leurs occurences.
 *
 * \param st Arbre binaire
 * \param mots Liste des mots
 * \param nbMots Nombre de mots dans la liste de mots
 *
 * \return Un ensemble ordonné de les occurences communes des mots données.
 *
 */
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


/**
 * \brief Teste si l'arbre binaire est vide
 *
 * \param st Arbre binaire

 * \return true si l'arbre est vide, false sinon
 *
 */
bool vide(SearchTree st)
{
    return st == NULL;
}


#define GAUCHE 1
#define DROIT  2


char * slash;
char * backslash;
char * tiret;
char * lignel;
char * deuxpt;


typedef char* String;

String ** display;
String * sets;


/**
 * \brief Affiche l'arbre binaire donné
 *
 * Parcours infixé de l'arbre binaire. Crée un tableau de deux dimensions de
 * chaînes de caractères. Remplit ce tableau avec soit NULL (espace), soit
 * un mot ou un caractère à affichier. Permet un affichage clair et plus
 * visible.
 *
 * \param st Arbre binaire à afficher
 *
 */
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

    deuxpt = malloc(2);
    strcpy(deuxpt, ":");


    int nb_lignes = getNumberString(st);
    int nb_colonnes = getHeight(st) * 3 + 1;

    nb_lignes *= 2;/////

    display = (String**)malloc(nb_lignes * sizeof(String*));
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        display[i] = (String*)malloc(nb_colonnes * sizeof(String));
        int j;
        for (j = 0; j < nb_colonnes; j++)
        {
            display[i][j] = NULL;
        }
    }

    sets = (String*)malloc((nb_lignes/2) * sizeof(String));

    int ligne = 0;
    printBinarySearchTreeAux(st, 0, 0, &ligne);

    /** liens **/

    int j;
    for (i = 0; i < nb_lignes - 1; i++)
    {
        for (j = 0; j < nb_colonnes; j++)
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
        for (j = 0; j < nb_colonnes; j++)
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
        for (j = 0; j < nb_colonnes; j++)
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
    free(deuxpt);

    for (i = 0; i < nb_lignes; i++)
    {
        free(display[i]);
    }
    free(display);

    for (i = 0; i < nb_lignes / 2; i++)
    {
        free(sets[i]);
    }
    free(sets);
}



/**
 * \brief Fonction auxiliaire de l'affichage
 *
 * Remplit le tableau (display) mentionné précedamment par les mots dans
 * l'arbre.
 *
 * \param st Arbre binaire à afficher
 * \param niveau ou la profondeur à afficher (racine est au niveau 0)
 * \param position Racine, gauche ou droit
 * \param display Le tableau d'affichage à remplir
 * \param ligne Le nombre de ligne dans le display actuel
 *
 */
void printBinarySearchTreeAux(SearchTree st, int niveau, int position, 
    int * ligne)
{
    if (vide(st))
    {
        return;
    }

    printBinarySearchTreeAux(st->fd, niveau + 1, DROIT, ligne);


    if (niveau == 0)
    {
        display[*ligne][0] = st->mot;
        display[*ligne][1] = deuxpt;
        display[*ligne][3] = to_string(st->positions);
        sets[(*ligne)/2] = display[*ligne][3];
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
        display[*ligne][3*niveau + 1] = deuxpt;
        display[*ligne][3*niveau + 3] = to_string(st->positions);
        sets[(*ligne)/2] = display[*ligne][3*niveau + 3];
    }

    (*ligne) += 2;

    printBinarySearchTreeAux(st->fg, niveau + 1, GAUCHE, ligne);
}


/**
 * \brief Affiche le mot et l'équilibre.
 *
 * Fonction sert à tester l'équilibraque de l'arbre binaire de recherche.
 *
 * \param st Arbre binaire à afficher
 *
 */
void printEquilibre (SearchTree st, int niveau, int pos)
{
    if (vide(st))
    {
        return;
    }
    if (niveau == 0){
        printf("%s eq = %d\n", st->mot, st->eq);
    }
    else
    {
        int i;
        for (i = 0; i < niveau-1; i++)
        {
            printf("%*s", 4, "");
        }
        if (pos ==GAUCHE)
            printf("|--fg: ");
        else
            printf("|--fd: ");
        printf("%s | eq = %d\n", st->mot, st->eq);
    }

    printEquilibre(st->fg, niveau + 1, GAUCHE);
    printEquilibre(st->fd, niveau + 1, DROIT);
}


/**
 * \brief Constructeur de base de l'arbre binaire
 *
 * Crée un nouveau noeud, le remplit avec les données passées en argument et le
 * lie aux deux arbres données en argument.
 *
 * \param mot Mot à rajouter dans la structure de noeud
 * \param positions Ensemble ordonné des occurences à rajouter dans le noeud
 * \param st1 Arbre binaire qui devient le fils gauche du nouveau noeud
 * \param st2 Arbre binaire qui devient le fils droit du noveau noeud
 *
 * \return L'arbre binaire nouveau
 *
 */
SearchTree enraciner(char *mot, OrderedSet positions, SearchTree st1, SearchTree st2)
{
    SearchTree racine = (SearchTree)malloc(sizeof(*racine));

    racine->mot = mot;
    racine->positions = positions;
    racine->eq = 0;
    racine->fg = st1;
    racine->fd = st2;

    return racine;
}
