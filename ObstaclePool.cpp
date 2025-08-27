#include "ObstaclePool.h"

ObstaclePool::~ObstaclePool()
{
	for (int i = 0; i < unitPool.size(); i++)
	{
		if (unitPool[i] != nullptr)
		{
			delete unitPool[i];
			unitPool[i] = nullptr;
		}
	}
}	

void ObstaclePool::init(int size)
{
	unitPool.resize(size);
	
	for (int i = 0; i < size; i++)
	{
		unitPool[i] = new Unit();
		unitPool[i]->setAvailability(true);
	}
	
}

Unit* ObstaclePool::getAvailableCone(Animation animation, Vector2D topLeftBounds, Vector2D bottomRightBounds, Vector2D velocity, std::string tag)
{

	for (int i = 0; i < unitPool.size(); i++)
	{
		Unit* pUnit = unitPool[i];

		if (pUnit != nullptr && pUnit->getAvailability())
		{
			pUnit->createConeInBounds(animation, topLeftBounds, bottomRightBounds, velocity, tag);
			pUnit->setAvailability(false);
			return pUnit;
		}
	}
	return nullptr;
}

Unit* ObstaclePool::getAvailableCone(Animation animation, Vector2D position, Vector2D velocity, std::string tag)
{

	for (int i = 0; i < unitPool.size(); i++)
	{
		Unit* pUnit = unitPool[i];

		if (pUnit != nullptr && pUnit->getAvailability())
		{
			pUnit->createCar(animation, position, velocity, tag);
			pUnit->setAvailability(false);
			return pUnit;
		}
	}
	return nullptr;
}

void ObstaclePool::reActivateCone(Unit* unit)
{
	unit->setAvailability(true);
}

void ObstaclePool::update()
{
	for (int i = 0; i < unitPool.size(); i++)
	{
		unitPool[i]->update(16.7f);
	}
}
