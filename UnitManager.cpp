#include "UnitManager.h"

#include <EventSystem.h>
#include "GameEvent.h"

#include "Unit.h"
#include <Animation.h>

UnitManager::UnitManager()
{
	EventSystem* pEventSystem = EventSystem::getInstance();
	pEventSystem->addListener((EventType)CHANGE_EVENT, this);
}

UnitManager::UnitManager(Hud* mpHudToBe, ObstaclePool* obstaclePool)
{
	EventSystem* pEventSystem = EventSystem::getInstance();
	pEventSystem->addListener((EventType)CHANGE_EVENT, this);
	mpHud = mpHudToBe;
	mpObstaclePool = obstaclePool;
}

UnitManager::~UnitManager()
{
	cleanup();

	//Remove this listener from all events
	EventSystem::getInstance()->removeListenerFromAllEvents(this);
}

void UnitManager::init()
{}

void UnitManager::cleanup()
{
	for (auto* object : mObjectCollection)
	{
		if (object->getTag() == "Car1" || object->getTag() == "Car2")
		{
			mObjectNumber--;
			delete object;
			object = nullptr;
		}
	}

	mObjectCollection.clear();
}

void UnitManager::createAndAddUnit(Animation animation, Vector2D pos, Vector2D vel, std::string tag)
{
	//Increase object number
	mObjectNumber++;

	if (tag == "Car1")
	{
		Unit* pUnit = new Unit(animation, pos, vel, tag);
		pUnit->setDrawable(true);
		mObjectCollection.push_back(pUnit);
	}
	else if (tag == "Car2")
	{
		Unit* pUnit = new Unit(animation, pos, vel, tag);
		pUnit->setDrawable(true);
		mObjectCollection.push_back(pUnit);
	}
}

void UnitManager::createAndAddUnit(Animation animation, Vector2D pos, std::string tag)
{
	//Increase object number
	mObjectNumber++;

	if (tag == "Car1")
	{
		Unit* pUnit = new Unit(animation, pos, tag);
		pUnit->setDrawable(true);
		mObjectCollection.push_back(pUnit);
	}
	if (tag == "Car2")
	{
		Unit* pUnit = new Unit(animation, pos, tag);
		pUnit->setDrawable(true);
		mObjectCollection.push_back(pUnit);
	}
}

void UnitManager::createUnitInBounds(Animation animation, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, Vector2D velocity, std::string tag)
{
	Vector2D topLeftBounds = Vector2D(topLeftX, topLeftY);
	Vector2D bottomRightBounds = Vector2D(bottomRightX, bottomRightY);

	Unit* pUnit = mpObstaclePool->getAvailableCone(animation, topLeftBounds, bottomRightBounds, velocity, tag);

	if (pUnit == nullptr)
	{
		std::cout << "No available cones" << std::endl;
		return;
	}

	else
	{
		mObjectCollection.push_back(pUnit);
		pUnit->setDrawable(true);
		coneCount++;
	}
}

void UnitManager::createUnitInBounds(Animation animation, Vector2D position, Vector2D velocity, std::string tag)
{
	Unit* pUnit = mpObstaclePool->getAvailableCone(animation, position, velocity, tag);

	if (pUnit == nullptr)
	{
		std::cout << "No available cones" << std::endl;
		return;
	}

	else
	{
		mObjectCollection.push_back(pUnit);
		pUnit->setDrawable(true);
		coneCount++;
	}
}
 
void UnitManager::createAndAddUnit(Unit* pUnit)
{
	mObjectNumber++;

	mObjectCollection.push_back(pUnit);
}

Unit* UnitManager::getUnit(unsigned int index)
{
	if (index >= mObjectCollection.size()) return nullptr;

	return mObjectCollection[index];
}

Unit* UnitManager::getUnit(std::string tag)
{
	for (Unit* pUnit : mObjectCollection)
	{
		if (pUnit->getTag() == tag)
		{
			return pUnit;
		}
	}
	//return this->getUnit(0);
}

