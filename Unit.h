#pragma once

#include <Vector2D.h>
#include <Trackable.h>
#include <Animation.h>
#include <random>

class Unit : public Trackable
{
public:
	friend class UnitManager;

	Unit();
	Unit(Animation animation, Vector2D velocity = Vector2D(1.0f, 1.0f), std::string tag = "Unit");
	Unit(Animation animation, Vector2D position, Vector2D velocity = Vector2D(1.0f, 1.0f), std::string tag = "Unit");

	Unit(Sprite sprite, Vector2D position, Vector2D velocity = Vector2D(1.0f, 1.0f), std::string tag = "Unit");
	~Unit();

	void update(float deltaTime);
	void setPosition(Vector2D position);
	Vector2D getPosition() { return mLocation; };
	Vector2D getVelocity() { return mVelocity; };
	Animation getAnimation() { return mAnimation; };
	void setVelocity(Vector2D velocity);
	void draw();
	void initCar(Animation animation, Vector2D position, Vector2D velocity = Vector2D(0.0f, 0.0f), std::string tag = "Unit");
	void initCone(Animation animation, Vector2D topLeft, Vector2D bottomRight, Vector2D velocity = Vector2D(1.0f, 1.0f), std::string tag = "Unit");
	void createCar(Animation animation, Vector2D position, Vector2D velocity, std::string tag = "Unit");
	void createCone(Animation animation, Vector2D velocity = Vector2D(1.0f, 1.0f), std::string tag = "Unit");
	Unit* createConeInBounds(Animation animation, Vector2D topLeft, Vector2D bottomRight, Vector2D velocity, std::string tag = "Unit");

	Unit* getNextUnit();
	void setNextUnit(Unit* pUnit); 

	bool isInBounds(Vector2D mousePos);
	bool isOnScreen();
	bool isOnScreen(std::string tag);

	void switchAnimation();
	void setAnimation(Animation animation);
	void setMovement(bool canMove);
	std::string getTag();
	bool checkCollsion(Unit* pUnit);
	bool checkCreated() { return isCreated; };
	
	void setAvailability(bool available) { isAvailable = available; };
	bool getAvailability() { return isAvailable; };

	void setDrawable(bool drawable) { isDrawable = drawable; };
	bool getDrawable() { return isDrawable; };

private:
	Vector2D getCenterOffset();

	Vector2D mLocation;
	Vector2D mDrawLocation;

	Animation mAnimation;

	Sprite* mpSprite = nullptr;

	const unsigned int maxXR = 400;
	const unsigned int minXR = 150;
	const unsigned int maxX = 800;
	const unsigned int minX = 0;
	const unsigned int maxY = 600;
	const unsigned int minY = 0;
	const unsigned int maxXB = 650;
	const unsigned int minXB = 400;

	bool mCanMove = true;
	bool mIsAltAnimation = false;

	//variables for game to work
	Vector2D mVelocity;
	std::string mTag = "";
	bool isCreated = false;
	bool isDrawable = false;
	bool isAvailable = false;

};