#ifndef _CANVAS_HPP
#define _CANVAS_HPP

#include <SFML/Graphics.hpp>

#include <cmath>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

#include "color.hpp"

class CanvasDrawable;

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
    Canvas(const unsigned int width, const unsigned int height, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f));

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    bool isAlternateOn();

    void alternateBegin();

    void alternateFromMain();

    void alternateEnd();

    void alternateSetPixel(int x, int y, Color color);

    void alternateUpdate();

    bool save(const char* const file_name);

    bool load(const char* const file_name);


    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition();

    ~Canvas();

    void setPixel(int x, int y, Color color);

    void update();

    void clear();

    void drawShapes(std::vector<CanvasDrawable*> canvas_drawables);

    void drawShape(CanvasDrawable* canvas_drawable);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


class CanvasDrawable
{
public:
    virtual void draw(Canvas*) = 0;
};

#endif
