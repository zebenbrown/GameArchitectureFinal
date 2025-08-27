#pragma once

#include <unordered_map>
#include "GraphicsBuffer.h"

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	void init();
	void cleanup();

	void addBuffer(std::string key, const std::string& filename);
	void addBuffer(std::string key, unsigned int width, unsigned int height, Color color = Color());

	sf::Texture* getBuffer(std::string key);
	void deleteBuffer(std::string key);
	void deleteBuffer(sf::Texture* buffer);
private:
	std::unordered_map<std::string, sf::Texture*> mBufferDictionary;
};

