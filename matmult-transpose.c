#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "matmult-helpers.h"

static double A[MSIZE][MSIZE];
static double B[MSIZE][MSIZE];
static volatile double R[MSIZE][MSIZE];
double tmp[MSIZE][MSIZE];

int main(void)
{
    random_matrix(MSIZE, MSIZE, A);
    random_matrix(MSIZE, MSIZE, B);
    memset((double **)R, 0, sizeof(R));

    /* Transposition de la seconde matrice */
    for (int i = 0; i < MSIZE; i++) {
        for(int j = 0; j < MSIZE; j++) {
            tmp[i][j] = B[j][i];
        }
    }

    do {
        for (int i = 0; i < MSIZE; i++) {
            for(int j = 0; j < MSIZE; j++) {
                for(int k = 0; k < MSIZE; k++) {
                    R[i][j] += A[i][k] * tmp[j][k];
                }
            }
        }
    } while (COND);

    return (int)sum(MSIZE, MSIZE, R);
}
