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

        void draw(Canvas* canvas)
        {
            #if _LINE_ALGORITHM == 1

            // Have a problem when delta_x < delta_y
            double delta_y = (double)(y2 - y1);
            double delta_x = (double)(x2 - x1);
            double gradient = delta_y / delta_x;

            double c = (double) y1 - gradient * (double) x1;
            
            for (size_t x = x1; x <= x2; x++)
            {
                double y = gradient * (double) x + c;
                canvas->setPixel(x, (size_t) std::round(y), this->color);
            }

            #elif _LINE_ALGORITHM == 2
            
            if (x2 < x1 || y2 < y1)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }

            double step;
            double delta_y = (double) (y2 - y1);
            double delta_x = (double) (x2 - x1);

            if (std::abs(delta_x) >= std::abs(delta_y))
            {
                step = (std::size_t) std::abs(delta_x);
            }
            else
            {
                step = (std::size_t) std::abs(delta_y);
            }

            delta_x = delta_x / step;
            delta_y = delta_y / step;
            std::size_t x = x1;
            std::size_t y = y1;
            std::size_t i = 1;

            while (i <= step)
            {
                canvas->setPixel(x, y, this->color);
                x = x + delta_x;
                y = y + delta_y;
                i = i + 1;
            }

            #elif _LINE_ALGORITHM == 3

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

        class LineBuilder
        {
            private:
            Color color;
            std::size_t x1;
            std::size_t y1;
            std::size_t x2;
            std::size_t y2;

            public:
            LineBuilder()
            {
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

            Line build()
            {
                Line line(this->x1, this->y1, this->x2, this->y2, this->color);
                return line;
            }
        };

        public:
        Line(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, Color color = Color::Red())
        {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->color = color;
        }

        static LineBuilder from(std::size_t x1, std::size_t y1)
        {
            LineBuilder line_builder;
            line_builder.from(x1, y1);
            return line_builder;
        }

        static double slope(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2)
        {
            double delta_y = (double)(y2 - y1);
            double delta_x = (double)(x2 - x1);
            double gradient = delta_y / delta_x;
            return std::atan(gradient);
        }
    };
}