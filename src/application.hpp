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
            
            std::vector<CanvasDrawable*> shapes;
            shape::Line down = shape::Line::from(400, 400)
                .to(400, 500)
                .build();
            shapes.push_back(&down);

            shape::Line rightdown = shape::Line::from(400, 400)
                .to(500, 500)
                .build();
            shapes.push_back(&rightdown);

            shape::Line leftdown = shape::Line::from(400, 400)
                .to(300, 500)
                .build();
            shapes.push_back(&leftdown);

            shape::Line right = shape::Line::from(400, 400)
                .to(500, 401)
                .build();
            shapes.push_back(&right);

            shape::Line rightup = shape::Line::from(400, 400)
                .to(500, 300)
                .build();
            shapes.push_back(&rightup);

            shape::Line leftup = shape::Line::from(400, 400)
                .to(300, 300)
                .build();
            shapes.push_back(&leftup);

            shape::Line up = shape::Line::from(400, 400)
                .to(400, 300)
                .build();
            shapes.push_back(&up);

            shape::Line left = shape::Line::from(400, 400)
                .to(300, 400)
                .build();
            shapes.push_back(&left);

            // Begin assignment box with dot in the center
            this->canvas->setPixel(75, 75, Color::Red());

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

            // End assignment box with dot in the center

            // End canvas draw

            // TODO
            // Shouldn't be call this, it should be done automatically
            // when the canvas was drawn
            this->canvas->update();

            this->window->draw(*(this->canvas));
            this->window->draw(fps);
            this->window->display();
        }
    }
};