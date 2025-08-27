#include "SoundManager.h"


SoundManager::SoundManager()
{
	
}

SoundManager::~SoundManager()
{
	cleanup();
}

void SoundManager::loadAndAddSample(const std::string& filename, std::string keyName)
{
	if (!mSoundBuffer.loadFromFile(filename))
	{
		std::cout << "Failed to load sound" << std::endl;
	}
	mpSound = new sf::Sound(mSoundBuffer);
	mSoundMap[keyName] = mpSound;
}

void SoundManager::playSound(std::string key)
{
	mSoundMap[key]->play();
}

void SoundManager::cleanup()
{
	for (auto& search : mSoundMap)
	{
		if (search.second) 
		{
			search.second = nullptr;
		}
	}
	mSoundMap.clear();
}