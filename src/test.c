#include "ensemble.h"
#include "abr.h"
#include "arbeq.h"
#include "accents.h"
#include "more.h"
#include "tests.h"

char * prog;

void tests(){
    testOrderedSet();
    testABR();
    testConstruction();
    testAVL();
}


void testOrderedSet()
{
    printf("[32m################### TESTING: Partie 1: ensemble ordonné[0m\n");
    OrderedSet testOs = initOrderedSet();

    srand(time(NULL));
    int i, r;
    printf("Insertion de 10 entiers aléatoires entre 0 et 20 dans un ensemble ordonné:\n");
    for (i = 0; i < 10; i++)
    {
        r = rand() % 20;
        printf("Insertion de l'entier %d.\n", r);
        testOs = insertValue(testOs, r);
    }
    printf("Ensemble ordonné :\n");
    printOrderedSet(testOs);
    printf("L'ensemble a %d elements.\n", getNumberElt(testOs));

    printf("\nInsertion de la valeur 10.\n");
    testOs = insertValue(testOs, 10);

    printf("Ensemble ordonné :\n");
    printOrderedSet(testOs);

    printf("\nInsertion de la valeur 5.\n");
    testOs = insertValue(testOs, 5);

    printf("Ensemble ordonné :\n");
    printOrderedSet(testOs);

    printf("L'ensemble a %d elements.\n", getNumberElt(testOs));
    printf("L'ensemble contient t'il 10 ? %s\n", contains(testOs, 10) ? "oui" : "non");

    //------------------

    OrderedSet testOs2 = initOrderedSet();
    testOs2 = insertValue(testOs2, 3);
    testOs2 = insertValue(testOs2, 7);
    testOs2 = insertValue(testOs2, 8);
    testOs2 = insertValue(testOs2, 11);
    testOs2 = insertValue(testOs2, 21);
    testOs2 = insertValue(testOs2, 30);

    printf("\nTest d'intersection:\n");
    printf("Ensemble 1:\n");
    printOrderedSet(testOs);
    printf("Ensemble 2:\n");
    printOrderedSet(testOs2);
    printf("\nIntersection:\n");
    OrderedSet intersection = intersect(testOs, testOs2);
    printOrderedSet(intersection);

    freeOrderedSet(testOs);
    printf("[32m################### TESTING: fin tests ensemble ordonné[0m\n\n");
}

void testABR()
{
    printf("[32m################### TESTING: Partie 2: Arbre binaire de recherche[0m\n");
    printf("Test fonctions sur arbre initialisé avec texte/foo.txt\n");

    SearchTree stFile = initBinarySearchTree();
    stFile = construction_arbre("texte/foo.txt");

    printf("Affichage de l'arbre créé avec foot.txt\n");
    printBinarySearchTree(stFile);
    printf("L'arbre contient %d mots differents.\n\n", getNumberString(stFile));

    printf("Equilibre de l'arbre:\n");
    printEquilibre(stFile, 0, 0);
    printf("\n");

    printf("Rajout du mot 'projet' dans l'arbre à l'index 3.\n");
    char * mot = malloc (7);
    strcpy(mot, "projet");
    stFile = insavl(stFile, mot, 3);

    printf("\nNouvel arbre:\n");
    printBinarySearchTree(stFile);

    printf("L'arbre contient %d mots differents\n", getNumberString(stFile));
    printf("L'arbre contient %d mots au total\n", getTotalNumberString(stFile));
    printf("Profondeur moyenne des noeuds de l'arbre : %f\n", getAverageDepth(stFile));

    char *mots[3];
    mots[0] = "foo";
    mots[1] = "bar";
    OrderedSet cooccurences = findCooccurrences(stFile, mots, 2);
    printf ("Les mots %s et %s apparaissent dans les phrases : ", mots[0], mots[1]);
    printOrderedSet(cooccurences);
    freeOrderedSet(cooccurences);

    mots[0] = "waldo";
    mots[1] = "foo";
    mots[2] = "grault";
    cooccurences = findCooccurrences(stFile, mots, 3);
    printf ("Les mots %s, %s et %s apparaissent dans les phrases : ", mots[0], mots[1], mots[2]);
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

    freeBinarySearchTree(stFile);
    printf("[32m################### TESTING: fin tests arbre binaire de recherche[0m\n\n");
}

void testConstruction()
{
    printf("[32m################### TESTING: Partie 3: Construction de l'arbre[0m\n");
    SearchTree stFile = initBinarySearchTree();
    printf("Arbre initialisé avec texte/texte.txt qui contient 500 mots de lorem ipsum.\n");
    stFile = construction_arbre("texte/texte.txt");

    printBinarySearchTree(stFile);


    printf("L'arbre contient %d mots differents\n", getNumberString(stFile));
    printf("Profondeur moyenne des noeuds de l'arbre : %f\n", getAverageDepth(stFile));

    freeBinarySearchTree(stFile);
    printf("[32m################### TESTING: fin tests construction de l'arbre[0m\n\n");
}

void testAVL ()
{
///////////////// TEST ROTATION GAUCHE /////////////////////////////////////////
    printf("[32m################### TESTING: Partie 4: AVL[0m\n");
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
    printf("Test fonctions sur arbre initialisé avec foo.txt\n");

    SearchTree stFile = initBinarySearchTree();
    stFile = construction_arbre("texte/foo.txt");

    bool b = isBalanced(stFile);
    printf("L'arbre est-il équilibré ? %s\n", (b) ? "oui" : "non");

    freeBinarySearchTree(stFile);
////////////////////////////////////////////////////////////////////////////////
}
