#include "../src/snake.h"
#include "../src/snakesolver.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include <QProcess>

#include <stdlib.h>

using namespace std;

using Strip = vector<vector<bool>>;

#define WIDTH 32
#define HEIGHT 8

Strip fromSnake(Snake snake)
{
    Strip s = Strip(WIDTH, vector<bool>(HEIGHT, false));

    for (int i = 0; i < WIDTH; ++i){
        for (int j = 0; j < HEIGHT; ++j){
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
    for (int i = 0; i < WIDTH; ++i){
        for (int j = 0; j < HEIGHT; ++j)
        {
            cout << (s[j][i] ? '*' : ' ');
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    Snake snake(HEIGHT, WIDTH, 0);
    SnakeSolver ssolver(&snake);
    while (true){
        system("cls");
        print(snake);

//        char c;
//        cin >> c;
//        switch (c)
//        {
//        case 'w':
//            snake.setDir(Snake::Dir::UP);
//            break;
//        case 'a':
//            snake.setDir(Snake::Dir::LEFT);
//            break;
//        case 's':
//            snake.setDir(Snake::Dir::DOWN);
//            break;
//        case 'd':
//            snake.setDir(Snake::Dir::RIGHT);
//            break;
//        }
//        snake.move();

        ssolver.move();
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }
}
