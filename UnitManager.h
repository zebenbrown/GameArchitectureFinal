#pragma once

#include <vector>
#include <Vector2D.h>
#include <EventListener.h>
#include "Hud.h"
#include "ObstaclePool.h"
#include <random>

class Unit;
class Animation;

class UnitManager : public EventListener
{
public:
	UnitManager();
	UnitManager(Hud* mpHudToBe, ObstaclePool* obstaclePool);
	~UnitManager();

	void init();
	void cleanup();

	void createAndAddUnit(Animation mainAnim, Animation altAnim, Vector2D pos, Vector2D vel = Vector2D(1.0f, 1.0f), std::string tag = "Unit");
	void createAndAddUnit(Animation animation, Vector2D pos, std::string tag = "Unit");
	void createAndAddUnit(Animation animation, Vector2D pos, Vector2D vel, std::string tag = "Unit");
	void createUnitInBounds(Animation animation, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, Vector2D velocity, std::string tag = "Unit");
	void createUnitInBounds(Animation animation, Vector2D position, Vector2D velocity, std::string tag = "Unit");
	void createAndAddUnit(Unit* pUnit);

	Unit* getUnit(unsigned int index);
	Unit* getUnit(std::string tag);
	int getObjectNumber() const { return mObjectNumber; }
	std::vector<Unit*> getObjectCollection();
	int getScore() const { return mScore; }
	void setMovementAllUnits();
	bool coneExists();
	int getConeCount() { return coneCount; };
	void setConeCount(int count);

	void deleteUnit(Unit* pUnit);
	void deleteAllUnits();
	//Remove all units at vec2
	//RemoveUnit at vec 2

	void handleEvent(const Event& theEvent);

	void clearGarbageCollection();

	bool removeUnitAt(Vector2D mousePos);
	void removeAllUnitsAt(Vector2D mousePos);

	void changeGlowColor(Vector2D mousePos);

	void toggleLatestUnit();

	void update(float deltaTime);
	void draw();


private:
	std::vector<Unit*> mObjectCollection;
	std::vector<Unit*> mGarbageCollection;

	Hud* mpHud = nullptr;
	ObstaclePool* mpObstaclePool = nullptr;

	const Vector2D mSTARTING_LOC1 = Vector2D(300, 500);
	const Vector2D mSTARTING_LOC2 = Vector2D(550, 500);

	int mObjectNumber = 0;
	int mScore = 10;
	bool mUnitsCanMove = true;
	int coneCount = 0;
};

