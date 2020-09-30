//
// Created by Elizaveta on 19.09.2020.
//
#include <omp.h>
#include <iostream>
#include <utility>
#include <NTL/mat_GF2.h>
#include "MixColumnsCoherently.h"


using namespace std;
int counter = 0;
int matNum = 0;
double mixColumns(const string& fileName, const string& resultFileName, long matrixQuantity) {
   return readColumn(fileName, resultFileName, matrixQuantity);
}

double readColumn(const string& name, const string& resultFileName,long matrixQuantity) {

    NTL::mat_GF2 matGf2;
    matGf2.SetDims(4, 4);
    std::ifstream myfile(name);
    std::string str;
    printf("nam %ldm \n", matrixQuantity);
    auto* matrixesFromFile = new NTL::mat_GF2[matrixQuantity];
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
    double finalTime = count(matrixesFromFile, resultFileName);
    myfile.close();
    matNum = 0;
    delete [] matrixesFromFile;
    return finalTime;
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

double count(NTL::mat_GF2 matrixesFromFile[],  const string& resultFileName){
    NTL::mat_GF2 oneColumnMatrix;
    NTL::mat_GF2 resultColumn;
    NTL::mat_GF2 matGf2;
    auto* resultMatrixes = new NTL::mat_GF2[matNum];
    NTL::mat_GF2 fixedMatrix = createFixedMatrix();
    // matrix for 1 column
    oneColumnMatrix.SetDims(4, 1);
    // column for multiplication
    resultColumn.SetDims(4, 1);
    std::clock_t    start;
    // iterate through all matrixes (matNum is size we've already found in addLine() method)
    start = std::clock();
    int j;
    int k;
    int i;
    int threadID = 0;
    //OpenMP block, comment to get no-parallel execution
    omp_set_num_threads(2);
    #pragma omp parallel for  default(none) private(k, matGf2, i, j) firstprivate(oneColumnMatrix, resultColumn, fixedMatrix) shared(matrixesFromFile, resultMatrixes, matNum)
    for(k = 0; k < matNum; k++) {
        matGf2 = matrixesFromFile[k];
        //iterate through columns and lines
        //TODO развернуть цикл

        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++) {
                //create one column
                oneColumnMatrix.put(i, j, matGf2.get(i, j));
            }

            mul(resultColumn, fixedMatrix, oneColumnMatrix);
            for (i = 0; i < 4; i++) {
                //put result
                matGf2.put(i, j, resultColumn.get(i, j));
            }
//        };
        }
        //add result to array
        resultMatrixes[k] = matGf2;
    }
    //write result into file
    double myTime = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
    cout << myTime;
    ofstream resultFile;
    resultFile.open (resultFileName, std::ios_base::app);
    for(int a = 0; a < matNum; a++){
        resultFile << resultMatrixes[a];
    }
    resultFile << "\nTime: " << myTime << " ms" << std::endl;
    resultFile.close();
    delete [] resultMatrixes;
    return myTime;
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