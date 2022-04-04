#ifndef _FPS_HPP
#define _FPS_HPP

#include <SFML/Graphics.hpp>

class FPS: public sf::Drawable
{
    private:
    sf::Clock clock;
    sf::Font frame_per_second_font;
    float current_time;
    unsigned int character_size;

    public:
    FPS(unsigned int character_size = 15, const char * font_file_location = "../fonts/OpenSans-Regular.ttf");

    ~FPS() = default;

    void start();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
