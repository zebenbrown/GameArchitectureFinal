#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <SFML/Graphics.hpp>

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	Sprite(sf::Texture* texture, const Vector2D& ulCorner, unsigned int width, unsigned int height);
	Sprite();//default constructor
	~Sprite();//implement this destructor

	//implement these functions for real
	sf::Texture* getTexture() const { return mpTexture; };
	const Vector2D& getSourceLoc() const { return mSourceLocation; };
	unsigned int getWidth() const { return mWidth; };
	unsigned int getHeight() const { return mHeight; };

	void setBounds(Vector2D bounds);
	Vector2D getBounds();
private:
	//add data
	GraphicsBuffer* mpSpriteBuffer;
	sf::Texture* mpTexture;
	Vector2D mSourceLocation;
	sf::RectangleShape* mpSpriteBounds;

	unsigned int mWidth = 0;
	unsigned int mHeight = 0;
};