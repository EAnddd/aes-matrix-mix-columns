//
// Created by Elizaveta on 19.09.2020.
//
#include <cstdio>
#include <iostream>
#include "NTL/GF2.h"
#include <NTL/mat_GF2.h>
#include "MatrixGenerator.h"
#include <fstream>
#include <omp.h>
using namespace std;

long generateNMatrixes(int size, const string& fileName){
//    remove(fileName);
    // т.к размер передается в mb, умножим на 1048576, чтобы получить байты
    long currentSize = 0;

    long matrixQuantity = size * 1048576 / 16;
    auto* matrixesFromFile = new NTL::mat_GF2[matrixQuantity];
    int j = 0;
    cout << "bbb";
    while(currentSize < size * 1048576) {
        NTL::mat_GF2 matGf2;
        NTL::mat_GF2 generatedMatrix = generateMatrix(matGf2, 4);
        matrixesFromFile[j] = generatedMatrix;
        j++;
        currentSize += sizeof(generatedMatrix);
    }
    //write into file matrix array
    ofstream matrixFile;
    matrixFile.open(fileName, std::ios_base::app);

    for(int i = 0; i < matrixQuantity; i++){
        matrixFile << matrixesFromFile[i];
    }
    matrixFile.close();
    delete[] matrixesFromFile;
    cout << "aa";
    return matrixQuantity;
}

NTL::mat_GF2 generateMatrix(NTL::mat_GF2& M, long p) {

    int rounds=0;
    long i, j;
    NTL::GF2 det;
    // М - квадратная матрица р на р
    M.SetDims(p,p);

    // итерируемся, пока не найдем инвертируемую матрицу
        // заполняем матрицу случайными значениями
        for(i=0; i<p; i++){
            for(j=0; j<p; j++){
                M.put(i,j,rand()%2);
            }
        return M;
    }

    throw exception();
}
