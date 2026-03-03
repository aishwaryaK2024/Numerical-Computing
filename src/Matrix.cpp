#include "Matrix.hpp"

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(rows, std::vector<double>(cols, 0));
}

Matrix::Matrix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file");
    file >> rows >> cols;
    data.resize(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            file >> data[i][j];
}

void Matrix::display() const {
    std::cout << *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    if (rows != m.rows || cols != m.cols) throw std::runtime_error("Dimension mismatch");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] + m.data[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& m) const {
    if (rows != m.rows || cols != m.cols) throw std::runtime_error("Dimension mismatch");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] - m.data[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& m) const {
    if (cols != m.rows) throw std::runtime_error("Dimension mismatch for multiplication");
    Matrix result(rows, m.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < m.cols; j++)
            for (int k = 0; k < cols; k++)
                result.data[i][j] += data[i][k] * m.data[k][j];
    return result;
}

Matrix Matrix::operator/(double scalar) const {
    if (scalar == 0) throw std::runtime_error("Division by zero");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] / scalar;
    return result;
}

bool Matrix::operator==(const Matrix& m) const {
    if (rows != m.rows || cols != m.cols) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (data[i][j] != m.data[i][j]) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++)
            os << m.data[i][j] << " ";
        os << "\n";
    }
    return os;
}

Matrix Matrix::createAugmented(const Matrix& right) const {
    if (rows != right.rows) throw std::runtime_error("Row mismatch");
    Matrix result(rows, cols + right.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j];
        for (int j = 0; j < right.cols; j++)
            result.data[i][cols + j] = right.data[i][j];
    }
    return result;
}