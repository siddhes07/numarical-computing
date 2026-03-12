#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "gaussian_elimination.hpp"
#include "lu_decomposition.hpp"
using namespace std;

const string MAT = "input/1.txt";
const string VEC = "input/2.txt";
const string OUT = "output/";

void printProperties(Matrix &A, string outFile) {
    ofstream fout(outFile, ios::app);
    fout << "=== Matrix Properties ===\n"
         << "Is Square             : " << (A.isSquare()             ? "Yes" : "No") << "\n"
         << "Is Symmetric          : " << (A.isSymmetric()          ? "Yes" : "No") << "\n"
         << "Is Identity           : " << (A.isIdentity()           ? "Yes" : "No") << "\n"
         << "Is Null               : " << (A.isNull()               ? "Yes" : "No") << "\n"
         << "Is Diagonal           : " << (A.isDiagonal()           ? "Yes" : "No") << "\n"
         << "Is Diagonally Dominant: " << (A.isDiagonallyDominant() ? "Yes" : "No") << "\n"
         << "Determinant           : " << A.determinant()            << "\n"
         << "=========================\n\n";
}

void runSolver(int choice, int size, Matrix &A, string outFile) {
    ofstream clear(outFile); clear.close();
    printProperties(A, outFile);

    if (choice == 1) {
        GaussianElimination gauss(size);
        ifstream f(MAT); int r, c; f >> r >> c; // skip size line
        gauss.readFromFile(f); f.close();
        gauss.readVector(VEC);
        gauss.solve(outFile);
    } else {
        LUDecomposition lu(size);
        ifstream f(MAT); int r, c; f >> r >> c; // skip size line
        lu.readFromFile(f); f.close();
        lu.readVector(VEC);
        if      (choice == 2) lu.doolittle(outFile);
        else if (choice == 3) lu.crout(outFile);
        else if (choice == 4) lu.cholesky(outFile);
    }
    cout << "Done! -> " << outFile << "\n";
}

int main() {
    int choice;

    // Size file मधूनच read करतो
    ifstream fin(MAT);
    if (!fin) { cerr << "Cannot open: " << MAT << "\n"; return 1; }
    int rows, cols;
    fin >> rows >> cols;  // पहिली line - 49 50 read करतो
    int size = rows;      // square matrix साठी rows वापरतो
    
    // Matrix read करतो
    Matrix A(size, size);
    A.readFromFile(fin);
    fin.close();

    cout << "=== Linear Equation Solver ===\n"
         << "Matrix: " << MAT << " (" << size << "x" << size << ")\n"
         << "Vector: " << VEC << "\n\n"
         << "1. Gaussian Elimination\n"
         << "2. LU Doolittle\n"
         << "3. LU Crout\n"
         << "4. LU Cholesky\n"
         << "5. All Methods\n"
         << "Enter choice: ";
    cin >> choice;

    if (choice >= 1 && choice <= 4) {
        string files[] = {"", OUT+"gaussian_output.txt", OUT+"lu_doolittle_output.txt",
                              OUT+"lu_crout_output.txt", OUT+"lu_cholesky_output.txt"};
        runSolver(choice, size, A, files[choice]);
    } else if (choice == 5) {
        runSolver(1, size, A, OUT+"gaussian_output.txt");
        runSolver(2, size, A, OUT+"lu_doolittle_output.txt");
        runSolver(3, size, A, OUT+"lu_crout_output.txt");
        runSolver(4, size, A, OUT+"lu_cholesky_output.txt");
        cout << "All methods done!\n";
    } else {
        cout << "Invalid choice!\n";
        return 1;
    }

    return 0;
}