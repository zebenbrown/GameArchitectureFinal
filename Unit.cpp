#include "Unit.h"
#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>

Unit::Unit()
{
	mLocation = Vector2D(0, 0);
	mVelocity = Vector2D(1.0f, 1.0f);
}

Unit::Unit(Animation animation, Vector2D position, Vector2D velocity, std::string tag)
{
	mVelocity = velocity;
	mLocation = position;
	mAnimation = animation;
	mTag = tag;
	
}

Unit::Unit(Animation animation, Vector2D velocity, std::string tag)
{
	mVelocity = velocity;
	mAnimation = animation;
	mTag = tag;
}

Unit::Unit(Sprite sprite, Vector2D position, Vector2D velocity, std::string tag)
{
	mLocation = position;
	mVelocity = velocity;
	mTag = tag;
	mpSprite = new Sprite(sprite);
}


Unit::~Unit() 
{
	if (mpSprite != nullptr)
	{
		delete mpSprite;
		mpSprite = nullptr;
	}
	
}

void Unit::update(float deltaTime)
{
	//Set draw location
	//mDrawLocation = getCenterOffset();

	if (!mCanMove) return;

	//Prevent animating if unit can't move
	mAnimation.update(deltaTime);

	//Move across screen to right
	//mLocation.setX(mLocation.getX() + 1);

	//random movement for orb instead of right
	mLocation.setX(mLocation.getX() + mVelocity.getX());
	mLocation.setY(mLocation.getY() + mVelocity.getY());
}

void Unit::setPosition(Vector2D position)
{
	mLocation = position;
}

void Unit::setVelocity(Vector2D velocity)
{
	mVelocity = velocity;
}

void Unit::draw()
{
	mDrawLocation = getCenterOffset();
	GraphicsSystem::drawSprite(mDrawLocation, mAnimation.getCurrentSprite(), 1.0);
}

void Unit::initCar(Animation animation, Vector2D position, Vector2D velocity, std::string tag)
{
	mAnimation = animation;
	mLocation = position;
	mVelocity = velocity;
	mTag = tag;
	isCreated = true;
	isDrawable = true;
}

void Unit::initCone(Animation animation, Vector2D topLeft, Vector2D bottomRight, Vector2D velocity, std::string tag)
{
	std::random_device randomDevice;
	std::mt19937 randomGenerator(randomDevice());
	std::uniform_int_distribution<> randomXCoordinate(topLeft.getX(), bottomRight.getX());
	std::uniform_int_distribution<> randomYCoordinate(topLeft.getY(), bottomRight.getY());
	int newPositionX = randomXCoordinate(randomGenerator);
	int newPositionY = randomYCoordinate(randomGenerator);

	mAnimation = animation;
	mVelocity = velocity;
	mTag = tag;
	mLocation = Vector2D(newPositionX, newPositionY);
	isCreated = true;
	isDrawable = false;
}

void Unit::createCar(Animation animation, Vector2D position, Vector2D velocity, std::string tag)
{
	mAnimation = animation;
	mLocation = position;
	mVelocity = velocity;
	mTag = tag;
}

void Unit::createCone(Animation animation, Vector2D velocity, std::string tag)
{
	mAnimation = animation;
	mVelocity = velocity;
	mTag = tag;
}

Unit* Unit::createConeInBounds(Animation animation, Vector2D topLeft, Vector2D bottomRight, Vector2D velocity, std::string tag)
{
	std::random_device randomDevice;
	std::mt19937 randomGenerator(randomDevice());
	std::uniform_int_distribution<> randomXCoordinate(topLeft.getX(), bottomRight.getX());
	std::uniform_int_distribution<> randomYCoordinate(topLeft.getY(), bottomRight.getY());
	int newPositionX = randomXCoordinate(randomGenerator);
	int newPositionY = randomYCoordinate(randomGenerator);

	mAnimation = animation;
	mVelocity = velocity;
	mTag = tag;
	mLocation = Vector2D(newPositionX, newPositionY);
	isCreated = true;
	isDrawable = false;
	return this;
}

bool Unit::isInBounds(Vector2D mousePos)
{
	//Cache width and heigh
	float width = mAnimation.getCurrentSprite().getWidth();
	float height = mAnimation.getCurrentSprite().getHeight();

	//Get min location
	float minX = mDrawLocation.getX();
	float minY = mDrawLocation.getY();

	//get max location
	float maxX = width + mDrawLocation.getX();
	float maxY = height + mDrawLocation.getY();

	//cache current mouse position
	float currentX = mousePos.getX();
	float currentY = mousePos.getY();

	//Check if mouse is within bounds
	if (currentX < maxX && currentX > minX)
	{
		if (currentY < maxY && currentY > minY)
		{
			return true;
		}
	}
	return false;
}

bool Unit::checkCollsion(Unit* pUnit)
{
	//Cache width and heigh
	float width = mAnimation.getCurrentSprite().getWidth();
	float height = mAnimation.getCurrentSprite().getHeight();

	//Get min location
	float minX = mDrawLocation.getX();
	float minY = mDrawLocation.getY();

	//get max location
	float maxX = width + mDrawLocation.getX();
	float maxY = height + mDrawLocation.getY();

	//cache current mouse position
	float currentX = pUnit->getPosition().getX();
	float currentY = pUnit->getPosition().getY();

	//Check if mouse is within bounds
	if (currentX < maxX && currentX > minX)
	{
		if (currentY < maxY && currentY > minY)
		{
			return true;
		}
	}
	return false;
}

bool Unit::isOnScreen()
{
	float currentX = mDrawLocation.getX();
	float currentY = mDrawLocation.getY();

	if (currentX < maxX && currentX > minX)
	{
		if (currentY < maxY && currentY > minY)
		{
			return true;
		}
	}

	return false;
}

bool Unit::isOnScreen(std::string tag)
{
	float currentX = mDrawLocation.getX();
	float currentY = mDrawLocation.getY();

	if (tag == "Car1")
	{
		if (currentX < maxXR && currentX > minXR)
		{
			if (currentY < maxY && currentY > minY)
			{
				return true;
			}
		}
	}
	else if (tag == "Car2")
	{
		if (currentX < maxXB && currentX > minXB)
		{
			if (currentY < maxY && currentY > minY)
			{
				return true;
			}
		}
	}


	return false;
}

void Unit::switchAnimation()
{
	mDrawLocation = getCenterOffset();

	mIsAltAnimation = !mIsAltAnimation;

	mAnimation.reset();
}

void Unit::setAnimation(Animation animation)
{
	mAnimation = animation;
}

void Unit::setMovement(bool canMove)
{
	mCanMove = canMove;
}

std::string Unit::getTag()
{
	return mTag;
}

Vector2D Unit::getCenterOffset()
{
	//Get center of sprite
	Sprite currentSprite = mAnimation.getCurrentSprite();
	int posX = mLocation.getX() - currentSprite.getWidth() / 2.0f;
	int posY = mLocation.getY() - currentSprite.getHeight() / 2.0f;

	return Vector2D(posX, posY);
}
