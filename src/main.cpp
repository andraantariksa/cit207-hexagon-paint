// 0. Naive    // Have a problem
// 1. EQUATION // TODO
// 2. DDA
// 3. MID      // TODO
//#define _LINE_ALGORITHM 2

#define STB_IMAGE_IMPLEMENTATION
#include "application.hpp"

int main(int argc, char *argv[])
{
    Application app(1000, 600, sf::String("Hexagon Paint"));
    app.dispatch();
    return 0;
}
