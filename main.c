#include <stdio.h>
#include <stdlib.h>

#include "ensemble.h"
#include "abr.h"

char * prog;

int main(int argc, char * const argv[])
{
    prog = argv[0];
    (void) argc;
    /*
    OrderedSet test = initOrderedSet();

    test = insertValue(test, 1);
    test = insertValue(test, 3);
    test = insertValue(test, 5);
    test = insertValue(test, 7);
    test = insertValue(test, 9);
    test = insertValue(test, 11);
    test = insertValue(test, 13);
    test = insertValue(test, 15);
    test = insertValue(test, 17);
    test = insertValue(test, 19);
    test = insertValue(test, 21);
    test = insertValue(test, 23);
    test = insertValue(test, 25);
    test = insertValue(test, 27);
    test = insertValue(test, 29);
    test = insertValue(test, 31);
    test = insertValue(test, 33);
    test = insertValue(test, 35);
    test = insertValue(test, 37);

    printOrderedSet(test);

    test = insertValue(test, 20);

    printOrderedSet(test);

    */
/*
    test = insertValue(test, 5);

    printOrderedSet(test);

    printf("L'ensemble a %d elements\n", getNumberElt(test));

    test = insertValue(test, 7);
    printOrderedSet(test);

    //------------------

    OrderedSet test2 = initOrderedSet();
    test2 = insertValue(test2, 3);
    test2 = insertValue(test2, 7);
    test2 = insertValue(test2, 8);
    test2 = insertValue(test2, 11);
    test2 = insertValue(test2, 21);
    test2 = insertValue(test2, 30);

    printf("\n\nTest d'intersection:\nEnsemble 1:\n");
    printOrderedSet(test);
    printf("\nEnsemble 2:\n");
    printOrderedSet(test2);
    printf("\nIntersection:\n");
    OrderedSet intersection = intersect(test, test2);
    printOrderedSet(intersection);

    freeOrderedSet(test);
*/

/*
    SearchTree st = initBinarySearchTree();

    char * mot1 = malloc(5);
    strcpy(mot1,"caca");

    char * mot2 = malloc(5);
    strcpy(mot2,"aaaa");

    char * mot3 = malloc(5);
    strcpy(mot3, "zzzz");

    char * mot4 = malloc(5);
    strcpy(mot4, "gggg");

    st = insert(st, mot1, 1);
    st = insert(st, mot2, 3);
    st = insert(st, mot1, 2);
    st = insert(st, mot3, 6);
    st = insert(st, mot3, 4);
    st = insert(st, mot4, 4);
    st = insert(st, mot2, 1);
    st = insert(st, mot2, 4);

    printBinarySearchTree(st);

    printf("L'arbre contient %d mots differents\n", getNumberString(st));
    printf("L'arbre contient %d mots en total\n", getTotalNumberString(st));

    char *mots[2];
    mots[0] = mot1;
    mots[1] = mot2;
    OrderedSet cooccurences = findCooccurrences(st, mots, 2);
    printf ("Les mots %s et %s apparaissent dans les phrases : ", mot1, mot2);
    printOrderedSet(cooccurences);
    freeOrderedSet(cooccurences);

    mots[0] = mot4;
    mots[1] = mot3;
    cooccurences = findCooccurrences(st, mots, 2);
    printf ("Les mots %s et %s apparaissent dans les phrases : ", mot4, mot3);
    printOrderedSet(cooccurences);
    freeOrderedSet(cooccurences);

    char *mots2[3];
    mots2[0] = mot4;
    mots2[1] = mot2;
    mots2[2] = mot3;
    cooccurences = findCooccurrences(st, mots2, 3);
    printf ("Les mots %s, %s et %s apparaissent dans les phrases : ", mot4, mot2, mot3);
    printOrderedSet(cooccurences);
    freeOrderedSet(cooccurences);

    char *motRecherche = "abaa";
    cooccurences = find(st, motRecherche);
    if (cooccurences == NULL)
        printf ("Le mot %s n'est pas dans une phrase.\n", motRecherche);
    else
    {
        printf("Occurences du mot %s dans les phrases :", motRecherche);
        printOrderedSet(cooccurences);
    }

    freeBinarySearchTree(st);
*/

    SearchTree st = construction_arbre("toto");

    printBinarySearchTree(st);

    freeBinarySearchTree(st);

    return 0;
}
