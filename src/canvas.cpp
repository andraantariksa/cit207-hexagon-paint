#include "canvas.hpp"

#include <lodepng.h>

Canvas::Canvas(const unsigned int width, const unsigned int height, sf::Vector2f position)
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

unsigned int Canvas::getWidth() const
{
    return this->width;
}

unsigned int Canvas::getHeight() const
{
    return this->height;
}

bool Canvas::isAlternateOn()
{
    return this->is_alternate_on;
}

void Canvas::alternateBegin()
{
    this->is_alternate_on = true;
    this->pixels_alternate = new sf::Uint8[this->width * this->height * 4];
    std::copy(this->pixels, this->pixels + (this->width * this->height * 4), this->pixels_alternate);
}

void Canvas::alternateFromMain()
{
    std::copy(this->pixels, this->pixels + (this->width * this->height * 4), this->pixels_alternate);
}

void Canvas::alternateEnd()
{
    this->is_alternate_on = false;
    delete this->pixels_alternate;
}

void Canvas::alternateSetPixel(int x, int y, Color color)
{
    const int current_pixel_pos = (x + (y * this->width)) * 4;
    this->pixels_alternate[current_pixel_pos] = color.getRed();
    this->pixels_alternate[current_pixel_pos + 1] = color.getGreen();
    this->pixels_alternate[current_pixel_pos + 2] = color.getBlue();
    this->pixels_alternate[current_pixel_pos + 3] = color.getAlpha();
}

void Canvas::alternateUpdate()
{
    this->texture.update(this->pixels_alternate);
}

bool Canvas::save(const char* const file_name)
{
    return (bool) lodepng_encode32_file(file_name, this->pixels, this->width, this->height);
}

bool Canvas::load(const char* const file_name)
{
    sf::Uint8 *temp_source;
    unsigned int loaded_width, loaded_height;
    if (lodepng_decode32_file(&temp_source, &loaded_width, &loaded_height, file_name))
    {
        printf("Can't load image, it may not encoded in PNG\n");
        return false;
    }

    if (this->width != loaded_width || this->height != loaded_height)
    {
        printf("Invalid width and height\n");
        return false;
    }

    std::memcpy(this->pixels, temp_source, this->width * this->height * 4);
    std::free(temp_source);
    return true;
}


void Canvas::setPosition(sf::Vector2f position)
{
    this->position = position;
    this->sprite.setPosition(position);
}

sf::Vector2f Canvas::getPosition()
{
    return this->sprite.getPosition();
}

Canvas::~Canvas()
{
    delete pixels;
}

void Canvas::setPixel(int x, int y, Color color)
{
    const int current_pixel_pos = (x + (y * this->width)) * 4;
    this->pixels[current_pixel_pos] = color.getRed();
    this->pixels[current_pixel_pos + 1] = color.getGreen();
    this->pixels[current_pixel_pos + 2] = color.getBlue();
    this->pixels[current_pixel_pos + 3] = color.getAlpha();
}

void Canvas::update()
{
    this->texture.update(this->pixels);
}

void Canvas::clear()
{
    std::memset(this->pixels, 255, this->width * this->height * 4);
}

void Canvas::drawShapes(std::vector<CanvasDrawable*> canvas_drawables)
{
    for (std::vector<CanvasDrawable*>::iterator it = canvas_drawables.begin();
         it != canvas_drawables.end(); ++it)
    {
        (*it)->draw(this);
    }
}

void Canvas::drawShape(CanvasDrawable* canvas_drawable)
{
    canvas_drawable->draw(this);
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}