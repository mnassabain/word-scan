#include "arbeq.h"

bool isBalanced(SearchTree st)
{
    return (st->eq == 0 || st->eq == -1 || st->eq == 1);
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

    free(st);

    return new_st;
}

/**
 * prec: fd non vide
 */
SearchTree rotateLeft(SearchTree st)
{
    SearchTree new_st = enraciner(st->fd->mot, st->fd->positions, st->fd->fd,
        enraciner(st->mot, st->positions, st->fd->fg, st->fg));

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
    SearchTree new_st = rotateLeft(enraciner(st->mot, st->positions,
        rotateRight(st->fd), st->fg));

    free(st);

    return new_st;
}
