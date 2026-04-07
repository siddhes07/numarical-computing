#include "gaussian_elimination.hpp"
#include <fstream>
#include <cmath>
#include <stdexcept>

using namespace std;


// Constructor
GaussianElimination::GaussianElimination(int size)
    : SystemOfLinearEquation(size) {}


// Solve function
void GaussianElimination::solve(string outputFile)
{
    ofstream fout(outputFile, ios::app);

    fout << "========================================\n";
    fout << "Gaussian Elimination Method\n";
    fout << "========================================\n\n";

    // Step 1: Diagonal dominance check
    dominanceReport(fout);

   int n = this->n;
vector<vector<double>> A = this->A;
vector<double> rhs = this->b;

    // Step 2: Print Initial Matrix
    fout << "Initial Augmented Matrix:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            fout << A[i][j] << " ";

        fout << "| " << rhs[i] << "\n";
    }

    fout << "\n";


    // Step 3: Forward Elimination with Partial Pivoting
    for(int i = 0; i < n; i++)
    {
        int pivot = i;

        for(int k = i + 1; k < n; k++)
        {
            if(abs(A[k][i]) > abs(A[pivot][i]))
                pivot = k;
        }

        // Swap rows
        swap(A[i], A[pivot]);
        swap(rhs[i], rhs[pivot]);


        // Check singular matrix
        if(abs(A[i][i]) < 1e-10)
            throw runtime_error("Singular matrix detected!");


        // Elimination step
        for(int k = i + 1; k < n; k++)
        {
            double factor = A[k][i] / A[i][i];

            for(int j = i; j < n; j++)
                A[k][j] -= factor * A[i][j];

            rhs[k] -= factor * rhs[i];
        }


        // Print matrix after each iteration
        fout << "After Iteration " << i + 1 << ":\n";

        for(int r = 0; r < n; r++)
        {
            for(int c = 0; c < n; c++)
                fout << A[r][c] << " ";

            fout << "| " << rhs[r] << "\n";
        }

        fout << "\n";
    }


    // Step 4: Print Upper Triangular Matrix
    fout << "Upper Triangular Matrix:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            fout << A[i][j] << " ";

        fout << "\n";
    }

    fout << "\n";


    // Step 5: Back Substitution
    vector<double> solution(n);

    for(int i = n - 1; i >= 0; i--)
    {
        solution[i] = rhs[i];

        for(int j = i + 1; j < n; j++)
            solution[i] -= A[i][j] * solution[j];

        solution[i] /= A[i][i];
    }


    // Step 6: Print iteration completion info
    fout << "Solution obtained after "
         << n
         << " elimination iterations\n\n";

    fout.close();


    // Step 7: Final solution print (parent class function)
    this->writeSolution(outputFile, solution);
}