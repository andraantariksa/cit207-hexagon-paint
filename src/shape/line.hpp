#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

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
        bool is_dotted;

        void draw(Canvas* canvas)
        {
            if (!canvas->isAlternateOn())
            {
                std::size_t step;
                float delta_y = (float) ((int) y2 - (int) y1);
                float delta_x = (float) ((int) x2 - (int) x1);

                if (std::abs(delta_x) >= std::abs(delta_y))
                {
                    step = (std::size_t) std::abs(delta_x);
                }
                else
                {
                    step = (std::size_t) std::abs(delta_y);
                }

                delta_x = delta_x / (float) step;
                delta_y = delta_y / (float) step;
                float x = x1;
                float y = y1;

                for (std::size_t i = 0; i <= step; ++i)
                {
                    std::printf("%d\n", this->is_dotted);
                    if ((this->is_dotted && i % 9 < 4) || !this->is_dotted)
                    {
                        canvas->setPixel((std::size_t) std::round(x), (std::size_t) std::round(y), this->color);
                    }
                    x = x + delta_x;
                    y = y + delta_y;
                }
            }
            else
            {
                std::size_t step;
                float delta_y = (float) ((int) y2 - (int) y1);
                float delta_x = (float) ((int) x2 - (int) x1);

                if (std::abs(delta_x) >= std::abs(delta_y))
                {
                    step = (std::size_t) std::abs(delta_x);
                }
                else
                {
                    step = (std::size_t) std::abs(delta_y);
                }

                delta_x = delta_x / (float) step;
                delta_y = delta_y / (float) step;
                float x = x1;
                float y = y1;

                for (std::size_t i = 0; i <= step; ++i)
                {
                    if ((this->is_dotted && i % 9 < 4) || !this->is_dotted)
                    {
                        canvas->alternateSetPixel((std::size_t) std::round(x), (std::size_t) std::round(y), this->color);
                    }
                    x = x + delta_x;
                    y = y + delta_y;
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

            LineBuilder isDotted(bool is_dotted)
            {
                this->is_dotted = is_dotted;
                return *this;
            }

            Line build()
            {
                Line line(this->x1, this->y1, this->x2, this->y2, this->color, this->is_dotted);
                return line;
            }
        };

        public:
        Line(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, Color color = Color::Red(), bool is_dotted = false)
        {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->color = color;
            this->is_dotted = is_dotted;
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