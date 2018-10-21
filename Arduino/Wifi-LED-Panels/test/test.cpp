#include "../src/snake.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

using Strip = vector<vector<bool>>;

Strip fromSnake(Snake snake)
{
    Strip s = Strip(8, vector<bool>(8, false));

    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            Snake::Cell c(j, i);
            if (snake.cellFood(c))
                s[j][i] = true;
            else
                s[j][i] = !snake.cellFree(c);
        }
    }
    return s;
}

void print(Snake snake)
{
    cout << "Snake:" << endl;
    Strip s = fromSnake(snake);
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j)
        {
            cout << (s[j][i] ? '*' : ' ');
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    Snake snake(8, 8);
    while (true){
        print(snake);

        char c;
        cin >> c;
        switch (c)
        {
        case 'w':
            snake.setDir(Snake::Dir::UP);
            break;
        case 'a':
            snake.setDir(Snake::Dir::RIGHT);
            break;
        case 's':
            snake.setDir(Snake::Dir::DONW);
            break;
        case 'd':
            snake.setDir(Snake::Dir::LEFT);
            break;
        }
        snake.move();
        std::this_thread::sleep_for (std::chrono::seconds(0
                                                          ));
    }
    std::cout << "Hello";
}
