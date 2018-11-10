#ifndef PLATFORM_H
#define PLATFORM_H

#include "box.h"

class Platform: public Box
{
public:
    Platform();
    Platform(int x, int y, int width);
};

#endif // PLATFORM_H
