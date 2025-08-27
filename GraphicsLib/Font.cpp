
#include "Font.h"
#include <cassert>

Font::Font()
{}

Font::Font(const std::string& filename, int size)
{
	mpFont = new sf::Font(filename);
	mSize = size;
}

Font::~Font()
{
	delete mpFont;
	mpFont = nullptr;
}

int Font::getAllegroFontAlignFlag(Font::Alignment align)
{
	//Returns flag type in a format Allegro can read
	switch (align) 
	{
		case LEFT:
			return 0;
			break;

		case CENTER:
			return 1;
			break;

		case RIGHT:
			return 2;
			break;
	}

	return 0;
}
