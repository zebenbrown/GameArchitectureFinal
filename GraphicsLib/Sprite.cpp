#include "Sprite.h"

Sprite::Sprite(sf::Texture* texture, const Vector2D& ulCorner, unsigned int width, unsigned int height)
{
	mpTexture = texture;
	mSourceLocation = ulCorner;
	mWidth = width;
	mHeight = height;
	mpSpriteBounds = new sf::RectangleShape(sf::Vector2f(width, height));
}

Sprite::Sprite()
{
	
	mpTexture = nullptr;
	mSourceLocation = Vector2D(0, 0);
}

Sprite::~Sprite() 
{
	//delete mpSpriteBounds;
	//mpSpriteBounds = nullptr;
}

void Sprite::setBounds(Vector2D bounds)
{
	mpSpriteBounds->setSize(sf::Vector2f(bounds.getX(), bounds.getY()));
}

Vector2D Sprite::getBounds()
{
	return Vector2D(mpSpriteBounds->getSize().x, mpSpriteBounds->getSize().y);
}
