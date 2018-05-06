#include <stdio.h>
#include <stdlib.h>

#include "ensemble.h"
#include "abr.h"
#include "arbeq.h"
#include "accents.h"
#include "more.h"
#include "tests.h"

char * prog;

void tests(){
    testOrderedSet();
    testAVL();
}


void testOrderedSet()
{
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
}

void testAVL ()
{
///////////////// TEST ROTATION GAUCHE /////////////////////////////////////////
    printf("[32m################### TESTING: rotation gauche[0m\n");
    SearchTree stRG = initBinarySearchTree();

    char * mot1 = malloc(5);
    char * mot2 = malloc(5);
    char * mot3 = malloc(5);

    strcpy(mot1, "aaaa");
    strcpy(mot2, "bbbb");
    strcpy(mot3, "cccc");

    printf("Insertion du mot %s\n", mot1);
    stRG = insavl(stRG, mot1, 1);
    printf("Insertion du mot %s\n", mot2);
    stRG = insavl(stRG, mot2, 1);
    printf("Insertion du mot %s\n", mot3);
    stRG = insavl(stRG, mot3, 1);

    printf("Affichage de l'arbre:\n\n");
    printBinarySearchTree(stRG);
    freeBinarySearchTree(stRG);
////////////////////////////////////////////////////////////////////////////////

///////////////// TEST ROTATION DROITE /////////////////////////////////////////
    printf("[32m################### TESTING: rotation droite[0m\n");
    SearchTree stRD = initBinarySearchTree();

    mot1 = malloc(5);
    mot2 = malloc(5);
    mot3 = malloc(5);

    strcpy(mot1, "cccc");
    strcpy(mot2, "bbbb");
    strcpy(mot3, "aaaa");

    printf("Insertion du mot %s\n", mot1);
    stRD = insavl(stRD, mot1, 1);
    printf("Insertion du mot %s\n", mot2);
    stRD = insavl(stRD, mot2, 1);
    printf("Insertion du mot %s\n", mot3);
    stRD = insavl(stRD, mot3, 1);

    printf("Affichage de l'arbre:\n\n");
    printBinarySearchTree(stRD);
    freeBinarySearchTree(stRD);
////////////////////////////////////////////////////////////////////////////////

///////////////// TEST ROTATION GAUCHE DROITE //////////////////////////////////
    printf("[32m################### TESTING: rotation double gauche-droite[0m\n");
    SearchTree stRGD = initBinarySearchTree();

    mot1 = malloc(5);
    mot2 = malloc(5);
    mot3 = malloc(5);

    strcpy(mot1, "cccc");
    strcpy(mot2, "aaaa");
    strcpy(mot3, "bbbb");

    printf("Insertion du mot %s\n", mot1);
    stRGD = insavl(stRGD, mot1, 1);
    printf("Insertion du mot %s\n", mot2);
    stRGD = insavl(stRGD, mot2, 1);
    printf("Insertion du mot %s\n", mot3);
    stRGD = insavl(stRGD, mot3, 1);

    printf("Affichage de l'arbre:\n\n");
    printBinarySearchTree(stRGD);
    freeBinarySearchTree(stRGD);
////////////////////////////////////////////////////////////////////////////////

///////////////// TEST ROTATION DROITE GAUCHE //////////////////////////////////
    printf("[32m################### TESTING: rotation double droite-gauche[0m\n");
    SearchTree stRDG = initBinarySearchTree();

    mot1 = malloc(5);
    mot2 = malloc(5);
    mot3 = malloc(5);

    strcpy(mot1, "aaaa");
    strcpy(mot2, "cccc");
    strcpy(mot3, "bbbb");

    printf("Insertion du mot %s\n", mot1);
    stRDG = insavl(stRDG, mot1, 1);
    printf("Insertion du mot %s\n", mot2);
    stRDG = insavl(stRDG, mot2, 1);
    printf("Insertion du mot %s\n", mot3);
    stRDG = insavl(stRDG, mot3, 1);

    printf("Affichage de l'arbre:\n\n");
    printBinarySearchTree(stRDG);
    freeBinarySearchTree(stRDG);
////////////////////////////////////////////////////////////////////////////////

///////////////// TESTS FONCTIONS SUR ARBRE ////////////////////////////////////
    printf("[32m################### TESTING: fonctions sur arbre initialisé avec foo.txt[0m\n");
    SearchTree stFile = construction_arbre("foo.txt");

    printf("Equilibre de l'arbre: ");
    printEquilibre(stFile, 0, 0);

    printBinarySearchTree(stFile);

    printf("L'arbre contient %d mots differents\n", getNumberString(stFile));
    printf("L'arbre contient %d mots au total\n", getTotalNumberString(stFile));
    printf("Profondeur moyenne des noeuds de l'arbre : %f\n", getAverageDepth(stFile));

    char *mots[2];
    mots[0] = "foo";
    mots[1] = "bar";
    OrderedSet cooccurences = findCooccurrences(stFile, mots, 2);
    printf ("Les mots %s et %s apparaissent dans les phrases : ", mots[0], mots[1]);
    printOrderedSet(cooccurences);
    freeOrderedSet(cooccurences);

    mots[0] = "grault";
    mots[1] = "foo";
    cooccurences = findCooccurrences(stFile, mots, 2);
    printf ("Les mots %s et %s apparaissent dans les phrases : ", mots[0], mots[1]);
    printOrderedSet(cooccurences);
    freeOrderedSet(cooccurences);

    char *motRecherche = "abaa\0";
    cooccurences = find(stFile, motRecherche);
    if (cooccurences == NULL)
        printf ("Le mot %s n'est pas dans une phrase.\n", motRecherche);
    else
    {
        printf("Occurences du mot %s dans les phrases :", motRecherche);
        printOrderedSet(cooccurences);
    }

    bool b = isBalanced(stFile);
    printf("L'arbre est-il équilibré? %s\n", (b) ? "oui" : "non");

    freeBinarySearchTree(stFile);
}
