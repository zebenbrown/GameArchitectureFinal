#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{
	//Empty for now
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	cleanup();
}

void GraphicsBufferManager::init()
{
	//Empty for now
}

void GraphicsBufferManager::cleanup()
{
	//Iterate through and delete every item
	for (auto& search : mBufferDictionary)
	{
		delete search.second;
	}
	mBufferDictionary.clear();
}

void GraphicsBufferManager::addBuffer(std::string key, const std::string& filename)
{
	auto search = mBufferDictionary.find(key);

	//Prevent overwriting of Graphics buffers
	if (search != mBufferDictionary.end())
	{
		return;
	}
	mBufferDictionary[key] = new sf::Texture(filename);
}

void GraphicsBufferManager::addBuffer(std::string key, unsigned int width, unsigned int height, Color color)
{
	sf::RenderTexture renderTexture;

	sf::Texture texture = renderTexture.getTexture();

	auto search = mBufferDictionary.find(key);

	//Prevent overwriting of Graphics buffers
	if (search != mBufferDictionary.end())
	{
		return;
	}
	mBufferDictionary[key] = new sf::Texture(texture);
}

sf::Texture* GraphicsBufferManager::getBuffer(std::string key)
{
	//Get iterator for key and search for it
	auto search = mBufferDictionary.find(key);

	if (search != mBufferDictionary.end())
	{
		return search->second;
	}
	return nullptr;
}

void GraphicsBufferManager::deleteBuffer(std::string key)
{
	//figure out if it exists already
	auto search = mBufferDictionary.find(key);

	//If found, delete
	if (search != mBufferDictionary.end())
	{
		delete search->second;
		mBufferDictionary.erase(search);
		search->second = nullptr;
	}
}

void GraphicsBufferManager::deleteBuffer(sf::Texture* buffer)
{
	//Search through map to find buffer
	for (auto& search : mBufferDictionary)
	{
		if (search.second == buffer)
		{
			delete search.second;
			mBufferDictionary.erase(search.first);
			search.second = nullptr;
			return;
		}
	}
}
