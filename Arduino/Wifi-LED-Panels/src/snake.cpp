#include "snake.h"
#include <random>

Snake::Cell::Cell(int x, int y):
    x(x),
    y(y)
{}

bool Snake::Cell::operator!=(const Cell& other) const{
    return !(*this == other);
}

bool Snake::Cell::operator==(const Cell& other) const{
    return (x==other.x && y==other.y);
}

std::size_t Snake::CellHasher::operator()(const Cell& c) const
{
    using std::hash;
    return ((hash<int>()(c.x)^ (hash<int>()(c.y) << 1)) >> 1);
}

Snake::SnakeNode::SnakeNode(int x, int y):
    Cell(x,y)
{}

Snake::SnakeNode::SnakeNode(const Cell& c):
    Cell(c)
{}

Snake::Cell Snake::SnakeNode::getNextCell(Snake::Dir d, int width, int height){
    Cell c;
    switch (d){
        case UP:
            c.x = x;
            c.y = y-1;
        break;
        case DOWN:
            c.x = x;
            c.y = y+1;
        break;
        case LEFT:
            c.x = x-1;
            c.y = y;
        break;
        case RIGHT:
            c.x = x+1;
            c.y = y;
        break;
    }
    return c;
}

Snake::Snake(int width, int height, unsigned int seed):
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

void Snake::setDir(Dir d){
    SnakeNode head = m_nodes.at(0);
    Cell next = head.getNextCell(d, m_width, m_height);
    if (m_nodes.size() > 1 && next == m_nodes.at(1))
        return;
    else
        m_dir = d;
}

bool Snake::move(){
    SnakeNode head = m_nodes.at(0);
    Cell next = head.getNextCell(m_dir, m_width, m_height);

    if (!validCell(next))
        return false;

    if (m_nodes.size() > 1 && next == m_nodes.at(1))
    {
        return false;
    }
    if (!cellFree(next))
        return false;

    Cell last = m_nodes[m_nodes.size()-1];

    for (unsigned int i = m_nodes.size()-1; i >= 1; --i)
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

bool Snake::validCell(const Cell& c)
{
    return (c.x >= 0 && c.x < m_width &&
            c.y >= 0 && c.y < m_height);
}

void Snake::dropFood(){
    if (!full()){
        int k = rand() % m_freeCells.size();
        auto it = m_freeCells.begin();
        std::advance(it, k);
        m_food = it->first;
    }
}

bool Snake::full()
{
    return (m_freeCells.empty());
}

bool Snake::cellFood(const Cell& c){
    return (m_food == c);
}

bool Snake::cellFree(const Cell& c){
    return (m_freeCells.find(c)!= m_freeCells.end());
}

int Snake::width() const
{
    return m_width;
}

int Snake::height() const
{
    return m_height;
}

Snake::Cell Snake::head() const
{
    return m_nodes.at(0);
}
