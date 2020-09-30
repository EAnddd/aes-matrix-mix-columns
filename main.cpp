

#include "MatrixGenerator.h"
#include "MixColumnsCoherently.h"
#include "plots/pbPlots.h"
#include "plots/supportLib.h"

using namespace std;

int main() {
    double sizes[] = {1, 5, 10, 50, 100};
    auto* times = new double[10];
    for (int i = 0; i < 5; i++) {
        int size = sizes[i];
        long matrixQuantity = generateNMatrixes(size, "matrix" + to_string(size)+ ".txt");
        times[i] = mixColumns("matrix" + to_string(size)+ ".txt", "result" + to_string(size)+ ".txt", matrixQuantity);
    }
    std::vector<double> timesV;
    std::vector<double> sizesV;
    for (int j = 0; j < 5; j++) {
        timesV.push_back(times[j]);
        sizesV.push_back(sizes[j]);
        cout << times[j];
        cout << " size ";
        cout << sizes[j];
        cout << "\n";
    }

    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
    DrawScatterPlot(imageReference, 600, 400, &timesV, &sizesV);
    vector<double> *pngdata = ConvertToPNG(imageReference->image);
    WriteToFile(pngdata, "result.png");
    return 0;
}
