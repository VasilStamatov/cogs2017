#pragma once

namespace cogs
{
		using byte = unsigned char;

		struct Color
		{
				Color() { }
				Color(byte _r, byte _g, byte _b, byte _a);
				Color(byte _rgb, byte _alpha);
				Color(const Color& _other);
				Color& operator=(const Color& _rhs);

				bool operator==(const Color& _rhs) const;

				static Color getWhite() noexcept;
				static Color getBlack() noexcept;
				static Color getRed() noexcept;
				static Color getGreen() noexcept;
				static Color getBlue() noexcept;
				static Color getSilver() noexcept;
				static Color getGray() noexcept;
				static Color getYellow() noexcept;
				static Color getOlive() noexcept;
				static Color getLime() noexcept;
				static Color getAqua() noexcept;
				static Color getTeal() noexcept;
				static Color getNavy() noexcept;
				static Color getFuchsia() noexcept;
				static Color getPurple() noexcept;

				byte r{ 0 };
				byte g{ 0 };
				byte b{ 0 };
				byte a{ 0 };
		};
}