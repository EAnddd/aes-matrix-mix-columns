//
// Created by Elizaveta on 19.09.2020.
//
#include <iostream>
#include <NTL/mat_GF2.h>
#include <NTL/vec_GF2.h>
#include "MixColumnsCoherently.h"

using namespace std;
int counter = 0;

int mixColumns(const char *fileName, const char *resultFileName) {
    readColumn(fileName);
    return 0;
}

void readColumn(const char *name) {
    ofstream resultFile;
    resultFile.open ("result.txt", std::ios_base::app);
    NTL::mat_GF2 matGf2;
    matGf2.SetDims(4, 4);
    std::ifstream myfile(name);
    std::string str;
    NTL::mat_GF2 fixedMatrix = createFixedMatrix();
    std::clock_t    start;

    start = std::clock();
    while (std::getline(myfile, str))
    {

        str.erase(std::remove(str.begin(), str.end(), '['), str.end());
        str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        char charLine[5];

        NTL::vec_GF2 vecGf2;

        strcpy(charLine, str.c_str());
        addLineOrCount(charLine, matGf2, fixedMatrix, resultFile);
    }
    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    myfile.close();
}

void addLineOrCount(const char *line, NTL::mat_GF2& matGf2, NTL::mat_GF2& fixedMatrix, ofstream &resultFile){

    if(counter < 4){
        for(int i = 0; i < 4; i++) {
            matGf2.put(counter, i, line[i]);
        }

        counter++;
    } else {
        NTL::mat_GF2 oneColumnMatrix;
        NTL::mat_GF2 resultColumn;
        oneColumnMatrix.SetDims(4, 1);
        resultColumn.SetDims(4, 1);
        for(int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                oneColumnMatrix.put(i, j, matGf2.get(i, j));
            }
            mul(resultColumn, fixedMatrix, oneColumnMatrix);
            for (int i = 0; i < 4; i++) {
                matGf2.put(i, j, resultColumn.get(i, j));
            }

        }
        resultFile << matGf2;
        matGf2.kill();
        matGf2.SetDims(4, 4);
        counter = 0;
    }


}



NTL::mat_GF2 createFixedMatrix() {
    int p = 4;
    //матрица, которая будет слева умножаться на столбцы
    NTL::mat_GF2 M;
    M.SetDims(p,p);
    long i, j;
    for(i=0; i<p; i++){
        for(j=0; j<p; j++){
            M.put(i,j,rand()%2);
        }
    }
    cout << "Fixed matrix\n";
    cout << M;

    return M;
}