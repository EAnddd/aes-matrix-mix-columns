
#include "MatrixGenerator.h"
#include "MixColumnsCoherently.h"

using namespace std;

int main() {

    generateNMatrixes(1, "matrix.txt");
    mixColumns("matrix.txt", "result.txt");
    return 0;
}
