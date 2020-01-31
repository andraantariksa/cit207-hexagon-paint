#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

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
    sf::Uint8 *pixels_alternate;
    sf::Vector2f position;
    unsigned int width;
    unsigned int height;
    bool is_alternate_on;

    public:
    Canvas(const unsigned int width, const unsigned int height, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f))
    {
        this->is_alternate_on = false;
        this->width = width;
        this->height = height;
        this->position = position;
        this->sprite.setPosition(position);
        this->pixels = new sf::Uint8[this->width * this->height * 4];
        this->texture.create(this->width, this->height);
        this->sprite.setTexture(this->texture);
        this->clear();
    }

    unsigned int getWidth() const
    {
        return this->width;
    }

    inline unsigned int getHeight() const
    {
        return this->height;
    }

    inline bool isAlternateOn()
    {
        return this->is_alternate_on;
    }

    inline void alternateBegin()
    {
        this->is_alternate_on = true;
        this->pixels_alternate = new sf::Uint8[this->width * this->height * 4];
        std::copy(this->pixels, this->pixels + (this->width * this->height * 4), this->pixels_alternate);
    }

    inline void alternateFromMain()
    {
        std::copy(this->pixels, this->pixels + (this->width * this->height * 4), this->pixels_alternate);
    }

    inline void alternateEnd()
    {
        this->is_alternate_on = false;
        delete this->pixels_alternate;
    }

    inline void alternateSetPixel(int x, int y, Color color)
    {
        const int current_pixel_pos = (x + (y * this->width)) * 4;
        this->pixels_alternate[current_pixel_pos] = color.getRed();
        this->pixels_alternate[current_pixel_pos + 1] = color.getGreen();
        this->pixels_alternate[current_pixel_pos + 2] = color.getBlue();
        this->pixels_alternate[current_pixel_pos + 3] = color.getAlpha();
    }

    inline void alternateUpdate()
    {
        this->texture.update(this->pixels_alternate);
    }

    inline bool save(const char* const file_name)
    {
        return (bool) lodepng_encode32_file(file_name, this->pixels, this->width, this->height);
    }

    inline bool load(const char* const file_name)
    {
		sf::Uint8 *temp_source;
        unsigned int loaded_width, loaded_height;
		if (lodepng_decode32_file(&temp_source, &loaded_width, &loaded_height, file_name))
		{
			return false;
		}

		if (this->width != loaded_width || this->height != loaded_height)
		{
			return false;
		}

		std::memcpy(this->pixels, temp_source, this->width * this->height * 4);
		std::free(temp_source);
		return true;
    }


    inline void setPosition(sf::Vector2f position)
    {
        this->position = position;
        this->sprite.setPosition(position);
    }

    inline sf::Vector2f getPosition()
    {
        return this->sprite.getPosition();
    }

    ~Canvas()
    {
        delete pixels;
    }

    inline void setPixel(int x, int y, Color color)
    {
        const int current_pixel_pos = (x + (y * this->width)) * 4;
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
