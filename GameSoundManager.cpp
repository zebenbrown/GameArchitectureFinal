#include "GameSoundManager.h"

const std::string ASSET_PATH = "assets\\minetrap\\";
const std::string SOUND_PATH = ASSET_PATH + "GameSounds.txt";

GameSoundManager::GameSoundManager()
{
	EventSystem::getInstance()->addListener(static_cast<EventType>(SAD_SOUND), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(SELECT_SOUND), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(CRASH_SOUND), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(HAPPY_SOUND), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(PIRATE_SOUND), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(CAR_SOUND), this);
	EventSystem::getInstance()->addListener(static_cast<EventType>(EXTRA_SOUND), this);

}

GameSoundManager::~GameSoundManager()
{
}

void GameSoundManager::handleEvent(const Event& theEvent)
{
	EventType eventType = theEvent.getType();

	if (eventType == (EventType)CRASH_SOUND)
	{
		loadAndAddSample(ASSET_PATH + "EXP-L.wav", "sound");
		playSound("sound");
	}
	else if (eventType == (EventType)SELECT_SOUND)
	{
		loadAndAddSample(ASSET_PATH + "BLIP.wav", "sound2");
		playSound("sound2");
	}
	else if (eventType == (EventType)SAD_SOUND)
	{
		loadAndAddSample(ASSET_PATH + "KILLED.wav", "sound3");
		playSound("sound3");
	}
	else if (eventType == (EventType)HAPPY_SOUND)
	{
		loadAndAddSample(ASSET_PATH + "BEATHIGH.wav", "sound4");
		playSound("sound4");
	}
	else if (eventType == (EventType)EXTRA_SOUND)
	{
		loadAndAddSample(ASSET_PATH + "NEWPLAY.wav", "sound5");
		playSound("sound5");
	}
	else if (eventType == (EventType)PIRATE_SOUND)
	{
		loadAndAddSample(ASSET_PATH + "PROPGN.wav", "sound6");
		playSound("sound6");
	}
	else if (eventType == (EventType)CAR_SOUND)
	{
		loadAndAddSample(ASSET_PATH + "NEWHI.wav", "sound7");
		playSound("sound7");
	}
}