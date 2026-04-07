#include <iostream>
#include <fstream>
#include <string>
#include "gaussian_elimination.hpp"
#include "lu_decomposition.hpp"
#include "gauss_jacobi.hpp"
#include "gauss_seidel.hpp"
#include "interpolation.hpp"
using namespace std;

const string MATRIX_FILE = "input/matrix.txt";
const string VECTOR_FILE = "input/vector.txt";
const string OUTPUT_FILE = "output/iterative_output.txt";
const string INTERPOLATION_FILE = "input/interpolation.txt";

int readMatrixSize() {
    ifstream fin(MATRIX_FILE);
    if (!fin) { cerr << "Error: Cannot open " << MATRIX_FILE << endl; exit(1); }
    int n; fin >> n; fin.close();
    return n;
}

void initOutputFile(int n) {
    ofstream fout(OUTPUT_FILE);
    fout << "========================================\n";
    fout << "  Numerical Computing - Method Output\n";
    fout << "  Matrix Size : " << n << " x " << n << "\n";
    fout << "========================================\n\n";
    fout.close();
}

void runGaussJacobi(int n) {
    cout << "\nRunning Gauss Jacobi...\n";
    try {
        GaussJacobi gj(n);
        ifstream fin(MATRIX_FILE); gj.readFromFile(fin); fin.close();
        gj.readVector(VECTOR_FILE);
        gj.solve(OUTPUT_FILE);
        cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
    } catch (exception &e) { cerr << "Error: " << e.what() << endl; }
}

void runGaussSeidel(int n) {
    cout << "\nRunning Gauss Seidel...\n";
    try {
        GaussSeidel gs(n);
        ifstream fin(MATRIX_FILE); gs.readFromFile(fin); fin.close();
        gs.readVector(VECTOR_FILE);
        gs.solve(OUTPUT_FILE);
        cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
    } catch (exception &e) { cerr << "Error: " << e.what() << endl; }
}

void runGaussianElimination(int n) {
    cout << "\nRunning Gaussian Elimination...\n";
    try {
        GaussianElimination ge(n);
        ifstream fin(MATRIX_FILE); ge.readFromFile(fin); fin.close();
        ge.readVector(VECTOR_FILE);
        ge.solve(OUTPUT_FILE);
        cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
    } catch (exception &e) { cerr << "Error: " << e.what() << endl; }
}
void runInterpolation()
{
    cout << "\nRunning Lagrange Interpolation...\n";

    try
    {
        int points = 20;

        Interpolation interp(points);

        interp.readData(INTERPOLATION_FILE);

        double value;

        cout << "Enter interpolation point: ";
        cin >> value;

        // Save output to file
        interp.lagrange(value, OUTPUT_FILE);

        cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
    }
    catch(exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}
void runLUDecomposition(int n) {
    cout << "\n--- LU Decomposition Sub-Menu ---\n";
    cout << "  1. Doolittle\n";
    cout << "  2. Crout\n";
    cout << "  3. Cholesky\n";
    cout << "  4. All LU Methods\n";
    cout << "Enter choice: ";
    int luChoice; cin >> luChoice;
    try {
        LUDecomposition lu(n);
        ifstream fin(MATRIX_FILE); lu.readFromFile(fin); fin.close();
        lu.readVector(VECTOR_FILE);
        if (luChoice == 1) { lu.doolittle(OUTPUT_FILE); cout << "Doolittle Done!\n"; }
        else if (luChoice == 2) { lu.crout(OUTPUT_FILE); cout << "Crout Done!\n"; }
        else if (luChoice == 3) { lu.cholesky(OUTPUT_FILE); cout << "Cholesky Done!\n"; }
        else if (luChoice == 4) {
            lu.doolittle(OUTPUT_FILE); cout << "Doolittle Done!\n";
            lu.crout(OUTPUT_FILE); cout << "Crout Done!\n";
            lu.cholesky(OUTPUT_FILE); cout << "Cholesky Done!\n";
        } else { cout << "Invalid choice!\n"; }
        cout << "Output saved to: " << OUTPUT_FILE << "\n";
    } catch (exception &e) { cerr << "Error: " << e.what() << endl; }
}

void runAllMethods(int n) {
    cout << "\nRunning All Methods...\n";
    cout << "-----------------------------\n";
    runGaussJacobi(n);
    runGaussSeidel(n);
    runGaussianElimination(n);
    try {
        LUDecomposition lu(n);
        ifstream fin(MATRIX_FILE); lu.readFromFile(fin); fin.close();
        lu.readVector(VECTOR_FILE);
        lu.doolittle(OUTPUT_FILE); cout << "LU Doolittle Done!\n";
        lu.crout(OUTPUT_FILE); cout << "LU Crout Done!\n";
    } catch (exception &e) { cerr << "LU Error: " << e.what() << endl; }
    cout << "\n========================================\n";
    cout << "All Methods Done!\n";
    cout << "Output saved to: " << OUTPUT_FILE << "\n";
    cout << "========================================\n";
}

int main() {
    int n = readMatrixSize();
    while (true) {
        cout << "\n========================================\n";
        cout << "  Numerical Computing - Method Selector\n";
        cout << "  Matrix Size: " << n << " x " << n << "\n";
        cout << "========================================\n";
        cout << "  1. Gauss Jacobi\n";
        cout << "  2. Gauss Seidel\n";
        cout << "  3. Gaussian Elimination\n";
        cout << "  4. LU Decomposition\n";
        cout << "  5. Run All Methods\n";
        cout << "  6. Lagrange Interpolation\n";
        cout << "  0. Exit\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        int choice; cin >> choice;
        if (choice != 0) initOutputFile(n);
        switch (choice) {
            case 1: runGaussJacobi(n); break;
            case 2: runGaussSeidel(n); break;
            case 3: runGaussianElimination(n); break;
            case 4: runLUDecomposition(n); break;
            case 5: runAllMethods(n); break;
            case 6: runInterpolation(); break;
            case 0: cout << "\nExiting... Goodbye!\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}