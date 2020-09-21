//
// Created by Elizaveta on 19.09.2020.
//

#ifndef SUPERCOMPUTERS_MATRIXGENERATOR_H
#define SUPERCOMPUTERS_MATRIXGENERATOR_H

#include <iostream>
#include <NTL/GF2.h>
#include <NTL/mat_GF2.h>

using namespace std;

int generateNMatrixes(int size, const char *fileName);
NTL::mat_GF2 generateMatrix(NTL::mat_GF2& M, int p);

#endif //SUPERCOMPUTERS_MATRIXGENERATOR_H
