#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <cstdio>
#include <vector>

#include "color.hpp"

class Canvas;

class CanvasDrawable
{
    public:
    virtual void draw(Canvas*) = 0;
};

class Canvas: public sf::Drawable
{
    private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Uint8 *pixels;

    public:
    Canvas(const unsigned int window_width, const unsigned int window_height)
    {
        this->pixels = new sf::Uint8[window_width * window_height * 4];
        this->texture.create(window_width, window_height);
        this->sprite.setTexture(this->texture);
    }

    ~Canvas()
    {
        delete pixels;
    }

    inline void setPixel(size_t x, size_t y, Color color)
    {
        const size_t current_pixel_pos = (x + (y * 800)) * 4;
        this->pixels[current_pixel_pos] = color.getRed();
        this->pixels[current_pixel_pos + 1] = color.getGreen();
        this->pixels[current_pixel_pos + 2] = color.getBlue();
        this->pixels[current_pixel_pos + 3] = color.getAlpha();
    }

    void update()
    {
        this->texture.update(this->pixels);
    }

    void drawShapes(std::vector<CanvasDrawable*> canvas_drawables)
    {
        for (std::vector<CanvasDrawable*>::iterator it = canvas_drawables.begin();
            it != canvas_drawables.end(); ++it)
        {
            (*it)->draw(this);
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite);
    }
};

#include "shape/line.hpp"
