#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>

#include "color.hpp"

#include "../lib/lodepng/lodepng.h"
// Set it up manually by renaming the lodepng.cpp to lodepng.c
#include "../lib/lodepng/lodepng.c"

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
    unsigned int width;
    unsigned int height;

    public:
    Canvas(const unsigned int width, const unsigned int height)
    {
        this->width = width;
        this->height = height;
        this->pixels = new sf::Uint8[this->width * this->height * 4];
        this->texture.create(this->width, this->height);
        this->sprite.setTexture(this->texture);
        this->clear();
    }

    unsigned int getWidth() const
    {
        return this->width;
    }
    unsigned int getHeight() const
    {
        return this->height;
    }

    inline bool save(const char* const file_name)
    {
        return (bool) lodepng_encode32_file(file_name, this->pixels, this->width, this->height);
    }

    inline bool load(const char* const file_name)
    {
        unsigned int _width, _height;
        return (bool) lodepng_decode32_file(&this->pixels, &_width, &_height, file_name);
    }


    inline void setPosition(float x, float y)
    {
        this->sprite.setPosition(sf::Vector2f(x, y));
    }

    inline sf::Vector2f getPosition()
    {
        return this->sprite.getPosition();
    }

    ~Canvas()
    {
        delete pixels;
    }

    inline void setPixel(size_t x, size_t y, Color color)
    {
        const size_t current_pixel_pos = (x + (y * this->width)) * 4;
        this->pixels[current_pixel_pos] = color.getRed();
        this->pixels[current_pixel_pos + 1] = color.getGreen();
        this->pixels[current_pixel_pos + 2] = color.getBlue();
        this->pixels[current_pixel_pos + 3] = color.getAlpha();
    }

    void update()
    {
        this->texture.update(this->pixels);
    }

    void clear()
    {
        std::memset(this->pixels, 255, this->width * this->height * 4);
    }

    void drawShapes(std::vector<CanvasDrawable*> canvas_drawables)
    {
        for (std::vector<CanvasDrawable*>::iterator it = canvas_drawables.begin();
            it != canvas_drawables.end(); ++it)
        {
            (*it)->draw(this);
        }
    }

    inline void drawShape(CanvasDrawable* canvas_drawable)
    {
        canvas_drawable->draw(this);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite);
    }
};

#include "shape/line.hpp"
