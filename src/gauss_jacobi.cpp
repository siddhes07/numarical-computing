#include "gauss_jacobi.hpp"
#include <fstream>
#include <cmath>

using namespace std;

GaussJacobi::GaussJacobi(int size, int maxIter, double tol)
: SystemOfLinearEquation(size)
{
    maxIterations = maxIter;
    tolerance = tol;
}

void GaussJacobi::solve(string outputFile)
{
    ofstream fout(outputFile, ios::app);

    fout<<"Method Selected : Gauss Jacobi\n\n";

    fout<<"Checking Diagonal Dominance...\n";

    bool dominant = isDiagonallyDominant();

    if(dominant)
    {
        fout<<"Matrix is diagonally dominant\n";
        fout<<"Using original matrix for iterations\n\n";
    }
    else
    {
        fout<<"Matrix is NOT diagonally dominant\n";
        fout<<"Trying conversion...\n";

        if(makeDiagonallyDominant())
        {
            fout<<"Conversion successful\n";
            fout<<"Using converted matrix for iterations\n\n";
        }
        else
        {
            fout<<"Conversion NOT possible\n";
            fout<<"Using original matrix for iterations\n\n";
        }
    }

    vector<double> x_old(n,0);
    vector<double> x_new(n,0);

    int convergedIteration = -1;

    for(int iter=1; iter<=maxIterations; iter++)
    {
        for(int i=0;i<n;i++)
        {
            double sum=0;

            for(int j=0;j<n;j++)
            {
                if(i!=j)
                    sum+=A[i][j]*x_old[j];
            }

            x_new[i]=(b[i]-sum)/A[i][i];
        }

        fout<<"Iteration "<<iter<<"\n";

        for(int i=0;i<n;i++)
        {
            fout<<"x"<<i+1<<" = "<<x_new[i]<<"\n";
        }

        fout<<"\n";

        bool converged=true;

        for(int i=0;i<n;i++)
        {
            if(abs(x_new[i]-x_old[i])>tolerance)
            {
                converged=false;
                break;
            }
        }

        if(converged)
        {
            convergedIteration = iter;
            break;
        }

        x_old=x_new;
    }

    if(convergedIteration!=-1)
    {
        fout<<"Solution converged at iteration "
            <<convergedIteration<<"\n\n";
    }
    else
    {
        fout<<"Solution did NOT converge within "
            <<maxIterations<<" iterations\n\n";
    }

    writeSolution(outputFile, x_new);

    fout.close();
}