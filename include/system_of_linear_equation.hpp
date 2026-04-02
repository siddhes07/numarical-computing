#ifndef SYSTEM_OF_LINEAR_EQUATION_HPP
#define SYSTEM_OF_LINEAR_EQUATION_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

class SystemOfLinearEquation
{
protected:

    int n;
    vector<vector<double>> A;
    vector<double> b;

public:

    // Constructor
    SystemOfLinearEquation(int size)
    {
        n = size;
        A.resize(n, vector<double>(n));
        b.resize(n);
    }


    // Read matrix
    void readFromFile(ifstream &fin)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                fin>>A[i][j];
            }
        }
    }


    // Read vector
    void readVector(string filename)
    {
        ifstream fin(filename);

        if(!fin)
        {
            cout<<"Vector file open error\n";
            exit(1);
        }

        for(int i=0;i<n;i++)
        {
            fin>>b[i];
        }

        fin.close();
    }


    // Check diagonal dominance
    bool isDiagonallyDominant()
    {
        for(int i=0;i<n;i++)
        {
            double sum=0;

            for(int j=0;j<n;j++)
            {
                if(i!=j)
                    sum+=abs(A[i][j]);
            }

            if(abs(A[i][i])<sum)
                return false;
        }

        return true;
    }


    // Convert matrix into diagonally dominant form
    bool makeDiagonallyDominant()
    {
        for(int i=0;i<n;i++)
        {
            int maxRow=i;

            for(int k=i+1;k<n;k++)
            {
                if(abs(A[k][i])>abs(A[maxRow][i]))
                    maxRow=k;
            }

            if(maxRow!=i)
            {
                swap(A[i],A[maxRow]);
                swap(b[i],b[maxRow]);
            }
        }

        return isDiagonallyDominant();
    }


    // Print matrix
    void printMatrix(ofstream &fout)
    {
        fout<<"Matrix Used:\n";

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                fout<<A[i][j]<<" ";
            }

            fout<<endl;
        }

        fout<<endl;
    }


    // Dominance report (COMMON for all methods)
    // Dominance report (COMMON for all methods)
void dominanceReport(ofstream &fout)
{
    fout<<"Checking Diagonal Dominance...\n";

    if(isDiagonallyDominant())
    {
        fout<<"Matrix is Diagonally Dominant\n\n";
    }
    else
    {
        fout<<"Matrix is NOT Diagonally Dominant\n";
        fout<<"Trying to convert...\n";

        if(makeDiagonallyDominant())
        {
            fout<<"Matrix converted successfully\n\n";
            printMatrix(fout);
        }
        else
        {
            fout<<"Matrix cannot be converted to Dominant form\n\n";
        }
    }
}


// 🔽 ADD THIS FUNCTION EXACTLY HERE

void writeSolution(string outputFile, vector<double> solution)
{
    ofstream fout(outputFile, ios::app);

    fout<<"Solution:\n";

    for(int i=0;i<n;i++)
    {
        fout<<"x"<<i+1<<" = "<<solution[i]<<"\n";
    }

    fout<<"\n========================================\n\n";

    fout.close();
}


// Polymorphism
virtual void solve(string outputFile)=0;

    

};

#endif