#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>

typedef std::vector<double> row;

class Figura;

class Matrix : public std::vector<row>
{
    friend Figura;
public:
    Matrix(std::initializer_list<row> matrix);

    Matrix(int rows, int columns);

    const Matrix operator * (const Matrix &matrix) const;

private:
    int rowCount;
    int columnCount;
};

#endif // MATRIX_H
