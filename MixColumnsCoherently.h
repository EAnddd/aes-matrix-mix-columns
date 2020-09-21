//
// Created by Elizaveta on 19.09.2020.
//

#ifndef SUPERCOMPUTERS_MIXCOLUMNSCOHERENTLY_H
#define SUPERCOMPUTERS_MIXCOLUMNSCOHERENTLY_H
#include <cstdio>
#include <iostream>
#include "NTL/GF2.h"
#include <NTL/mat_GF2.h>
#include <fstream>

NTL::mat_GF2 createFixedMatrix();
int mixColumns(const char *fileName, const char *resultFileName);
void readColumn(const char *name);
void addLineOrCount(const char *fileName, NTL::mat_GF2& matGf2, NTL::mat_GF2& fixedMatrix, std::ofstream &file);
NTL::mat_GF2 multiplyMatrixes(NTL::mat_GF2 &mat, NTL::mat_GF2 &mat1);

#endif //SUPERCOMPUTERS_MIXCOLUMNSCOHERENTLY_H
