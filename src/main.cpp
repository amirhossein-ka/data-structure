#include <iostream>
#include <stack.h>
#include <cstdlib>
#include <ctime>
#include "matrix.h"

int numbers[3] = {1, 2, 3};

int main() {
    Matrix matrix(4, 4);

    // Fill the matrix with the provided values
    matrix.put(0, 0, 19);
    matrix.put(0, 1, 19);
    matrix.put(0, 2, 18);
    matrix.put(0, 3, 11);

    matrix.put(1, 0, 7);
    matrix.put(1, 1, 20);
    matrix.put(1, 2, 3);
    matrix.put(1, 3, 13);

    matrix.put(2, 0, 2);
    matrix.put(2, 1, 5);
    matrix.put(2, 2, 5);
    matrix.put(2, 3, 10);

    matrix.put(3, 0, 11);
    matrix.put(3, 1, 18);
    matrix.put(3, 2, 20);
    matrix.put(3, 3, 9);

    matrix.print();


    double c = Matrix::cofactor_determinant(matrix);
    std::cout << c << std::endl;

    return 0;
}
