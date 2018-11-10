#include "matrix.h"

using namespace std;

Matrix::Matrix(int width, int height):
    m_width(width),
    m_height(height),
    m_mat(height, vector<bool>(width, false))
{
}

void Matrix::setPixel(int x, int y, bool state)
{
    if (y < m_height && y >= 0 && x < m_width && x >= 0)
        m_mat[y][x] = state;
}

std::vector<std::vector<bool>> Matrix::getMat(bool transposed) const
{
    if (!transposed)
        return m_mat;
    std::vector<std::vector<bool>> res(width(), std::vector<bool>(height(), false));
    for (int i = 0; i < width(); ++i)
        for (int j = 0; j < height(); ++j)
            res[i][j] = m_mat[height() - 1 - j][i];
    return res;
}