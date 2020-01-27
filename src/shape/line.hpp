#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <algorithm>
#include <cstdio>

#include "../canvas.hpp"

namespace shape
{
    class Line: public CanvasDrawable
    {
        private:
        Color color;
        std::size_t x1;
        std::size_t y1;
        std::size_t x2;
        std::size_t y2;
        std::size_t width;
        bool is_dotted;

        void draw(Canvas* canvas) override
        {
            int delta_y = (int) y2 - (int) y1;
            int delta_x = (int) x2 - (int) x1;
            float m = (float) delta_y / (float) delta_x;
            float n = (float) delta_x / (float) delta_y;
            if (!canvas->isAlternateOn())
            {
                // Horizontal case
                if (delta_y == 0)
                {
                    // To down
                    if (x1 > x2)
                    {
                        for (std::size_t x = x2; x <= x1; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x, y1, this->color);
                            }
                        }
                    }
                    // To up
                    else
                    {
                        for (std::size_t x = x1; x <= x2; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x, y1, this->color);
                            }
                        }
                    }
                }
                // Vertical case
                else if (delta_x == 0)
                {
                    // To left
                    if (y1 > y2)
                    {
                        for (std::size_t y = y2; y <= y1; ++y)
                        {
                            if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x1, (std::size_t) std::round(y), this->color);
                            }
                        }
                    }
                    // To right
                    else
                    {
                        for (std::size_t y = y1; y <= y2; ++y)
                        {
                            if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x1, (std::size_t) std::round(y), this->color);
                            }
                        }
                    }
                }
                // Diagonal
                else if (delta_x == delta_y)
                {
                    // To left down
                    if (delta_x < 0)
                    {
                        std::size_t total = x1 - x2;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x1 - x, y1 - x, this->color);
                            }
                        }
                    }
                    // To right up
                    else
                    {
                        std::size_t total = x2 - x1;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x1 + x, y1 + x, this->color);
                            }
                        }
                    }
                }
                // Diagonal
                else if (delta_x == -delta_y)
                {
                    // To left up
                    if (delta_x < 0)
                    {
                        std::size_t total = x1 - x2;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x1 - x, y1 + x, this->color);
                            }
                        }
                    }
                    // To right down
                    else
                    {
                        std::size_t total = x2 - x1;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->setPixel(x1 + x, y1 - x, this->color);
                            }
                        }
                    }
                }
                // Quadrant 1 sharp
                else if (delta_x > delta_y && delta_x > 0 & delta_y > 0)
                {
                    float y = y1;

                    for (std::size_t x = x1; x <= x2; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
                // Quadrant 1 steep
                else if (delta_x < delta_y && delta_x > 0 & delta_y > 0)
                {
                    float x = x1;

                    for (std::size_t y = y1; y <= y2; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 2 steep
                else if (-delta_x < delta_y && delta_x < 0 & delta_y > 0)
                {
                    float x = x1;

                    for (std::size_t y = y1; y <= y2; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 2 sharp
                else if (-delta_x > delta_y && delta_x < 0 & delta_y > 0)
                {
                    float y = y2;

                    for (std::size_t x = x2; x <= x1; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
                // Quadrant 3 steep
                else if (-delta_x < -delta_y && delta_x < 0 & delta_y < 0)
                {
                    float x = x2;

                    for (std::size_t y = y2; y <= y1; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 3 sharp
                else if (-delta_x > -delta_y && delta_x < 0 & delta_y < 0)
                {
                    float y = y2;

                    for (std::size_t x = x2; x <= x1; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
                // Quadrant 4 steep
                else if (delta_x < -delta_y && delta_x > 0 & delta_y < 0)
                {
                    float x = x2;

                    for (std::size_t y = y2; y <= y1; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 4 sharp
                else if (delta_x > -delta_y && delta_x > 0 & delta_y < 0)
                {
                    float y = y1;

                    for (std::size_t x = x1; x <= x2; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->setPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
            }
            else
            {
                // Horizontal case
                if (delta_y == 0)
                {
                    // To down
                    if (x1 > x2)
                    {
                        for (std::size_t x = x2; x <= x1; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x, y1, this->color);
                            }
                        }
                    }
                    // To up
                    else
                    {
                        for (std::size_t x = x1; x <= x2; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x, y1, this->color);
                            }
                        }
                    }
                }
                // Vertical case
                else if (delta_x == 0)
                {
                    // To left
                    if (y1 > y2)
                    {
                        for (std::size_t y = y2; y <= y1; ++y)
                        {
                            if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x1, (std::size_t) std::round(y), this->color);
                            }
                        }
                    }
                    // To right
                    else
                    {
                        for (std::size_t y = y1; y <= y2; ++y)
                        {
                            if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x1, (std::size_t) std::round(y), this->color);
                            }
                        }
                    }
                }
                // Diagonal
                else if (delta_x == delta_y)
                {
                    // To left down
                    if (delta_x < 0)
                    {
                        std::size_t total = x1 - x2;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x1 - x, y1 - x, this->color);
                            }
                        }
                    }
                    // To right up
                    else
                    {
                        std::size_t total = x2 - x1;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x1 + x, y1 + x, this->color);
                            }
                        }
                    }
                }
                // Diagonal
                else if (delta_x == -delta_y)
                {
                    // To left up
                    if (delta_x < 0)
                    {
                        std::size_t total = x1 - x2;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x1 - x, y1 + x, this->color);
                            }
                        }
                    }
                        // To right down
                    else
                    {
                        std::size_t total = x2 - x1;
                        for (std::size_t x = 0; x <= total; ++x)
                        {
                            if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                            {
                                canvas->alternateSetPixel(x1 + x, y1 - x, this->color);
                            }
                        }
                    }
                }
                // Quadrant 1 sharp
                else if (delta_x > delta_y && delta_x > 0 & delta_y > 0)
                {
                    float y = y1;

                    for (std::size_t x = x1; x <= x2; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
                // Quadrant 1 steep
                else if (delta_x < delta_y && delta_x > 0 & delta_y > 0)
                {
                    float x = x1;

                    for (std::size_t y = y1; y <= y2; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 2 steep
                else if (-delta_x < delta_y && delta_x < 0 & delta_y > 0)
                {
                    float x = x1;

                    for (std::size_t y = y1; y <= y2; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 2 sharp
                else if (-delta_x > delta_y && delta_x < 0 & delta_y > 0)
                {
                    float y = y2;

                    for (std::size_t x = x2; x <= x1; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
                // Quadrant 3 steep
                else if (-delta_x < -delta_y && delta_x < 0 & delta_y < 0)
                {
                    float x = x2;

                    for (std::size_t y = y2; y <= y1; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 3 sharp
                else if (-delta_x > -delta_y && delta_x < 0 & delta_y < 0)
                {
                    float y = y2;

                    for (std::size_t x = x2; x <= x1; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
                // Quadrant 4 steep
                else if (delta_x < -delta_y && delta_x > 0 & delta_y < 0)
                {
                    float x = x2;

                    for (std::size_t y = y2; y <= y1; ++y)
                    {
                        if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel((std::size_t) std::round(x), y, this->color);
                        }
                        x += n;
                    }
                }
                // Quadrant 4 sharp
                else if (delta_x > -delta_y && delta_x > 0 & delta_y < 0)
                {
                    float y = y1;

                    for (std::size_t x = x1; x <= x2; ++x)
                    {
                        if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
                        {
                            canvas->alternateSetPixel(x, (std::size_t) std::round(y), this->color);
                        }
                        y += m;
                    }
                }
            }
        }

        class LineBuilder
        {
            private:
            Color color;
            std::size_t x1;
            std::size_t y1;
            std::size_t x2;
            std::size_t y2;
            bool is_dotted;
            std::size_t width;

            public:
            LineBuilder()
            {
                this->is_dotted = false;
                this->color = Color::Red();
            }

            LineBuilder from(std::size_t x1, std::size_t y1)
            {
                this->x1 = x1;
                this->y1 = y1;
                return *this;
            }

            LineBuilder to(std::size_t x2, std::size_t y2)
            {
                this->x2 = x2;
                this->y2 = y2;
                return *this;
            }

            LineBuilder withColor(Color color)
            {
                this->color = color;
                return *this;
            }

            LineBuilder withWidth(std::size_t width)
            {
                this->width = width;
                return *this;
            }

            LineBuilder isDotted(bool is_dotted)
            {
                this->is_dotted = is_dotted;
                return *this;
            }

            Line build()
            {
                Line line(this->x1, this->y1, this->x2, this->y2, this->color, this->is_dotted, this->width);
                return line;
            }
        };

        public:
        Line(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, Color color = Color::Red(), bool is_dotted = false, std::size_t width = 1)
        {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->color = color;
            this->is_dotted = is_dotted;
            this->width = width;
        }

        static LineBuilder from(std::size_t x1, std::size_t y1)
        {
            LineBuilder line_builder;
            line_builder.from(x1, y1);
            return line_builder;
        }

        static float slope(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2)
        {
            float delta_y = (float)(y2 - y1);
            float delta_x = (float)(x2 - x1);
            float gradient = delta_y / delta_x;
            return std::atan(gradient);
        }
    };
}