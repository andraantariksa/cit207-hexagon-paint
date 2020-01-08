#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define PI 3.14159265
#include <cmath>

// 1. EQUATION // TODO
// 2. DDA
// 3. MID      // TODO
#define _LINE_ALGORITHM 2

#include "application.hpp"

int main(int argc, char *argv[])
{
    Application app(800, 600, sf::String("Computer Graphics and Animation"));
    app.dispatch();
    return 0;
}
