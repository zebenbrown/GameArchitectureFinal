#pragma once

#include <Trackable.h>
#include <Vector2D.h>

#include <SFML/Graphics.hpp>

#include "Color.h"
#include "Font.h"

class GraphicsBuffer;
class Sprite;

class GraphicsSystem :public Trackable
{
public:
	GraphicsSystem();//should not call init
	~GraphicsSystem();//should call cleanup

	//make sure initting multiple times in a row doesn't fail
	void init(unsigned int width, unsigned int height);//make sure initting multiple times in a row doesn't fail
	void update();
	
	//make sure calling cleanup never fails
	void cleanup();

	unsigned int getDisplayWidth() const { return mWidth; };
	unsigned int getDisplayHeight() const { return mHeight; };
	
	static GraphicsBuffer* getBackBuffer() { return mpBackBuffer; };

	void flip();//flip the allegro display
	static sf::RenderWindow* getDisplay() { return mpWindow; };

	void writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align = Font::LEFT);
	void loadTexture(std::string fileName);
	void createBackground(std::string fileName);
	void drawBackgroundWithShaders();
	void initBackgroundShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName, const std::string& backgroundFileName);

	static void GraphicsSystem::drawSprite(const Vector2D& destLoc, const Sprite& sprite, double scale);


private:
	//ALLEGRO_DISPLAY* mDisplay = nullptr;
	static sf::RenderWindow* mpWindow;
	sf::RenderTexture* mpRenderTexture = nullptr;
	static GraphicsBuffer* mpBackBuffer;
	sf::Sprite* mpBackgroundSprite = nullptr;
	sf::Shader* mpBackgroundShader = nullptr;
	sf::Texture* mpBackgroundTexture = nullptr;

	sf::Clock* mpClock = nullptr;

	unsigned int mWidth = 0;
	unsigned int mHeight = 0;

	//bool initAddOns();
};
