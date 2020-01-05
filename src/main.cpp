#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define PI 3.14159265
#include <cmath>

// 1. EQUATION,
// 2. DDA
// 3. MID
#define _LINE_ALGORITHM 1

#include "application.hpp"

int main(int argc, char *argv[])
{
    Application app(800, 600, sf::String("Test"));
    app.dispatch();
    return 0;
}
