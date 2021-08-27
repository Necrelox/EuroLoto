/*
** Author : Necrelox
** ech_twister
** File description:
** My Interpretation of pseudo code Mersen Twister MT19937
*/

#include "ech_twister.h"

unsigned long ech_genRandom(ECHMT_S *ech)
{
    static unsigned long mag[2] = {0x0, A};
    unsigned long y, i;

    if (ech->index >= N || ech->index < 0) {
        for (i = 0; i < N - M; ++i) {
            y = (ech->dimension[i] & UP_MASK) | (ech->dimension[i+1] & LOW_MASK);
            ech->dimension[i] = ech->dimension[i + M] ^ (y >> 1) ^ mag[y & 0x1];
        }
        for (;i < N - 1; ++i) {
            y = (ech->dimension[i] & UP_MASK) | (ech->dimension[i+1] & LOW_MASK);
            ech->dimension[i] = ech->dimension[i + (M - N)] ^ (y >> 1) ^ mag[y & 0x1];
        }
        y = (ech->dimension[N - 1] & UP_MASK) | (ech->dimension[0] & LOW_MASK);
        ech->dimension[N - 1] = ech->dimension[M - 1] ^ (y >> 1) ^ mag[y & 0x1];
        ech->index = 0;
    }
    y = ech->dimension[ech->index++];
    REGISTER_SHIFTER(y)
    return y;
}

ECHMT_S ech_seedRand(int seed)
{
    ECHMT_S ech;
    ech.dimension[0] = seed & 0xffffffff;

    for (ech.index = 1; ech.index < N; ++ech.index)
        ech.dimension[ech.index] = (6969 * (ech.dimension[ech.index - 1])) & 0xffffffff;
    return ech;
}
