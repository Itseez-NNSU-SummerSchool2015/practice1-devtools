#include "matrix.hpp"

#include <time.h>
#include <stdlib.h>

using namespace std;

void Matrix::alloc(int rows, int cols)
{
    values = new uchar*[rows];
    for (int i = 0; i < rows; i++)
    {
        values[i] = new uchar[cols];
    }
}

Matrix::Matrix(int _kRows, int _kCols) : kRows(_kRows), kCols(_kCols)
{
    alloc(kRows, kCols);
}

Matrix::Matrix(const Matrix& m) : kRows(m.kRows), kCols(m.kCols)
{
    alloc(kRows, kCols);
    copy(m);
}

int Matrix::rows() const
{
    return kRows;
}

int Matrix::cols() const
{
    return kCols;
}

uchar** Matrix::data() const
{
    return values;
}

uchar* Matrix::operator[](int i) const
{
    return values[i];
}

void Matrix::Zeros()
{
    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            values[i][j] = 0;
        }
    }
}

void Matrix::Ones()
{
    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            values[i][j] = 1;
        }
    }
}

void Matrix::Random(int seed)
{
    srand(seed);

    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            values[i][j] = (uchar) (rand() % 256);
        }
    }
}

void Matrix::free()
{
    for (int i = 0; i < kRows; i++)
    {
        delete [] values[i];
    }
    delete [] values;
}

Matrix::~Matrix()
{
    free();
}

bool Matrix::operator==(const Matrix& m) const
{
    if (kRows != m.kRows || kCols != m.kCols)
    {
        return false;
    }

    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            if (values[i][j] != m[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

void Matrix::copy(const Matrix& m)
{
    for (int i = 0; i < m.kRows; i++)
    {
        for (int j = 0; j < m.kCols; j++)
        {
            values[i][j] = m.values[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (!(m == *this))
    {
        free();
        kRows = m.kRows;
        kCols = m.kCols;
        alloc(m.kRows, m.kCols);
        copy(m);
    }
    return *this;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    os << endl;

    os << "Matrix size: " << m.rows() << " x " << m.cols() << endl;

    // We limit number of printed elements to fit to the screen
    os << "Top-left 10x10 corner of the matrix is:" << endl;
    for (int i = 0; i < m.kRows && i < 10; i++)
    {
        for (int j = 0; j < m.kCols && j < 10; j++)
        {
            os << (int)(m.values[i][j]) << '\t';
        }
        os << endl;
    }

    return os;
}
