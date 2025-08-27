#include "Animation.h"

Animation::Animation()
{}

Animation::Animation(float speed, bool canLoop)
{
	setSpeed(speed);
	mCanLoop = canLoop;
}

/// <summary>
/// Sprite sheet constructor
/// </summary>
/// <param name="speed"></param>
/// <param name="canLoop"></param>
/// <param name="spriteBuffer"></param>
/// <param name="pixelWidth"></param>
/// <param name="pixelHeight"></param>
/// <param name="spritesAcross"></param>
/// <param name="spritesDown"></param>
Animation::Animation(float speed, bool canLoop, sf::Texture* texture, int pixelWidth, int pixelHeight, int spritesAcross, int spritesDown, Vector2D startPoint)
{
	setSpeed(speed);
	mCanLoop = canLoop;

	//Add sprites to animation
	for (unsigned int x = 0; x < (unsigned)spritesDown; x++)
	{
		for (unsigned int y = 0; y < (unsigned)spritesAcross; y++)
		{
			Sprite sprite(texture, Vector2D((int)((y + startPoint.getY()) * pixelWidth), (int)((x + startPoint.getX()) * pixelHeight)), pixelWidth, pixelHeight);
			addSprite(sprite);
		}
	}
}

Animation::Animation(float speed, bool canLoop, sf::Texture* texture, int pixelWidth, int pixelHeight)
{
	setSpeed(speed);
	mCanLoop = canLoop;
	Sprite sprite(texture, Vector2D(0, 0), pixelWidth, pixelHeight);
	addSprite(sprite);
}

//Destroy in game instead
Animation::~Animation()
{}

void Animation::update(float deltaTime)
{
	//Subtract from time between sprites
	mTimeUntilNextFrame -= deltaTime;

	if (mTimeUntilNextFrame <= 0)
	{
		mSpriteIndex++;
		mTimeUntilNextFrame = mTimePerFrame;

		//Loop animation
		if (mCanLoop)
		{
			mSpriteIndex %= mSpriteList.size();
		}
		//Otherwise 'pause' on last animation
		else
		{
			mSpriteIndex = mSpriteList.size() - 1;
		}
	}
}

void Animation::addSprite(Sprite newSprite)
{
	mSpriteList.push_back(newSprite);
}

void Animation::setSpeed(float speed)
{
	mTimePerFrame = 1000.0f / speed;
}

void Animation::reset()
{
	mSpriteIndex = 0;
}
