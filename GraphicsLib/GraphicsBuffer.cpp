#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Sprite.h"
#include "Font.h"

GraphicsBuffer::GraphicsBuffer(sf::RenderWindow* window)
{
	//this isnt neccessary since render window draws directly to a window and not the back buffer
	//this will probably get deleted
}

GraphicsBuffer::GraphicsBuffer(const std::string& filename)
{
	//make a temp texture to be loaded in from a file
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//this creates a new render texture
	mpRenderTexture = new sf::RenderTexture(sf::Vector2u(texture.getSize().x, texture.getSize().y));
	//need to change color class to sfml still
	//this should change the screen to black but this keeps it white
	mpRenderTexture->clear();
	mpRenderTexture->draw(sf::Sprite(texture));
	//this draws it to the screen, kind of like al_flip_display but for textures
	mpRenderTexture->display();
}

GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, Color color)
{
	//create a new render texture
	mpRenderTexture = new sf::RenderTexture(sf::Vector2u(width, height));
	//set the screen color
	setToColor(color);
}

GraphicsBuffer::~GraphicsBuffer()
{
	//sfml should handle this
	delete mpRenderTexture;
	mpRenderTexture = nullptr;
}

GraphicsBuffer* GraphicsBuffer::clone() const
{
	//Create new buffer
	GraphicsBuffer* pNewBuffer = new GraphicsBuffer(this->getWidth(), this->getHeight());

	//Draw to new buffer
	pNewBuffer->draw(Vector2D(0, 0), *this);

	return pNewBuffer;
}

void GraphicsBuffer::draw(const Vector2D& destLoc, const GraphicsBuffer& src, double scale)
{

	sf::Sprite sprite = sf::Sprite(src.mpRenderTexture->getTexture());
	sprite.setPosition(sf::Vector2f(destLoc.getX(), destLoc.getY()));
	sprite.setScale(sf::Vector2f(scale, scale));
	mpRenderTexture->draw(sprite);
}



void GraphicsBuffer::writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align)
{

	sf::String newString = sf::String(text);
	sf::Font newFont = *font.getFont();
	sf::Text newText(newFont, newString);
	sf::Color newColor(color.getR(), color.getG(), color.getB(), color.getA());
	newText.setPosition(sf::Vector2f(destLoc.getX(), destLoc.getY()));
	newText.setFillColor(newColor);
	newText.setCharacterSize(font.getSize());
}

void GraphicsBuffer::setToColor(const Color& color)
{
	//clears the render texture and sets it to the color
	mpRenderTexture->clear(sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));
}

void GraphicsBuffer::saveToFile(const std::string& filename) const
{
	//save the render texture's texture to a file
	if (!mpRenderTexture->getTexture().copyToImage().saveToFile(filename))
	{
		std::cout << "Failed to save texture" << std::endl;
	}
}

