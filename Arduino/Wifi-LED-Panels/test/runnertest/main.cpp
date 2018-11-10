#include "../../src/runner/runnergame.h"

#include <thread>
#include <iostream>

using namespace std;

void display(const Matrix& m)
{
    vector<vector<bool>> mat = m.getMat();
    for (int i = 0; i < m.height(); ++i)
    {
        for (int j = 0; j < m.width(); ++j)
            std::cout << (mat[i][j] ? '*' : ' ');
        std::cout << std::endl;
    }
}

int main()
{
    RunnerGame rg(8, 32, 0);

    while (true)
    {
        system("cls");
        display(rg.view());
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        rg.jump();
        rg.move();
    }
    return 0;
}
