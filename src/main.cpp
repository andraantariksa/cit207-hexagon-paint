#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define PI 3.14159265
#include <cmath>

// 0. Naive    // Have a problem for x1 == x2 and dx < dy is not really nice
// 1. EQUATION // TODO
// 2. DDA
// 3. MID      // TODO
#define _LINE_ALGORITHM 2

#include "application.hpp"

int main(int argc, char *argv[])
{
    Application app(800, 600, sf::String("2D Computer Graphics and Animation"));
    app.dispatch();
    return 0;
}
