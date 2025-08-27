#pragma once
#include <Trackable.h>
#include "Unit.h"
class ObstaclePool : public Trackable
{
public:
	~ObstaclePool();
	void init(int size);
	Unit* getAvailableCone(Animation animation, Vector2D topLeftBounds, Vector2D bottomRightBounds, Vector2D velocity, std::string tag = "Unit");
	Unit* getAvailableCone(Animation animation, Vector2D position, Vector2D velocity, std::string tag = "Unit");
	void reActivateCone(Unit* unit);
	void update();

private:
	std::vector<Unit*> unitPool;
	Unit* firstAvailable = nullptr;
};

