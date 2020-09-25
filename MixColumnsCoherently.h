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
int mixColumns(const char *fileName, const char *resultFileName, int matrixQuantity);
void readColumn(const char *name, int matrixQuantity);
void addLine(const char *fileName, NTL::mat_GF2& matGf2, NTL::mat_GF2 fixedMatrix[]);
void count(std::ofstream &resultFile, NTL::mat_GF2 matrixesFromFile[], NTL::mat_GF2 &fixedMatrix);

#endif //SUPERCOMPUTERS_MIXCOLUMNSCOHERENTLY_H
