//
// Created by Elizaveta on 19.09.2020.
//
#include <cstdio>
#include <iostream>
#include "NTL/GF2.h"
#include <NTL/mat_GF2.h>
#include "MatrixGenerator.h"
#include <fstream>
using namespace std;

int generateNMatrixes(int size, const char *fileName){
    remove(fileName);
    // т.к размер передается в mb, умножим на 1048576, чтобы получить байты
    int currentSize = 0;

    int matrixQuantity = size * 1048576 / 16;
    NTL::mat_GF2 matrixesFromFile[matrixQuantity];
    int j = 0;
    while(currentSize < size * 1048576) {
        NTL::mat_GF2 matGf2;
        NTL::mat_GF2 generatedMatrix = generateMatrix(matGf2, 4);
        matrixesFromFile[j] = generatedMatrix;
        j++;
        currentSize += sizeof(generatedMatrix);
    }
    //write into file matrix array
    ofstream matrixFile;
    matrixFile.open (fileName, std::ios_base::app);
    for(int i = 0; i < matrixQuantity; i++){
        matrixFile << matrixesFromFile[i];
    }
    matrixFile.close();
    return matrixQuantity;
}

NTL::mat_GF2 generateMatrix(NTL::mat_GF2& M, int p) {

    int rounds=0;
    long i, j;
    NTL::GF2 det;
    ;
    // М - квадратная матрица р на р
    M.SetDims(p,p);

    // итерируемся, пока не найдем инвертируемую матрицу
    for(rounds=0; rounds < 100; rounds++){
        // заполняем матрицу случайными значениями
        for(i=0; i<p; i++){
            for(j=0; j<p; j++){
                M.put(i,j,rand()%2);
            }
        }
        return M;
    }

    throw exception();
}
