#include <iostream>
#include <fstream>
#include <string>

#include "gaussian_elimination.hpp"
#include "lu_decomposition.hpp"
#include "gershgorin.hpp"
#include "gauss_jacobi.hpp"
#include "gauss_seidel.hpp"
#include "interpolation.hpp"
#include "least_squares.hpp"          // ← NEW

using namespace std;


// Runtime file paths
string MATRIX_FILE;
string VECTOR_FILE;
string INTERPOLATION_FILE;

const string OUTPUT_FILE = "output/iterative_output.txt";


// ============================================================
//  Read matrix size from the matrix input file
// ============================================================
int readMatrixSize()
{
    ifstream fin(MATRIX_FILE);

    if (!fin)
    {
        cerr << "Error: Cannot open " << MATRIX_FILE << endl;
        exit(1);
    }

    int n;
    fin >> n;
    fin.close();

    return n;
}


// ============================================================
//  Initialize / overwrite the output file with a header
// ============================================================
void initOutputFile(int n)
{
    ofstream fout(OUTPUT_FILE);

    fout << "========================================\n";
    fout << "  Numerical Computing - Method Output\n";
    fout << "  Matrix Size : " << n << " x " << n << "\n";
    fout << "========================================\n\n";

    fout.close();
}


// ============================================================
//  Gauss Jacobi
// ============================================================
void runGaussJacobi()
{
    cout << "\nRunning Gauss Jacobi...\n";

    cout << "Enter matrix file path: ";
    cin >> MATRIX_FILE;

    cout << "Enter vector file path: ";
    cin >> VECTOR_FILE;

    int n = readMatrixSize();
    initOutputFile(n);

    try
    {
        GaussJacobi gj(n);

        ifstream fin(MATRIX_FILE);
        gj.readFromFile(fin);
        fin.close();

        gj.readVector(VECTOR_FILE);

        Gershgorin g(n);

        ifstream fin2(MATRIX_FILE);
        g.readFromFile(fin2);
        fin2.close();

        g.check(OUTPUT_FILE);
        gj.solve(OUTPUT_FILE);

        cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}


// ============================================================
//  Gauss Seidel
// ============================================================
void runGaussSeidel()
{
    cout << "\nRunning Gauss Seidel...\n";

    cout << "Enter matrix file path: ";
    cin >> MATRIX_FILE;

    cout << "Enter vector file path: ";
    cin >> VECTOR_FILE;

    int n = readMatrixSize();
    initOutputFile(n);

    try
    {
        GaussSeidel gs(n);

        ifstream fin(MATRIX_FILE);
        gs.readFromFile(fin);
        fin.close();

        gs.readVector(VECTOR_FILE);

        Gershgorin g(n);

        ifstream fin2(MATRIX_FILE);
        g.readFromFile(fin2);
        fin2.close();

        g.check(OUTPUT_FILE);
        gs.solve(OUTPUT_FILE);

        cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}


// ============================================================
//  Gaussian Elimination
// ============================================================
void runGaussianElimination()
{
    cout << "\nRunning Gaussian Elimination...\n";

    cout << "Enter matrix file path: ";
    cin >> MATRIX_FILE;

    cout << "Enter vector file path: ";
    cin >> VECTOR_FILE;

    int n = readMatrixSize();
    initOutputFile(n);

    try
    {
        GaussianElimination ge(n);

        ifstream fin(MATRIX_FILE);
        ge.readFromFile(fin);
        fin.close();

        ge.readVector(VECTOR_FILE);
        ge.solve(OUTPUT_FILE);

        cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}


// ============================================================
//  LU Decomposition
// ============================================================
void runLUDecomposition()
{
    cout << "\nRunning LU Decomposition...\n";

    cout << "Enter matrix file path: ";
    cin >> MATRIX_FILE;

    cout << "Enter vector file path: ";
    cin >> VECTOR_FILE;

    int n = readMatrixSize();
    initOutputFile(n);

    cout << "\n--- LU Decomposition Sub-Menu ---\n";
    cout << "1. Doolittle\n";
    cout << "2. Crout\n";
    cout << "3. Cholesky\n";
    cout << "4. All LU Methods\n";
    cout << "Enter choice: ";

    int luChoice;
    cin >> luChoice;

    try
    {
        LUDecomposition lu(n);

        ifstream fin(MATRIX_FILE);
        lu.readFromFile(fin);
        fin.close();

        lu.readVector(VECTOR_FILE);

        if      (luChoice == 1) lu.doolittle(OUTPUT_FILE);
        else if (luChoice == 2) lu.crout(OUTPUT_FILE);
        else if (luChoice == 3) lu.cholesky(OUTPUT_FILE);
        else if (luChoice == 4)
        {
            lu.doolittle(OUTPUT_FILE);
            lu.crout(OUTPUT_FILE);
            lu.cholesky(OUTPUT_FILE);
        }
        else
            cout << "Invalid choice!\n";

        cout << "Output saved to: " << OUTPUT_FILE << "\n";
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}


// ============================================================
//  Helper : ask for interpolation file and return point count
// ============================================================
int askInterpFile()
{
    cout << "Enter interpolation file path: ";
    cin >> INTERPOLATION_FILE;

    ifstream file(INTERPOLATION_FILE);
    if (!file)
        throw runtime_error("Cannot open interpolation file");

    int points;
    file >> points;
    file.close();

    initOutputFile(points);
    return points;
}


// ============================================================
//  Interpolation Sub-Menu
//
//  1. Lagrange
//  2. Newton          (coming soon)
//  3. Least Squares   – Linear  Fit   y = a + bx
//  4. Least Squares   – Parabolic Fit y = a + bx + cx²
//  0. Back
// ============================================================
void runInterpolationMenu()
{
    while (true)
    {
        cout << "\n--- Interpolation Methods ---\n";
        cout << "1. Lagrange\n";
        cout << "2. Newton (Coming soon)\n";
        cout << "3. Least Squares - Linear Fit  (y = a + bx)\n";
        cout << "4. Least Squares - Parabolic Fit  (y = a + bx + cx²)\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        // ---------- Newton (stub) ----------
        if (choice == 2)
        {
            cout << "Newton interpolation not implemented yet.\n";
            continue;
        }

        // ---------- All other choices need a file ----------
        try
        {
            int points = askInterpFile();

            // ---- Lagrange ----
            if (choice == 1)
            {
                Interpolation interp(points);
                interp.readData(INTERPOLATION_FILE);

                double value;
                cout << "Enter interpolation point: ";
                cin >> value;

                interp.lagrange(value, OUTPUT_FILE);
            }

            // ---- Least Squares : Linear Fit ----
            else if (choice == 3)
            {
                LeastSquares ls(points);
                ls.readData(INTERPOLATION_FILE);

                ls.linearFit(OUTPUT_FILE);
            }

            // ---- Least Squares : Parabolic Fit ----
            else if (choice == 4)
            {
                LeastSquares ls(points);
                ls.readData(INTERPOLATION_FILE);

                ls.parabolicFit(OUTPUT_FILE);
            }

            else
            {
                cout << "Invalid choice!\n";
                continue;
            }

            cout << "Done! Output saved to: " << OUTPUT_FILE << "\n";
        }
        catch (exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }
}


// ============================================================
//  Run All Methods sequentially
// ============================================================
void runAllMethods()
{
    cout << "\nRunning All Methods Sequentially...\n";

    runGaussJacobi();
    runGaussSeidel();
    runGaussianElimination();
    runLUDecomposition();
    runInterpolationMenu();

    cout << "\nAll methods completed. Output saved to: "
         << OUTPUT_FILE << "\n";
}


// ============================================================
//  MAIN
// ============================================================
int main()
{
    while (true)
    {
        cout << "\n========================================\n";
        cout << "  Numerical Computing - Method Selector\n";
        cout << "========================================\n";
        cout << "1. Gauss Jacobi\n";
        cout << "2. Gauss Seidel\n";
        cout << "3. Gaussian Elimination\n";
        cout << "4. LU Decomposition\n";
        cout << "5. Interpolation\n";
        cout << "6. Run All Methods\n";
        cout << "0. Exit\n";
        cout << "========================================\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
            case 1: runGaussJacobi();         break;
            case 2: runGaussSeidel();         break;
            case 3: runGaussianElimination(); break;
            case 4: runLUDecomposition();     break;
            case 5: runInterpolationMenu();   break;
            case 6: runAllMethods();          break;
            case 0:
                cout << "\nExiting... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}