std::vector<Unit*> UnitManager::getObjectCollection()
{
	return mObjectCollection;
}

void UnitManager::setMovementAllUnits()
{
	//Toggle
	mUnitsCanMove = !mUnitsCanMove;

	for (auto instance : mObjectCollection)
	{
		instance->setMovement(mUnitsCanMove);
	}
}

bool UnitManager::coneExists()
{
	/*for (Unit* pUnit : mObjectCollection)
	{
		if (pUnit->getTag() == "Cone")
		{
			return true;
		}
	}*/

	if (coneCount > 0)
	{
		return true;
	}
	return false;
}

void UnitManager::setConeCount(int count)
{
	coneCount = count;
}

void UnitManager::deleteUnit(Unit* pUnitToDelete)
{
	//Iterates until it finds unit to delete
	for (unsigned int i = 0; i < mObjectCollection.size(); i++)
	{
		if (mObjectCollection[i] == pUnitToDelete)
		{
			mObjectNumber--;
			mObjectCollection.erase(mObjectCollection.begin() + i);
			break;
		}
	}
}

void UnitManager::deleteAllUnits()
{
	cleanup();
	//mScore = 10;
}

void UnitManager::handleEvent(const Event& theEvent)
{
	
}

void UnitManager::clearGarbageCollection()
{
	//Iterate through vector and delete all elements
	for (unsigned int i = 0; i < mGarbageCollection.size(); i++)
	{
		mObjectNumber--;
		delete mGarbageCollection[i];
	}
	mGarbageCollection.clear();
}

bool UnitManager::removeUnitAt(Vector2D mousePos)
{
	//Iterate through all units and if they are in bounds, delete
	for (unsigned int i = 0; i < mObjectCollection.size(); i++)
	{
		if (mObjectCollection[i]->isInBounds(mousePos))
		{
			deleteUnit(mObjectCollection[i]);
			return true;
		}
	}
	return false;
}

void UnitManager::removeAllUnitsAt(Vector2D mousePos)
{
	while (removeUnitAt(mousePos));
	return;
}

/// <summary>
/// Toggles the latest unit to different animation
/// </summary>
void UnitManager::toggleLatestUnit()
{
	//Edge case
	if (mObjectCollection.size() <= 0) return;

	//Get newest unit
	mObjectCollection.back()->switchAnimation();
}

void UnitManager::changeGlowColor(Vector2D mousePos)
{
	//go through all units on mouse and change color
	for (unsigned int i = 0; i < mObjectCollection.size(); i++)
	{
		if (mObjectCollection[i]->isInBounds(mousePos))
		{
			mObjectCollection[i]->setPosition(Vector2D(800 / 2.0f, 600 / 2.0f));
		}
	}
}

void UnitManager::update(float deltaTime)
{
	//Iterate and update
	for (auto unitToUpdate : mObjectCollection)
	{
		unitToUpdate->update(deltaTime);
	}

	//Iterate and check if on screen
	for (auto unitToUpdate : mObjectCollection)
	{
		//If unit goes off screen, delete
		if (!unitToUpdate->isOnScreen())
		{
			coneCount--;
			deleteUnit(unitToUpdate);
			mpObstaclePool->reActivateCone(unitToUpdate);
		}

		else if (!unitToUpdate->isOnScreen(unitToUpdate->getTag()))
		{
			if (unitToUpdate->getTag() == "Car1")
			{
				unitToUpdate->setPosition(mSTARTING_LOC1);
				return;
			}
			else if (unitToUpdate->getTag() == "Car2")
			{
				unitToUpdate->setPosition(mSTARTING_LOC2);
				return;
			}
		}
			
	}
	//clearGarbageCollection();
}

void UnitManager::draw()
{
	//Iterate and draw
	for (auto unitToDraw : mObjectCollection)
	{

		if (!unitToDraw->getDrawable()) 
		{
			continue;
		}
		unitToDraw->draw();
	}
}
