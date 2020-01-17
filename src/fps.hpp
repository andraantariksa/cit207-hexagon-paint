#pragma once

#include <SFML/Graphics.hpp>

class FPS: public sf::Drawable
{
    private:
    sf::Clock clock;
    sf::Font frame_per_second_font;
    float current_time;
    unsigned int character_size;

    public:
    FPS(unsigned int character_size = 15, const char * font_file_location = "../fonts/OpenSans-Regular.ttf")
    {
        this->current_time = 0;
        this->character_size = character_size;
        this->frame_per_second_font.loadFromFile(font_file_location);
    }

    ~FPS()
    {
    }

    void start()
    {
        current_time = clock.restart().asSeconds();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        float current_frame_per_second = 1.0 / current_time;

        // Convert to C string
        char frame_per_second_string[10];
        std::sprintf(frame_per_second_string, "FPS: %d", (int) current_frame_per_second);

        sf::Text frame_per_second_text(sf::String(frame_per_second_string),
            this->frame_per_second_font, this->character_size);
        frame_per_second_text.setPosition(sf::Vector2f(0, 500));
        target.draw(frame_per_second_text);
    }
};
