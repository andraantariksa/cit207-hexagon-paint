#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdio>

#include "fps.hpp"
#include "canvas.hpp"

class Application
{
    private:
    sf::RenderWindow *window;
    sf::Clock clock;
    FPS fps;
    Canvas *canvas;

    public:
    Application(const unsigned int window_width, const unsigned int window_height,
        sf::String title)
    {
        this->window = new sf::RenderWindow(sf::VideoMode(window_width, window_height, 32),
            title);
        this->canvas = new Canvas(window_width, window_height);
        // 100 FPS should be enough
        this->window->setFramerateLimit(100);
    }

    ~Application()
    {
        delete this->window;
    }

    void dispatch()
    {
        while (this->window->isOpen())
        {
            fps.start();

            sf::Event event;

            while (this->window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }
            }

            this->window->clear();
            
            // Begin canvas draw
            this->canvas->line(0, 0, 100, 300, Color::Red());
            // End canvas draw

            this->canvas->update(); // Shouldn't be call this, it should be done automatically
                                    // when the canvas was drawn
            this->window->draw(*(this->canvas));
            this->window->draw(fps);
            this->window->display();
        }
    }
};