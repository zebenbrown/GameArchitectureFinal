#pragma once

#include <Trackable.h>
#include "Sprite.h"
#include <vector>

class Sprite;

class Animation : public Trackable
{
public:
	Animation();
	Animation(float speed, bool canLoop);
	Animation(float speed, bool canLoop, sf::Texture* texture, int pixelWidth, int pixelHeight, int spritesAcross, int spritesDown, Vector2D startPoint = Vector2D(0, 0));
	Animation(float speed, bool canLoop, sf::Texture* texture, int pixelWidth, int pixelHeight);
	~Animation();

	void update(float deltaTime);

	void addSprite(Sprite newSprite);
	Sprite getCurrentSprite() { return mSpriteList[mSpriteIndex]; };

	void setSpeed(float speed); //Predifined speeds not multiplier, passing in time between frames
	void reset();
private:
	int mSpriteIndex = 0;
	std::vector<Sprite> mSpriteList;

	float mTimePerFrame = 15.0f;
	float mTimeUntilNextFrame = 15.0f;
	bool mCanLoop = false;
};

