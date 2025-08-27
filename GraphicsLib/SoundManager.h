#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <EventListener.h>

#include <Trackable.h>

class SoundManager :public EventListener
{
public:
	SoundManager();
	~SoundManager();

	bool init(int numSamples);
	void cleanup();

	void loadAndAddSample(const std::string& filename, std::string key);
	void playSound(std::string key);
	void addSample(std::string key);

private:
	std::unordered_map<std::string, sf::Sound*> mSoundMap;
	sf::Sound* mpSound;
	sf::SoundBuffer mSoundBuffer;
	std::vector<int16_t> sampleArray;
};
