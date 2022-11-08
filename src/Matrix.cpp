//
// Created by wrzos on 08.11.2022.
//

#include "../include/Matrix.h"


Matrix::Matrix(double *inValues) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            entries[i][j] = inValues[i*4 + j];
        }
    }
}

void Matrix::add(Matrix m) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            entries[i][j] += m.entries[i][j];
        }
    }
}

void Matrix::sub(Matrix m) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            entries[i][j] -= m.entries[i][j];
        }
    }
}

Matrix Matrix::multpily(double a) const {
    double temp[16];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp[i*4 + j] = a*entries[i][j];
        }
    }
    return Matrix(temp);
}

Matrix Matrix::multiplyByMatrix(Matrix m) {
    double temp[16] = {0};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++)
                temp[i*4 + j] += entries[i][k] * m.entries[k][j];
        }
    }
    return Matrix(temp);
}

Matrix Matrix::transpose() {
    double temp[16];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            temp[j*4 + i] = entries[i][j];
        }
    return Matrix(temp);
}

void Matrix::loadIdentity() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            if(i == j)
                entries[i][j] = 1;
            else
                entries[i][j] = 0;
        }
}

double Matrix::getDeterminant(int n)
{
    double D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return entries[0][0];

    int temp[4][4]; // To store cofactors

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(temp, 0, f, n);
        D += sign * entries[0][f]
             * getDeterminant(n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

void Matrix::getCofactor(int temp[4][4], int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q)
            {
                temp[i][j++] = entries[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

std::string Matrix::str() const {
    std::stringstream ss;
    ss << "|";
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
           ss << " " << entries[i][j] << " ";
        }
        if(i != 3)
            ss << "|\n|";
        else
            ss << "|";
    }
    return ss.str();
}

float Matrix::getEntry(int i, int j) {
    return entries[i][j];
}


