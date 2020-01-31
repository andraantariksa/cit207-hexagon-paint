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
		int x1;
		int y1;
		int x2;
		int y2;
		int width;
		bool is_dotted;

		void draw(Canvas* canvas) override
		{
			int delta_y = y2 - y1;
			int delta_x = x2 - x1;
			float m = (float) delta_y / (float) delta_x;
			float n = (float) delta_x / (float) delta_y;

			int max_width = this->width - 1;
			int min_width = -(this->width - 1);

			if (!canvas->isAlternateOn())
			{
				// Horizontal case
				if (delta_y == 0)
				{
					// To left
					if (x1 > x2)
					{
						for (int x = x2; x <= x1; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int y_width = min_width; y_width <= max_width; ++y_width)
								{
									canvas->setPixel(x, y1 - y_width, this->color);
								}
							}
						}
					}
					// To right
					else
					{
						for (int x = x1; x <= x2; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int y_width = min_width; y_width <= max_width; ++y_width)
								{
									canvas->setPixel(x, y1 + y_width, this->color);
								}
							}
						}
					}
				}
				// Vertical case
				else if (delta_x == 0)
				{
					// To down
					if (y1 > y2)
					{
						for (int y = y2; y <= y1; ++y)
						{
							if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->setPixel(x1 + x_width, y, this->color);
								}
							}
						}
					}
					// To up
					else
					{
						for (int y = y1; y <= y2; ++y)
						{
							if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->setPixel(x1 + x_width, y, this->color);
								}
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
						int total = x1 - x2;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->setPixel(x1 - x + x_width, y1 - x, this->color);
								}
							}
						}
					}
					// To right up
					else
					{
						int total = x2 - x1;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->setPixel(x1 + x + x_width, y1 + x, this->color);
								}
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
						int total = x1 - x2;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->setPixel(x1 - x + x_width, y1 + x, this->color);
								}
							}
						}
					}
					// To right down
					else
					{
						int total = x2 - x1;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->setPixel(x1 + x + x_width, y1 - x, this->color);
								}
							}
						}
					}
				}
				// Quadrant 1 sharp
				else if (delta_x > delta_y && delta_x > 0 & delta_y > 0)
				{
					float y = y1;

					for (int x = x1; x <= x2; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->setPixel(x, (int) std::round(y) + x_width, this->color);
							}
						}
						y += m;
					}
				}
				// Quadrant 1 steep
				else if (delta_x < delta_y && delta_x > 0 & delta_y > 0)
				{
					float x = x1;

					for (int y = y1; y <= y2; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->setPixel((int)std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
				// Quadrant 2 steep
				else if (-delta_x < delta_y && delta_x < 0 & delta_y > 0)
				{
					float x = x1;

					for (int y = y1; y <= y2; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->setPixel((int) std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
				// Quadrant 2 sharp
				else if (-delta_x > delta_y && delta_x < 0 & delta_y > 0)
				{
					float y = y2;

					for (int x = x2; x <= x1; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->setPixel(x, (int) std::round(y) + x_width, this->color);
							}
						}
						y += m;
					}
				}
				// Quadrant 3 steep
				else if (-delta_x < -delta_y && delta_x < 0 & delta_y < 0)
				{
					float x = x2;

					for (int y = y2; y <= y1; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->setPixel((int) std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
				// Quadrant 3 sharp
				else if (-delta_x > -delta_y && delta_x < 0 & delta_y < 0)
				{
					float y = y2;

					for (int x = x2; x <= x1; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->setPixel(x, (int) std::round(y) + x_width, this->color);
							}
						}
						y += m;
					}
				}
				// Quadrant 4 steep
				else if (delta_x < -delta_y && delta_x > 0 & delta_y < 0)
				{
					float x = x2;

					for (int y = y2; y <= y1; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->setPixel((int)std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
				// Quadrant 4 sharp
				else if (delta_x > -delta_y && delta_x > 0 & delta_y < 0)
				{
					float y = y1;

					for (int x = x1; x <= x2; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->setPixel(x, (int) std::round(y) + x_width, this->color);
							}
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
					// To left
					if (x1 > x2)
					{
						for (int x = x2; x <= x1; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int y_width = min_width; y_width <= max_width; ++y_width)
								{
									canvas->alternateSetPixel(x, y1 - y_width, this->color);
								}
							}
						}
					}
						// To right
					else
					{
						for (int x = x1; x <= x2; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int y_width = min_width; y_width <= max_width; ++y_width)
								{
									canvas->alternateSetPixel(x, y1 + y_width, this->color);
								}
							}
						}
					}
				}
					// Vertical case
				else if (delta_x == 0)
				{
					// To down
					if (y1 > y2)
					{
						for (int y = y2; y <= y1; ++y)
						{
							if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->alternateSetPixel(x1 + x_width, y, this->color);
								}
							}
						}
					}
						// To up
					else
					{
						for (int y = y1; y <= y2; ++y)
						{
							if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->alternateSetPixel(x1 + x_width, y, this->color);
								}
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
						int total = x1 - x2;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->alternateSetPixel(x1 - x + x_width, y1 - x, this->color);
								}
							}
						}
					}
						// To right up
					else
					{
						int total = x2 - x1;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->alternateSetPixel(x1 + x + x_width, y1 + x, this->color);
								}
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
						int total = x1 - x2;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->alternateSetPixel(x1 - x + x_width, y1 + x, this->color);
								}
							}
						}
					}
						// To right down
					else
					{
						int total = x2 - x1;
						for (int x = 0; x <= total; ++x)
						{
							if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
							{
								for (int x_width = min_width; x_width <= max_width; ++x_width)
								{
									canvas->alternateSetPixel(x1 + x + x_width, y1 - x, this->color);
								}
							}
						}
					}
				}
					// Quadrant 1 sharp
				else if (delta_x > delta_y && delta_x > 0 & delta_y > 0)
				{
					float y = y1;

					for (int x = x1; x <= x2; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->alternateSetPixel(x, (int) std::round(y) + x_width, this->color);
							}
						}
						y += m;
					}
				}
					// Quadrant 1 steep
				else if (delta_x < delta_y && delta_x > 0 & delta_y > 0)
				{
					float x = x1;

					for (int y = y1; y <= y2; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->alternateSetPixel((int)std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
					// Quadrant 2 steep
				else if (-delta_x < delta_y && delta_x < 0 & delta_y > 0)
				{
					float x = x1;

					for (int y = y1; y <= y2; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->alternateSetPixel((int) std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
					// Quadrant 2 sharp
				else if (-delta_x > delta_y && delta_x < 0 & delta_y > 0)
				{
					float y = y2;

					for (int x = x2; x <= x1; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->alternateSetPixel(x, (int) std::round(y) + x_width, this->color);
							}
						}
						y += m;
					}
				}
					// Quadrant 3 steep
				else if (-delta_x < -delta_y && delta_x < 0 & delta_y < 0)
				{
					float x = x2;

					for (int y = y2; y <= y1; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->alternateSetPixel((int) std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
					// Quadrant 3 sharp
				else if (-delta_x > -delta_y && delta_x < 0 & delta_y < 0)
				{
					float y = y2;

					for (int x = x2; x <= x1; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->alternateSetPixel(x, (int) std::round(y) + x_width, this->color);
							}
						}
						y += m;
					}
				}
					// Quadrant 4 steep
				else if (delta_x < -delta_y && delta_x > 0 & delta_y < 0)
				{
					float x = x2;

					for (int y = y2; y <= y1; ++y)
					{
						if ((this->is_dotted && y % 9 < 4) || !this->is_dotted)
						{
							for (int y_width = min_width; y_width <= max_width; ++y_width)
							{
								canvas->alternateSetPixel((int)std::round(x) + y_width, y, this->color);
							}
						}
						x += n;
					}
				}
					// Quadrant 4 sharp
				else if (delta_x > -delta_y && delta_x > 0 & delta_y < 0)
				{
					float y = y1;

					for (int x = x1; x <= x2; ++x)
					{
						if ((this->is_dotted && x % 9 < 4) || !this->is_dotted)
						{
							for (int x_width = min_width; x_width <= max_width; ++x_width)
							{
								canvas->alternateSetPixel(x, (int) std::round(y) + x_width, this->color);
							}
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
			int x1;
			int y1;
			int x2;
			int y2;
			bool is_dotted;
			int width;

		public:
			LineBuilder()
			{
				this->is_dotted = false;
				this->color = Color::Red();
				this->width = 1;
			}

			LineBuilder from(int x1, int y1)
			{
				this->x1 = x1;
				this->y1 = y1;
				return *this;
			}

			LineBuilder to(int x2, int y2)
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

			LineBuilder withWidth(int width)
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
		Line(int x1, int y1, int x2, int y2, Color color = Color::Red(), bool is_dotted = false, int width = 1)
		{
			this->x1 = x1;
			this->y1 = y1;
			this->x2 = x2;
			this->y2 = y2;
			this->color = color;
			this->is_dotted = is_dotted;
			this->width = width;
		}

		static LineBuilder from(int x1, int y1)
		{
			LineBuilder line_builder;
			line_builder.from(x1, y1);
			return line_builder;
		}

		static float slope(int x1, int y1, int x2, int y2)
		{
			float delta_y = (float)(y2 - y1);
			float delta_x = (float)(x2 - x1);
			float gradient = delta_y / delta_x;
			return std::atan(gradient);
		}
	};
}