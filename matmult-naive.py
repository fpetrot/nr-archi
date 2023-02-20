# -*- coding: utf-8 -*-
# Implantation naïve de la multiplication de matrice

import random

MSIZE = 512

def random_matrix(lines, columns):
    array = [[0 for _ in range(lines)] for _ in range(columns)]

    for j in range(columns):
        for i in range(lines):
            array[j][i] = random.random()
    return array

A = random_matrix(MSIZE, MSIZE)
B = random_matrix(MSIZE, MSIZE)
R = [[0 for _ in range(MSIZE)] for _ in range(MSIZE)]
 
for i in range(len(A)):
    for j in range(len(B[0])):
        for k in range(len(B)):
            R[i][j] += A[i][k] * B[k][j]
 
# for r in R:
#     print(r)
