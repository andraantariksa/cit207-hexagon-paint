#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "fps.hpp"
#include "canvas.hpp"
#include "helpers.hpp"
#include "shape/line.hpp"

class Application
{
private:
    enum class State
    {
        Nothing,
        LineFrom,
        LineTo,
        LineDone,
        PenDraw,
        PenIdle,
    };

    sf::RenderWindow* window;
    sf::Clock clock;
    FPS fps;
    Canvas* canvas;
    State state;

public:
    Application(const unsigned int window_width, const unsigned int window_height,
        sf::String title);

    ~Application();

    void dispatch();
};

#endif
