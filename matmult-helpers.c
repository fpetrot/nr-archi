#include <stdlib.h>
#include <stdint.h>
#include "matmult-helpers.h"
/*
 * initialisation aléatoire de la matrice
 */
void random_matrix(uint32_t lines, uint32_t columns, double m[lines][columns])
{
    srand(unix);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            m[i][j] = (double)rand()/(double)(RAND_MAX);
        }
    }
}

/*
 * pour éviter que le compilateur considère la multiplication comme du
 * code mort.
 */
double sum(uint32_t lines, uint32_t columns, volatile double m[lines][columns])
{
    double r = 0;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            r += m[i][j];
        }
    }
    return r;
}
