#pragma once

#include <vector>
#include <unordered_map>

class Snake
{
public:

    enum Dir {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };

    struct Cell{
        int x = -1;
        int y = -1;

        Cell() = default;
        Cell(int x, int y);

        bool operator!=(const Cell& other) const;

        bool operator==(const Cell& other) const;
    };

    struct CellHasher{
        std::size_t operator()(const Cell& c) const;
    };

    struct SnakeNode : public Cell{
        SnakeNode(int x, int y);
        SnakeNode(const Cell& c);
        Cell getNextCell(Dir d, int width, int height);
    };
    
    Snake(int width, int height, unsigned int seed);

    void setDir(Dir d);

    bool move();

    void dropFood();

    bool full();

    bool cellFood(const Cell& c);

    bool cellFree(const Cell& c);

    int width() const;
    int height() const;
    Cell head() const;

private:

    bool validCell(const Cell& c);

private:
    std::vector<SnakeNode> m_nodes;
    Cell m_food;
    int m_width;
    int m_height;
    Dir m_dir;

    std::unordered_map<Cell, bool, CellHasher> m_freeCells;
};
