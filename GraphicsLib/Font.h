#pragma once

#include <SFML/Graphics.hpp>

#include <Trackable.h>

#include <string>

class GraphicsSystem;

class Font:public Trackable
{
	friend class GraphicsBuffer;//allows GraphicsBuffer functions to call getAllegroFontAlignFlag
public:
	enum Alignment
	{
		LEFT,
		CENTER,
		RIGHT
	};

	Font();
	Font(const std::string& filename,int size);
	~Font();

	int getSize() const { return mSize; };
	sf::Font* getFont() const { return mpFont; };

private:
	sf::Font* mpFont = nullptr;
	int mSize=0;

	//map our Align enum values to the allegro values
	static int getAllegroFontAlignFlag(Font::Alignment align);
};
