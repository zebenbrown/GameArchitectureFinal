#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Color.h"


#include <iostream>
#include <cassert>


GraphicsBuffer* GraphicsSystem::mpBackBuffer=nullptr;
sf::RenderWindow* GraphicsSystem::mpWindow = nullptr;


GraphicsSystem::GraphicsSystem()
{
	//If adding member variables init them here
}

GraphicsSystem::~GraphicsSystem()
{
	delete mpWindow;
	mpWindow = nullptr;
	delete mpRenderTexture;
	mpRenderTexture = nullptr;
	cleanup();
}

void GraphicsSystem::init(unsigned int width, unsigned int height)
{

	//create a window with the title game and size of the parameters
	mpWindow = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), "Game");

}

void GraphicsSystem::update()
{

}

void GraphicsSystem::cleanup()
{
	if (mpBackgroundSprite != nullptr)
	{
		delete mpBackgroundSprite;
		mpBackgroundSprite = nullptr;
	}
}

void GraphicsSystem::flip()
{
	mpWindow->display();
}

void GraphicsSystem::writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align)
{
	sf::String newString = sf::String(text);
	sf::Font newFont = *font.getFont();
	sf::Text newText(newFont, newString);
	sf::Color newColor(color.getR(), color.getG(), color.getB(), color.getA());
	newText.setPosition(sf::Vector2f(destLoc.getX(), destLoc.getY()));
	newText.setFillColor(newColor);
	newText.setCharacterSize(font.getSize());

	mpWindow->draw(newText);
}

void GraphicsSystem::loadTexture(std::string fileName)
{
	sf::Texture texture;
	if (!texture.loadFromFile(fileName))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//this creates a new render texture
	mpRenderTexture = new sf::RenderTexture(sf::Vector2u(texture.getSize().x, texture.getSize().y));

	//this should change the screen to black but this keeps it white
	mpRenderTexture->clear();
	mpRenderTexture->draw(sf::Sprite(texture));
	//this draws it to the screen, kind of like al_flip_display but for textures
	mpRenderTexture->display();
}

void GraphicsSystem::createBackground(std::string fileName)
{
	sf::Texture texture;
	if (!texture.loadFromFile(fileName))
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	mpBackgroundSprite = new sf::Sprite(texture);
	mpWindow->draw(*mpBackgroundSprite);
	//mpWindow->display();
}

void GraphicsSystem::drawBackgroundWithShaders()
{
	if (mpBackgroundShader != nullptr && mpBackgroundSprite != nullptr && mpClock != nullptr) 
	{

		//https://gist.github.com/MarioLiebisch/c965e4caf4360ebd6def549d60423740
		sf::Shader backgroundShader;
		backgroundShader.loadFromMemory(
			"uniform float offset;"

			"void main() {"
			"    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
			"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
			"    gl_TexCoord[0].y = gl_TexCoord[0].y - offset;" // magic
			"    gl_FrontColor = gl_Color;"
			"}"
			, sf::Shader::Type::Vertex);

		float offset = 0.0f;

		backgroundShader.setUniform("offset", (offset += mpClock->getElapsedTime().asSeconds()) * 0.5f);
		mpWindow->draw(*mpBackgroundSprite, &backgroundShader);
		
	}
}

void GraphicsSystem::initBackgroundShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName, const std::string& backgroundFileName)
{
	mpClock = new sf::Clock();
	mpBackgroundTexture = new sf::Texture();
	if (!mpBackgroundTexture->loadFromFile(backgroundFileName))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	mpBackgroundTexture->setRepeated(true);
	mpBackgroundShader = new sf::Shader();
	if (!mpBackgroundShader->loadFromFile(vertexShaderFileName, fragmentShaderFileName))
	{
		std::cout << "Failed to load shader" << std::endl;
	}	
	mpBackgroundSprite = new sf::Sprite(*mpBackgroundTexture);
	mpBackgroundSprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(mpWindow->getSize().x, mpWindow->getSize().y)));
}

void GraphicsSystem::drawSprite(const Vector2D& destLoc, const Sprite& sprite, double scale = 1.0)
{

	sf::Texture* spriteTexture = sprite.getTexture();

	int spriteHeight = sprite.getHeight();
	int spriteWidth = sprite.getWidth();

	sf::Sprite newSprite(*spriteTexture);

	sf::Vector2i spritePosition(sprite.getSourceLoc().getX(), sprite.getSourceLoc().getY());
	sf::Vector2i spriteSize(spriteWidth, spriteHeight);
	sf::IntRect spriteRectangle(spritePosition, spriteSize);

	newSprite.setTextureRect(spriteRectangle);

	newSprite.setPosition(sf::Vector2f(destLoc.getX(), destLoc.getY()));
	newSprite.setScale(sf::Vector2f(scale, scale));
	mpWindow->draw(newSprite);
}




