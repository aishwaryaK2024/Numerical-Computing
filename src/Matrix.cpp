#include "Matrix.hpp"
#include <iomanip>
#include <cmath>
#include <algorithm>

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<double>(c, 0.0))
{
    if (r <= 0 || c <= 0) throw invalid_argument("Dimensions must be positive.");
}

Matrix::Matrix(const string& filename)
{
    ifstream file(filename);
    if (!file) throw runtime_error("Cannot open file: " + filename);
    file >> rows >> cols;
    if (rows <= 0 || cols <= 0) throw runtime_error("Invalid dimensions in file.");
    data.resize(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!(file >> data[i][j])) throw runtime_error("Incomplete data in file.");
}

double Matrix::operator()(int r, int c) const
{
    if (r < 0 || r >= rows || c < 0 || c >= cols) throw out_of_range("Index out of range.");
    return data[r][c];
}
double& Matrix::operator()(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols) throw out_of_range("Index out of range.");
    return data[r][c];
}

Matrix Matrix::operator+(const Matrix& m) const
{
    if (rows != m.rows || cols != m.cols) throw invalid_argument("Addition: dimension mismatch.");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] + m.data[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& m) const
{
    if (rows != m.rows || cols != m.cols) throw invalid_argument("Subtraction: dimension mismatch.");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] - m.data[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& m) const
{
    if (cols != m.rows) throw invalid_argument("Multiplication: incompatible dimensions.");
    Matrix result(rows, m.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < m.cols; j++)
            for (int k = 0; k < cols; k++)
                result.data[i][j] += data[i][k] * m.data[k][j];
    return result;
}

Matrix Matrix::operator/(double s) const
{
    if (fabs(s) < 1e-12) throw invalid_argument("Division by zero.");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] / s;
    return result;
}

bool Matrix::operator==(const Matrix& m) const
{
    if (rows != m.rows || cols != m.cols) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fabs(data[i][j] - m.data[i][j]) > 1e-9) return false;
    return true;
}

bool Matrix::isSquare() const { return rows == cols; }

bool Matrix::isSymmetric() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = i+1; j < cols; j++)   
            if (fabs(data[i][j] - data[j][i]) > 1e-9) return false;
    return true;
}

bool Matrix::isIdentity() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fabs(data[i][j] - (i == j ? 1.0 : 0.0)) > 1e-9) return false;
    return true;
}

bool Matrix::isNull() const
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fabs(data[i][j]) > 1e-9) return false;
    return true;
}

bool Matrix::isDiagonal() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (i != j && fabs(data[i][j]) > 1e-9) return false;
    return true;
}

bool Matrix::isDiagonalDominant() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++) if (j != i) sum += fabs(data[i][j]);
        if (fabs(data[i][i]) < sum) return false;
    }
    return true;
}

bool Matrix::isTransposeOf(const Matrix& m) const
{
    if (rows != m.cols || cols != m.rows) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fabs(data[i][j] - m.data[j][i]) > 1e-9) return false;
    return true;
}

Matrix Matrix::transpose() const
{
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[j][i] = data[i][j];
    return result;
}

double Matrix::det(vector<vector<double>> mat, int n) const
{
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    double result = 0.0;
    vector<vector<double>> sub(n-1, vector<double>(n-1));
    for (int col = 0; col < n; col++) {
        for (int i = 1; i < n; i++) {
            int k = 0;
            for (int j = 0; j < n; j++) if (j != col) sub[i-1][k++] = mat[i][j];
        }
        result += (col % 2 == 0 ? 1 : -1) * mat[0][col] * det(sub, n-1);
    }
    return result;
}

double Matrix::determinant() const
{
    if (!isSquare()) throw logic_error("Determinant: matrix must be square.");
    return det(data, rows);
}

Matrix Matrix::inverse() const
{
    if (!isSquare()) throw logic_error("Inverse: matrix must be square.");
    double d = determinant();
    if (fabs(d) < 1e-12) throw runtime_error("Inverse: matrix is singular.");
    int n = rows;
    Matrix inv(n, n);
    vector<vector<double>> sub(n-1, vector<double>(n-1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int si = 0;
            for (int r = 0; r < n; r++) {
                if (r == i) continue;
                int sj = 0;
                for (int c = 0; c < n; c++) if (c != j) sub[si][sj++] = data[r][c];
                si++;
            }
            inv.data[j][i] = ((i+j) % 2 == 0 ? 1 : -1) * det(sub, n-1) / d;
        }
    return inv;
}

Matrix Matrix::createAugmented(const Matrix& right) const
{
    if (rows != right.rows) throw invalid_argument("Augmented: row count must match.");
    Matrix result(rows, cols + right.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)       result.data[i][j]        = data[i][j];
        for (int j = 0; j < right.cols; j++) result.data[i][cols + j] = right.data[i][j];
    }
    return result;
}

bool Matrix::makeDiagonalDominant()
{
    if (!isSquare()) return false;
    for (int col = 0; col < rows; col++) {
        int best = -1;
        for (int row = col; row < rows; row++) {
            double sum = 0.0;
            for (int j = 0; j < cols; j++) if (j != col) sum += fabs(data[row][j]);
            if (fabs(data[row][col]) >= sum) { best = row; break; }
        }
        if (best == -1) return false;
        if (best != col) swap(data[col], data[best]);
    }
    return true;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++)
            os << setw(10) << fixed << setprecision(4) << m.data[i][j];
        os << "\n";
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            if (!(is >> m.data[i][j])) throw runtime_error("istream: insufficient data.");
    return is;
}