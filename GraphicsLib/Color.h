#pragma once

#include <SFML/Graphics.hpp>

#include <Trackable.h>

class GraphicsSystem;

class Color :public Trackable
{
	friend class GraphicsBuffer;//allows GraphicsBuffer functions to call getAllegroColorFromColor
public:
	Color() {};//default constructor
	Color(int r, int g, int b, int a = 255);//construct Color from int values
	Color(float r, float g, float b, float a = 1.0f);//construct Color from float values

	//implement these functions for real
	int getR() const { return mR; };
	int getG() const { return mG; };
	int getB() const { return mB; };
	int getA() const { return mA; };
	float getRf() const { return mR / 255.0f;  }
	float getGf() const { return mG / 255.0f; }
	float getBf() const { return mB / 255.0f; }
	float getAf() const { return mA / 255.0f; }

private:
	//use variable(s) to hold values to represent color
	unsigned char mR = 0, 
		mG = 0, 
		mB = 0,
		mA = 0;

	const int MAX_COLOR_VALUE = 255;

	//map a Color to an ALLEGRO_COLOR
	//static ALLEGRO_COLOR getAllegroColorFromColor(const Color& color);

	//map a Color to an SFML Color
	static sf::Color getSFMLColorFromColor(const Color& color);
	
};
