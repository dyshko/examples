#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
public:
    Matrix(int width, int height);

    void setPixel(int x, int y, bool state = true);

    std::vector<std::vector<bool>> getMat(bool transposed = false) const;

    int height() const {return m_height;}
    int width() const {return m_width;}

private:

    int m_width;
    int m_height;

    std::vector<std::vector<bool>> m_mat;
};

#endif // MATRIX_H
