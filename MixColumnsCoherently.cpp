//
// Created by Elizaveta on 19.09.2020.
//
#include <iostream>
#include <NTL/mat_GF2.h>
#include "MixColumnsCoherently.h"
#include "../../../../usr/local/include/NTL/mat_GF2.h"

using namespace std;
int counter = 0;
int matNum = 0;
int mixColumns(const char *fileName, const char *resultFileName, int matrixQuantity) {
    readColumn(fileName, matrixQuantity);
    return 0;
}

void readColumn(const char *name, int matrixQuantity) {
    ofstream resultFile;
    resultFile.open ("result.txt", std::ios_base::app);
    NTL::mat_GF2 matGf2;
    matGf2.SetDims(4, 4);
    std::ifstream myfile(name);
    std::string str;
    NTL::mat_GF2 fixedMatrix = createFixedMatrix();
    std::clock_t    start;

    //i don't know yet how to detect array size properly (the only thought us to divide whole size to one matrix size and add 10% to make sure)
    NTL::mat_GF2 matrixesFromFile[matrixQuantity];

    while (std::getline(myfile, str))
    {

        //remove rubbish symbols that lib has generated
        //example of matrix from lib:
        // [[0 1 1 0]
        //[0 1 0 0]
        //[1 1 1 0]
        //[1 1 0 1]
        //] and we want without brackets

        str.erase(std::remove(str.begin(), str.end(), '['), str.end());
        str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        char charLine[5];

        strcpy(charLine, str.c_str());
        addLine(charLine, matGf2, matrixesFromFile);

    }

    start = std::clock();
    count(resultFile, matrixesFromFile, fixedMatrix);
    resultFile << "\nTime: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    myfile.close();
}



void addLine(const char *line, NTL::mat_GF2& matGf2,  NTL::mat_GF2 matrixesFromFile[]){

    if(counter < 3){
        //until we've got 4 lines, filling matrix
        for(int i = 0; i < 4; i++) {
            matGf2.put(counter, i, line[i]);
        }
        counter++;
    } else {
        //when we've got 4 lines, add it into array and go on
        matrixesFromFile[matNum] = matGf2;
        matNum++;
        matGf2.kill();
        matGf2.SetDims(4, 4);
        counter = 0;
    }


}

void count(ofstream &resultFile, NTL::mat_GF2 matrixesFromFile[], NTL::mat_GF2 &fixedMatrix){
    NTL::mat_GF2 oneColumnMatrix;
    NTL::mat_GF2 resultColumn;
    NTL::mat_GF2 matGf2;
    NTL::mat_GF2 resultMatrixes[matNum];
    // matrix for 1 column
    oneColumnMatrix.SetDims(4, 1);
    // column for multiplication
    resultColumn.SetDims(4, 1);
    // iterate through all matrixes (matNum is size we've already found in addLine() method)
    for(int k = 0; k < matNum; k++) {

        matGf2 = matrixesFromFile[k];
        //iterate through columns and lines
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                //create one column
                oneColumnMatrix.put(i, j, matGf2.get(i, j));
            }
            //multiply columns
            mul(resultColumn, fixedMatrix, oneColumnMatrix);
            for (int i = 0; i < 4; i++) {
                //put result
                matGf2.put(i, j, resultColumn.get(i, j));
            }

        }
        //add result to array
        resultMatrixes[k] = matGf2;

    }
    //write result into file
    for(int i = 0; i < matNum; i++){
        resultFile << resultMatrixes[i];
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
    return M;
}