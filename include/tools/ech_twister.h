/*
** Author : Necrelox
** ech_twister
** File description:
** My Interpretation of pseudo code Mersen Twister MT19937
*/

#ifndef ECH_TWISTER_H_
#define ECH_TWISTER_H_

#define N             624 /** degree of recurrence*/
#define M             397 /** middle word, an offset used in the recurrence*/
#define A             0x9908B0DF /** coefficients of the rational normal form twist matrix*/
#define U             11 /** additional Mersenne Twister tempering bit shifts/masks*/
#define S             7 /** TGFSR(R) tempering bit shifts*/
#define B             0x9D2C5680 /** TGFSR(R) tempering bitmasks*/
#define T             15 /** TGFSR(R) tempering bit shifts*/
#define C             0xEFC60000 /** TGFSR(R) tempering bitmasks*/
#define L             18 /** additional Mersenne Twister tempering bit shifts/masks*/
#define LOW_MASK      0x7fffffff // (1 << r*) - 1
#define UP_MASK       0x80000000 // (1 << w*)

/**
* \struct MT_T
* \brief contain dimensionnal tab and index
*/
typedef struct ECHMT_T
{
    unsigned long dimension[N];
    short index;
}ECHMT_S;

#define SHIFTER_U(y) y ^= (y >> U)
#define SHIFTER_S_AND_B(y) y ^= (y >> S) & B
#define SHIFTER_T_AND_C(y) y ^= (y >> T) & C
#define SHIFTER_L(y) y ^= (y >> L)

#define REGISTER_SHIFTER(y)   \
        SHIFTER_U(y);         \
        SHIFTER_S_AND_B(y);   \
        SHIFTER_T_AND_C(y);   \
        SHIFTER_L(y);


////////////////////////////////////////////////////////////
///
/// \date 24/05/21
///
/// \version 3.0
///
/// \fn unsigned long ech_genRandom(ECHMT *ech)
///
/// \brief init pseudom random number dimension array
///
/// \param[in] ech struct contain index and dimensionnal tab
///
/// \return return number gen
///
////////////////////////////////////////////////////////////
unsigned long ech_genRandom(ECHMT_S *ech);

////////////////////////////////////////////////////////////
///
/// \date 24/05/21
///
/// \version 1.0
///
/// \fn void ech_seedRand(int seed)
///
/// \brief init pseudom random number serie
///
/// \param[in] seed seed for pseudom random number serie
///
/// \return ECHMT struct contain dimensionnal tab and index
///
////////////////////////////////////////////////////////////
ECHMT_S ech_seedRand(int seed);

#endif /* !ECH_TWISTER_H_ */
