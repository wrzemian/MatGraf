//
// Created by wrzos on 08.11.2022.
//

#include "../include/Matrix.h"
#include <iomanip>      // std::setprecision


Matrix::Matrix(const double *inValues) {
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

Vector Matrix::multiplyByVector(Vector v) {
    double vecTab[4] = {v.getX(), v.getY(), v.getZ(), v.getW()};
    double result[4] = {0};
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            result[i]+=( entries[i][j]*vecTab[j]);
        }
    }
    return {result[0], result[1], result[2], result[3]};
}

Matrix Matrix::transpose() {
    double temp[16];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            temp[j*4 + i] = entries[i][j];
        }
    return Matrix(temp);
}
Matrix Matrix::inverse() {
    double det = this->getDeterminant();
    if (det != 0) {
        // Find adjoint
        double adj[4][4];
        double A[4][4];
        double inverse[16];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                A[i][j] = entries[i][j];
            }
        }
        adjoint(A, adj);

        // Find Inverse using formula "inverse(A) =
        // adj(A)/det(A)"
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                inverse[i*4 + j] = adj[i][j] / det;

        return Matrix(inverse);
    }


}

void Matrix::readyIdentity() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            if(i == j)
                entries[i][j] = 1;
            else
                entries[i][j] = 0;
        }
}

double Matrix::getDeterminant(double matrix[4][4], int n)
{
    double determinant = 0;
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    double temp[4][4];
    int sign = 1;
    for (int i = 0; i < n; i++) {
        getCofactor(matrix, temp, 0, i, n);
        determinant += sign * matrix[0][i] * getDeterminant(temp, n - 1);
        sign = -sign;
    }
    return determinant;
}

double Matrix::getDeterminant()
{
    int n = 4;
    double matrix[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = entries[i][j];
        }
    }
    double determinant = 0;
    double temp[4][4];
    int sign = 1;
    for (int i = 0; i < n; i++) {
        getCofactor(matrix, temp, 0, i, n);
        determinant += sign * matrix[0][i] * getDeterminant(temp, n - 1);
        sign = -sign;
    }
    return determinant;
}

void Matrix::getCofactor(double matrix[4][4], double temp[4][4], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void Matrix::adjoint(double A[4][4], double adj[4][4]) {

    int sign = 1;
    double temp[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, 4);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign) * (getDeterminant(temp, 4 - 1));
        }
    }
}


std::string Matrix::str() const {
    std::stringstream ss;
    ss << "|";
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
           ss << " " << std::setprecision(3)  << std::setw(6) << entries[i][j] << " ";
        }
        if(i != 3)
            ss << "|\n|";
        else
            ss << "|";
    }
    ss << "\n";
    return ss.str();
}

double Matrix::getEntry(int i, int j) {
    return entries[i][j];
}

void Matrix::readyTranslation(Vector translationVec) {
    this->readyIdentity();
    entries[0][3] = translationVec.getX();
    entries[1][3] = translationVec.getY();
    entries[2][3] = translationVec.getZ();
    entries[3][3] = translationVec.getW();
}

void Matrix::readyScale(Vector scaleVec) {
    this->readyIdentity();
    entries[0][0] = scaleVec.getX();
    entries[1][1] = scaleVec.getY();
    entries[2][2] = scaleVec.getZ();
    entries[3][3] = scaleVec.getW();
}

void Matrix::readyRotationAxis(Vector axis, double angle) {
    Vector u = axis.normalise();

    double sinAngle = sin(M_PI*angle / 180);
    double cosAngle = cos(M_PI*angle / 180);
    double oneMinusCosAngle = 1 - cosAngle;

    this->readyIdentity();

    entries[0][0] = u.getX() * u.getX() + cosAngle * (1 - u.getX() * u.getX());
    entries[1][0] = u.getX() * u.getY() * oneMinusCosAngle - sinAngle * u.getZ();
    entries[2][0] = u.getX() * u.getZ() * oneMinusCosAngle + sinAngle * u.getY();

    entries[0][1] = u.getX() * u.getY() * oneMinusCosAngle + sinAngle * u.getZ();
    entries[1][1] = u.getY() * u.getY() + cosAngle * (1 - u.getY() * u.getY());
    entries[2][1] = u.getY() * u.getZ() * oneMinusCosAngle - sinAngle * u.getX();

    entries[0][2] = u.getX() * u.getZ() * oneMinusCosAngle - sinAngle * u.getY();
    entries[1][2] = u.getY() * u.getZ() * oneMinusCosAngle + sinAngle * u.getX();
    entries[2][2] = u.getZ() * u.getZ() + cosAngle * (1 - u.getZ() * u.getZ());
}

void Matrix::readyRotationX(double angle) {
    this->readyIdentity();

    entries[1][1] = round(cos(M_PI*angle / 180)*1000)/1000;
    entries[1][2] = round(sin(M_PI*angle / 180)*1000)/1000;
    entries[2][1] = -entries[1][2];
    entries[2][2] = entries[1][1];
}

void Matrix::readyRotationY(double angle) {
    this->readyIdentity();

    entries[0][0] = round(cos(M_PI*angle / 180)*1000)/1000;
    entries[0][2] = round(-sin(M_PI*angle / 180)*1000)/1000;
    entries[2][0] = -entries[0][2];
    entries[2][2] = entries[0][0];
}

void Matrix::readyRotationZ(double angle) {
    this->readyIdentity();

    entries[0][0] = round(cos(M_PI*angle / 180)*1000)/1000;
    entries[0][1] = round(sin(M_PI*angle / 180)*1000)/1000;
    entries[1][0] = -entries[0][1];
    entries[1][1] = entries[0][0];
}

bool Matrix::equals(Matrix m) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(entries[i][j] != m.entries[i][j])
            return false;
        }
    }
    return true;
}






