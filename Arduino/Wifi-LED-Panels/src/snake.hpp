#pragma once

#include <vector>
#include <random>
#include <unordered_map>

//#include <iostream>

class Snake
{
public:

    enum Dir {
        UP = 0,
        DONW,
        LEFT,
        RIGHT
    };

    struct Cell{
        int x = -1;
        int y = -1;

        Cell() = default;
        Cell(int x, int y):
            x(x),
            y(y)
        {}

        bool operator!=(const Cell& other) const{
            return !(*this == other);
        }

        bool operator==(const Cell& other) const{
            return (x==other.x && y==other.y);
        }
    };

    struct CellHasher
    {
        std::size_t operator()(const Cell& c) const
        {
            using std::hash;
            return ((hash<int>()(c.x)^ (hash<int>()(c.y) << 1)) >> 1);
        }
    };

    struct SnakeNode : public Cell{
        SnakeNode(int x, int y):
            Cell(x,y)
        {}

        SnakeNode(const Cell& c):
            Cell(c)
        {}

        Cell getNextCell(Dir d, int width, int height){
            Cell c;
            switch (d){
                case UP:
                    c.x = x;
                    c.y = y-1;
                break;
                case DONW:
                    c.x = x;
                    c.y = y+1;
                break;
                case LEFT:
                    c.x = x+1;
                    c.y = y;
                break;
                case RIGHT:
                    c.x = x-1;
                    c.y = y;
                break;
            }
            c.x = ((c.x % width) + width)%width;
            c.y = ((c.y % height) + height)%height;
            return c;
        }
    };
    
    Snake(int width, int height, int seed):
        m_width(width),
        m_height(height)
    {
        srand(seed);

        m_dir = static_cast<Dir>(rand()%4);

        int xStart = rand()%width;
        int yStart = rand()%height;

        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                m_freeCells[Cell(x,y)] = true;
        
        SnakeNode head(xStart,yStart);
        m_nodes.push_back(head);

        m_freeCells.erase(head);
        
        dropFood();
    }

    void setDir(Dir d){
        m_dir = d;
    }

    bool move(){
        SnakeNode head = m_nodes.at(0);
        Cell next = head.getNextCell(m_dir, m_width, m_height);
        if (!cellFree(next))
            return false;

        Cell last = m_nodes[m_nodes.size()-1];

        for (int i = m_nodes.size()-1; i >= 1; --i)
            m_nodes[i] = m_nodes[i-1];
        m_nodes[0] = next;

        m_freeCells.erase(next);

        if (next != m_food)
            m_freeCells[last] = true;
        else{
            dropFood();
            m_nodes.push_back(last);
        }
        return true;
    }

    void dropFood(){
        if (!full()){
            int k = rand()%m_freeCells.size();
            auto it = m_freeCells.begin();
            std::advance(it, k);
            m_food = it->first;
        }
    }

    bool full()
    {
        return (m_freeCells.empty());
    }

    bool cellFood(const Cell& c){
        return (m_food == c);
    }

    bool cellFree(const Cell& c){
        return (m_freeCells.find(c)!= m_freeCells.end());
    }

private:
    std::vector<SnakeNode> m_nodes;
    Cell m_food;
    int m_width;
    int m_height;
    Dir m_dir;

    std::unordered_map<Cell, bool, CellHasher> m_freeCells;
};
