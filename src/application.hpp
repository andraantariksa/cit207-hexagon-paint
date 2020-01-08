#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdio>
#include <vector>

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
            
            this->canvas->setPixel(75, 75, Color::Red());
            std::vector<CanvasDrawable*> shapes;

            shape::Line line_right = shape::Line::from(100, 50)
                .to(100, 100)
                .build();
            shapes.push_back(&line_right);

            shape::Line line_left = shape::Line::from(50, 100)
                .to(50, 50)
                .build();
            shapes.push_back(&line_left);
            
            shape::Line line_bottom = shape::Line::from(50, 100)
                .to(100, 100)
                .build();
            shapes.push_back(&line_bottom);

            shape::Line line_top = shape::Line::from(50, 50)
                .to(100, 50)
                .build();
            shapes.push_back(&line_top);

            this->canvas->drawShapes(shapes);

            // End canvas draw

            this->canvas->update(); // Shouldn't be call this, it should be done automatically
                                    // when the canvas was drawn
            this->window->draw(*(this->canvas));
            this->window->draw(fps);
            this->window->display();
        }
    }
};