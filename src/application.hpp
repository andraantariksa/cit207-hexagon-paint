#pragma once

class Application
{
    private:
    Window *window;

    public:
    size_t window_width;
    size_t window_height;

    Application(const unsigned int window_width, const unsigned int window_height, sf::String title)
    {
        this->window_width = window_width;
        this->window_height = window_height;
        this->window = new Window(window_width, window_height, title);
    }

    ~Application()
    {
        delete this->window;
    }

    void dispatch()
    {
        printf("%lf\n", this->window->lineSlope(0, 0, 100, 300) * 180.0 / PI);
        while (this->window->isOpen())
        {
            sf::Event event;

            while (this->window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
            }

            this->window->clear();
            
            // Begin draw
            
            this->window->line(0, 0, 100, 300, Color::Red());
            
            // End draw
            
            this->window->update();
            this->window->display();
        }
    }
};