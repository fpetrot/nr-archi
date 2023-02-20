#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "matmult-helpers.h"

static double A[MSIZE][MSIZE];
static double B[MSIZE][MSIZE];
static volatile double R[MSIZE][MSIZE];

int main(void)
{
    random_matrix(MSIZE, MSIZE, A);
    random_matrix(MSIZE, MSIZE, B);
    memset((double **)R, 0, sizeof(R));

    long blocksz = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    long dinc = blocksz/sizeof (double);
    dinc = 8;

    /*
     * hypothèse simplificatrice pour ne pas complexifier le
     * code de tuilage : le nombre de "double"s dans la ligne de cache
     * divise la taille de la matrice.
     */
    assert(MSIZE%dinc == 0);

    do {
        for (int i = 0; i < MSIZE; i += dinc) {
            for (int j = 0; j < MSIZE; j += dinc) {
                for (int k = 0; k < MSIZE; k += dinc) {
                    double *AA, *BB;
                    volatile double *RR;
                    int i2;
                    for (i2 = 0, RR = &R[i][j], AA = &A[i][k];
                            i2 < dinc;
                            i2++, RR += MSIZE, AA += MSIZE) {
                        int k2;
                        for (k2 = 0, BB = &B[k][j];
                                k2 < dinc;
                                k2++, BB += MSIZE) {
                            for (int j2 = 0; j2 < dinc; j2++) {
                                RR[j2] += AA[k2] * BB[j2];
                            }
                        }
                    }
                }
            }
        }
    } while (COND);

    return (int)sum(MSIZE, MSIZE, R);
}
