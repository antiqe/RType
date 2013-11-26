#ifndef _COLOR_H_
# define _COLOR_H_

namespace Ultra
{
	class Color
	{
	public:
		enum Composante
		{
			RED = 0,
			BLUE,
			GREEN,
			ALPHA,
			COMPOSANTESIZE
		};
	private:
		unsigned char	_rgba[Color::COMPOSANTESIZE];
	public:
		Color(unsigned char red, unsigned char blue, unsigned char green, unsigned char alpha);
		Color(unsigned char rgb, unsigned char alpha);
		Color(unsigned char rgba);
		Color();
		Color(Color const& cpy);
		~Color();
		Color&	operator=(Color const& cpy);

		void			setComposante(Color::Composante composante, unsigned char value);
		unsigned char	getComposante(Color::Composante composante) const;
	};
}

#endif