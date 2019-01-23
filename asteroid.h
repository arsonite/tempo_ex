#ifndef ASTEROID_H
#define ASTEROID_H

#include <entity.h>

class Asteroid: public Entity
{
public:
    Asteroid();

private:
    void fly(bool outOfBounds);

    double rotation_;
};

#endif // ASTEROID_H
