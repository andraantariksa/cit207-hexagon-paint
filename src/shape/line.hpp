#ifndef _SHAPE_LINE_HPP
#define _SHAPE_LINE_HPP

#include "../canvas.hpp"
#include "../color.hpp"

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

		void draw(Canvas* canvas) override;

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
			LineBuilder();

			LineBuilder from(int x1, int y1);

			LineBuilder to(int x2, int y2);

			LineBuilder withColor(Color color);

			LineBuilder withWidth(int width);

			LineBuilder isDotted(bool is_dotted);

			Line build();
		};

	public:
		Line(int x1, int y1, int x2, int y2, Color color = Color::Red(), bool is_dotted = false, int width = 1);

		static LineBuilder from(int x1, int y1);

		static float slope(int x1, int y1, int x2, int y2);
	};
}

#endif
