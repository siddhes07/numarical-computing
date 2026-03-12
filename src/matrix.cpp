#include "matrix.hpp"
#include <stdexcept>
#include <cmath>
using namespace std;

// --- Constructors ---
Matrix::Matrix() : rows(0), cols(0) {}
Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<double>(c, 0)) {}
Matrix::Matrix(const Matrix &m) : rows(m.rows), cols(m.cols), data(m.data) {}

// --- File I/O ---
void Matrix::readFromFile(ifstream &fin) {
    for (auto &row : data) for (auto &val : row) fin >> val;
}
void Matrix::displayToFile(ofstream &fout) const {
    for (const auto &row : data) {
        for (const auto &val : row) fout << val << " ";
        fout << "\n";
    }
}

// --- Operator Overloading ---
double &Matrix::operator()(int i, int j)       { return data[i][j]; }
double  Matrix::operator()(int i, int j) const { return data[i][j]; }
bool    Matrix::operator==(const Matrix &m) const { return data == m.data; }

// Arithmetic operators (+, -, *)
Matrix Matrix::operator+(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols) throw invalid_argument("Size mismatch!");
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res(i,j) = data[i][j] + m(i,j);
    return res;
}
Matrix Matrix::operator-(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols) throw invalid_argument("Size mismatch!");
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res(i,j) = data[i][j] - m(i,j);
    return res;
}
Matrix Matrix::operator*(const Matrix &m) const {
    if (cols != m.rows) throw invalid_argument("Size mismatch!");
    Matrix res(rows, m.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < m.cols; j++)
            for (int k = 0; k < cols; k++)
                res(i,j) += data[i][k] * m(k,j);
    return res;
}

// Stream operators
istream &operator>>(istream &in, Matrix &m) {
    for (auto &row : m.data) for (auto &val : row) in >> val;
    return in;
}
ostream &operator<<(ostream &out, const Matrix &m) {
    for (const auto &row : m.data) {
        for (const auto &val : row) out << val << " ";
        out << "\n";
    }
    return out;
}

// --- Properties ---
bool Matrix::isSquare()    const { return rows == cols; }
bool Matrix::isTranspose(const Matrix &m) const { return *this == m.transpose(); }
bool Matrix::isNull()      const {
    for (const auto &row : data) for (const auto &val : row) if (val != 0) return false;
    return true;
}
bool Matrix::isSymmetric() const {
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (data[i][j] != data[j][i]) return false;
    return true;
}
bool Matrix::isIdentity()  const {
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (data[i][j] != (i == j ? 1 : 0)) return false;
    return true;
}
bool Matrix::isDiagonal()  const {
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (i != j && data[i][j] != 0) return false;
    return true;
}
bool Matrix::isDiagonallyDominant() const {
    for (int i = 0; i < rows; i++) {
        double diag = abs(data[i][i]), sum = 0;
        for (int j = 0; j < cols; j++) if (i != j) sum += abs(data[i][j]);
        if (diag < sum) return false;
    }
    return true;
}

// --- Operations ---
Matrix Matrix::transpose() const {
    Matrix res(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res(j,i) = data[i][j];
    return res;
}

void Matrix::makeDiagonallyDominant() {
    for (int i = 0; i < rows; i++) {
        int maxRow = i;
        for (int k = i+1; k < rows; k++)
            if (abs(data[k][i]) > abs(data[maxRow][i])) maxRow = k;
        swap(data[i], data[maxRow]);
    }
}

double Matrix::determinant() const {
    if (!isSquare()) throw invalid_argument("Matrix must be square!");
    int n = rows;
    auto temp = data;
    double det = 1;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int k = i+1; k < n; k++) if (abs(temp[k][i]) > abs(temp[pivot][i])) pivot = k;
        if (pivot != i) { swap(temp[i], temp[pivot]); det *= -1; }
        if (temp[i][i] == 0) return 0;
        det *= temp[i][i];
        for (int k = i+1; k < n; k++) {
            double f = temp[k][i] / temp[i][i];
            for (int j = i; j < n; j++) temp[k][j] -= f * temp[i][j];
        }
    }
    return det;
}

Matrix Matrix::inverse() const {
    if (!isSquare()) throw invalid_argument("Matrix must be square!");
    int n = rows;
    vector<vector<double>> aug(n, vector<double>(2*n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) aug[i][j] = data[i][j];
        aug[i][i+n] = 1;
    }
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int k = i+1; k < n; k++) if (abs(aug[k][i]) > abs(aug[pivot][i])) pivot = k;
        swap(aug[i], aug[pivot]);
        if (aug[i][i] == 0) throw runtime_error("Matrix is singular!");
        double div = aug[i][i];
        for (auto &val : aug[i]) val /= div;
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            double f = aug[k][i];
            for (int j = 0; j < 2*n; j++) aug[k][j] -= f * aug[i][j];
        }
    }
    Matrix res(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res(i,j) = aug[i][j+n];
    return res;
}