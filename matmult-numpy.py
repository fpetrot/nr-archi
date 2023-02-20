# -*- coding: utf-8 -*-
# Implantation de la multiplication de matrice par appel à numpy
import numpy as np
import random

MSIZE = 1536

def random_matrix(lines, columns):
    array = [[0 for _ in range(lines)] for _ in range(columns)]

    for j in range(columns):
        for i in range(lines):
            array[j][i] = random.random()
    return array

A = random_matrix(MSIZE, MSIZE)
B = random_matrix(MSIZE, MSIZE)
R = [[0 for _ in range(MSIZE)] for _ in range(MSIZE)]
 
R = np.dot(A, B)
 
s = np.sum(R);
print(s)
