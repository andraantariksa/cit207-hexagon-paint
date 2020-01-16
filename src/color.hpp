#pragma once

class Color
{
    private:
    sf::Uint8 red;
    sf::Uint8 green;
    sf::Uint8 blue;
    sf::Uint8 alpha;

    public:
    Color()
    {
        this->red = 0;
        this->green = 0;
        this->blue = 0;
    }

    Color(float rgb[3])
    {
        this->red = rgb[0] * 255.0;
        this->green = rgb[1] * 255.0;
        this->blue = rgb[2] * 255.0;
        this->alpha = 255;
    }

    Color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

    inline sf::Uint8 getRed()
    {
        return this->red;
    }

    inline sf::Uint8 getGreen()
    {
        return this->green;
    }

    inline sf::Uint8 getBlue()
    {
        return this->blue;
    }

    inline sf::Uint8 getAlpha()
    {
        return this->alpha;
    }

    static inline Color Red()
    {
        Color color(255, 0, 0, 255);
        return color;
    }

    static inline Color Green()
    {
        Color color(0, 255, 0, 255);
        return color;
    }

    static inline Color Blue()
    {
        Color color(0, 0, 255, 255);
        return color;
    }

    static inline Color Black()
    {
        Color color(255, 255, 255, 255);
        return color;
    }
};