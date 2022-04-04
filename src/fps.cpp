#include "fps.hpp"

#include <SFML/Graphics.hpp>

FPS::FPS(unsigned int character_size, const char* font_file_location)
{
    this->current_time = 0;
    this->character_size = character_size;
    this->frame_per_second_font.loadFromFile(font_file_location);
}

void FPS::start()
{
    current_time = clock.restart().asSeconds();
}

void FPS::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    float current_frame_per_second = 1.0 / current_time;

    // Convert to C string
    char frame_per_second_string[10];
    std::sprintf(frame_per_second_string, "FPS: %d", (int)current_frame_per_second);

    sf::Text frame_per_second_text(sf::String(frame_per_second_string),
        this->frame_per_second_font, this->character_size);
    frame_per_second_text.setPosition(sf::Vector2f(0, 500));
    target.draw(frame_per_second_text);
}