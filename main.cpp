
#include "MatrixGenerator.h"
#include "MixColumnsCoherently.h"

using namespace std;

int main() {

    int matrixQuantity = generateNMatrixes(1, "matrix.txt");
    mixColumns("matrix.txt", "result.txt", matrixQuantity);
    return 0;
}
