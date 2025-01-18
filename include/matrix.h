#pragma once
#include <cmath>
#include <ostream>
#include <stdexcept>
#include <vector>

// Class Matrix works with double number type
class Matrix {
public:
    Matrix(const size_t rows, const size_t cols) : rows(rows), cols(cols) {
        this->data = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0.0));
    }

    ~Matrix() = default;

    [[nodiscard]] std::vector<std::vector<double>> get_data() const { return data; }

    [[nodiscard]] double at(const size_t row, const size_t col) const { return data[row][col]; }

    [[nodiscard]] size_t get_rows() const { return this->rows; }

    [[nodiscard]] size_t get_cols() const { return this->cols; }

    Matrix &operator=(const Matrix &other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix assignments must equal matrix sizes");
        }

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                this->data[i][j] = other.at(i, j);
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix assignments must equal matrix sizes");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    };

    Matrix operator-(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix assignments must equal matrix sizes");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }
        return result;
    };

    Matrix operator*(const Matrix &other) const {
        if (cols != other.get_rows()) {
            throw std::invalid_argument("Matrix assignments must equal matrix sizes");
        }
        Matrix result(rows, other.get_cols());

        // result.data[0][0] = (this->at(0, 0) * other.at(0, 0)) + (this->at(0,1) * other.at(1,0));
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < other.get_cols(); c++) {
                // pick i_th row of first one
                // pick j_th col of second one
                // multiply corresponding elements of row and col

                std::vector<double> row_i = this->data[r];
                std::vector<double> col_j = other.data[c];

                for (size_t i = 0; i < cols; i++) {
                    result.data[r][i] += row_i[i] * col_j[i];
                }
            }
        }

        return result;
    }

    Matrix operator*(const double scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = this->data[i][j] * scalar;
            }
        }
        return result;
    }

    bool operator==(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            // throw std::invalid_argument("Matrix assignments must equal matrix sizes");
            return false;
        }
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (this->at(i, j) != other.at(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            return true;
        }
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (this->at(i, j) != other.at(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    void put(const size_t row, const size_t col, const double value) { data[row][col] = value; }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        const auto d = matrix.get_data();
        for (size_t i = 0; i < matrix.get_cols(); i++) {
            for (size_t j = 0; j < matrix.get_rows(); j++) {
                os << matrix.at(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }

    void print() const { std::cout << *(this) << std::endl; }

    void transpose() {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = this->data[j][i];
            }
        }
        *this = result;
    }

    void clear() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                this->data[i][j] = 0.0;
            }
        }
    }

    [[nodiscard]] static double cofactor_determinant(const Matrix &d) {
        const size_t d_rows = d.get_rows();
        const size_t d_cols = d.get_cols();
        const auto d_data = d.get_data();

        if (d_rows != d_cols || (d_rows == 0 && d_cols == 0)) {
            throw std::invalid_argument("Matrix cofactor must equal matrix sizes");
        }
        if (d_rows == 1 && d_cols == 1) {
            return d_data[0][0];
        }
        if (d_rows == 2 && d_cols == 2) {
            return d._2x2_determinant();
        }
        double determinant = 0.0;

        const size_t SKIP_FUCKING_ROW = 0; // WE ARE GOING TO SKIP FIRST ROW ALWAYS !
        for (size_t r = 0; r < d_rows; r++) {
            Matrix minor(d_rows - 1, d_cols - 1);
            size_t minor_i = 0;
            for (size_t i = 0; i < d_cols; i++) {
                if (i == SKIP_FUCKING_ROW)
                    continue;
                size_t minor_j = 0;
                for (size_t j = 0; j < d_cols; j++) {
                    if (j == r)
                        continue;
                    minor.put(minor_i, minor_j, d_data[i][j]);
                    minor_j++;
                }
                minor_i++;
            }
            minor.print();
            auto t = std::pow(-1, 2 + r);
            std::cout << "DT : " << t * Matrix::cofactor_determinant(minor) << std::endl << std::endl;
            determinant += t * Matrix::cofactor_determinant(minor);
        }

        return determinant;
    }

    [[nodiscard]] double _2x2_determinant() const { return data[0][0] * data[1][1] - data[0][1] * data[1][0]; }
    [[nodiscard]] static double _2x2_determinant(const Matrix &d) {
        return d.at(0, 0) * d.at(1, 1) - d.at(0, 1) * d.at(1, 0);
    }

private:
    size_t rows, cols;
    std::vector<std::vector<double>> data;
};
