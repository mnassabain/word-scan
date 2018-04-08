#include <stdio.h>
#include <stdlib.h>

#include "ensemble.h"



int main()
{
    OrderedSet test = initOrderedSet();


    test = insertValue(test, 1);
    test = insertValue(test, 2);
    test = insertValue(test, 3);
    test = insertValue(test, 7);
    test = insertValue(test, 10);
    test = insertValue(test, 21);

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

    return 0;
}
