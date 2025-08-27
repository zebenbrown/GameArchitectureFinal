#include "Color.h"

Color::Color(int r, int g, int b, int a /*= 255*/)
{
	this->mR = r;
	this->mG = g;
	this->mB = b;
	this->mA = a;
}

Color::Color(float r, float g, float b, float a /*= 1.0f*/)
{
	this->mR = (r * MAX_COLOR_VALUE);
	this->mG = (g * MAX_COLOR_VALUE);
	this->mB = (b * MAX_COLOR_VALUE);
	this->mA = (a * MAX_COLOR_VALUE);
}


sf::Color Color::getSFMLColorFromColor(const Color& color)
{
	return sf::Color(color.getR(), color.getG(), color.getB(), color.getA());
}


