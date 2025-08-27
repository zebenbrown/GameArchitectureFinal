#pragma once

#include <SoundManager.h>
#include <EventSystem.h>
#include <Event.h>
#include <iostream>
#include <fstream>
#include "GameEvent.h"

class GameSoundManager : public SoundManager
{
public:
	void handleEvent(const Event& theEvent) override;

	GameSoundManager();
	~GameSoundManager();

private:
};