#include "../include/Color.h"

namespace cogs
{
		Color::Color(byte _r, byte _g, byte _b, byte _a) : r(_r), g(_g), b(_b), a(_a) { }

		Color::Color(byte _rgb, byte _alpha) : r(_rgb), g(_rgb), b(_rgb), a(_alpha) { }

		Color::Color(const Color & _other) : r(_other.r), g(_other.g), b(_other.b), a(_other.a)
		{
		}

		Color & Color::operator=(const Color & _rhs)
		{
				r = _rhs.r;
				g = _rhs.g;
				b = _rhs.b;

				return *this;
		}

		bool Color::operator==(const Color & _rhs) const
		{
				return (r == _rhs.r && g == _rhs.g && b == _rhs.b && a == _rhs.a);
		}

		/* codes from http://htmlcolorcodes.com/ */

		Color Color::getWhite() noexcept
		{
				return Color(255, 255, 255, 255);
		}
		Color Color::getBlack() noexcept
		{
				return Color(0, 0, 0, 255);
		}
		Color Color::getRed() noexcept
		{
				return Color(255, 0, 0, 255);
		}
		Color Color::getGreen() noexcept
		{
				return Color(0, 128, 0, 255);
		}
		Color Color::getBlue() noexcept
		{
				return Color(0, 0, 255, 255);
		}
		Color Color::getSilver() noexcept
		{
				return Color(192, 192, 192, 255);
		}
		Color Color::getGray() noexcept
		{
				return Color(128, 128, 128, 255);
		}
		Color Color::getYellow() noexcept
		{
				return Color(255, 255, 0, 255);
		}
		Color Color::getOlive() noexcept
		{
				return Color(128, 128, 255, 255);
		}
		Color Color::getLime() noexcept
		{
				return Color(0, 255, 0, 255);
		}
		Color Color::getAqua() noexcept
		{
				return Color(0, 255, 255, 255);
		}
		Color Color::getTeal() noexcept
		{
				return Color(0, 128, 128, 255);
		}
		Color Color::getNavy() noexcept
		{
				return Color(0, 0, 128, 255);
		}
		Color Color::getFuchsia() noexcept
		{
				return Color(255, 0, 255, 255);
		}
		Color Color::getPurple() noexcept
		{
				return Color(128, 0, 128, 255);
		}
}