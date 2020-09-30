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
double mixColumns(const std::string& fileName,  const std::string& resultFileName,long matrixQuantity);
double readColumn(const std::string& name,  const std::string& resultFileName, long matrixQuantity);
void addLine(const char *fileName, NTL::mat_GF2& matGf2, NTL::mat_GF2 fixedMatrix[]);
double count( NTL::mat_GF2 matrixesFromFile[],  const std::string& resultFileName);

#endif //SUPERCOMPUTERS_MIXCOLUMNSCOHERENTLY_H
