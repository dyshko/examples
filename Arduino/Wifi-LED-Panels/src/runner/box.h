#ifndef BOX_H
#define BOX_H


class Box
{
public:
    Box();
    Box(int x, int y, int width, int height);

    bool collision(const Box& other) const;
    bool onTopOf(const Box& other) const;

    int x;
    int y;
    int width;
    int height;
};

#endif // BOX_H
