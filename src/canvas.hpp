#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <cstdio>

#include "color.hpp"

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

    void line(size_t x1, size_t y1, size_t x2, size_t y2, Color color)
    {
        #if _LINE_ALGORITHM == 1

        double delta_y = (double) (y2 - y1);
        double delta_x = (double) (x2 - x1);
        double gradient = delta_y / delta_x;

        double c = (double) y1 - gradient * (double) x1;
        
        for (size_t x = x1; x <= x2; x++)
        {
            double y = gradient * (double) x + c;
            this->setPixel(x, (size_t) std::round(y), color);
        }

        #elif _LINE_ALGORITHM == 2
        
        double delta_y = (double) (y2 - y1);
        double delta_x = (double) (x2 - x1);
        double gradient = delta_y / delta_x;

        size_t x = x1;
        double y = (double) y1;

        while (x <= x2)
        {
            this->setPixel(x, (size_t) std::round(y), color);
            x += 1;
            y += gradient;
        }

        #elif _LINE_ALGORITHM == 3
        
        // TODO

        size_t delta_y = y2 - y1;
        size_t delta_x = x2 - x1;

        size_t D = 2 * delta_y - delta_x;
        size_t y = y1;

        for (size_t x = x1; x <= x2; x++)
        {
            this->setPixel(x, y, color);
            if (D > 0)
            {
                y += 1;
                D = D - 2 * delta_x;
            }
            D = D + 2 * delta_y;
        }

        #endif
    }

    double lineSlope(size_t x1, size_t y1, size_t x2, size_t y2)
    {
        double delta_y = (double)(y2 - y1);
        double delta_x = (double)(x2 - x1);
        double gradient = delta_y / delta_x;
        return std::atan(gradient);
    }

    void update()
    {
        this->texture.update(this->pixels);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite);
    }
};
