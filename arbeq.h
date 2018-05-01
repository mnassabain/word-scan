#ifndef __ARBEQ_H__
#define __ARBEQ_H__

#include <stdbool.h>
#include "abr.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

bool isBalanced(SearchTree st);

int getHeight (SearchTree st);

int getAverageDepth (SearchTree st);

SearchTree rotateLeft(SearchTree st);

SearchTree rotateRight(SearchTree st);

SearchTree rotateLeftRight(SearchTree st);

SearchTree rotateRightLeft(SearchTree st);

#endif
