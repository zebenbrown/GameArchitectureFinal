#include "InputSystem.h"
#include <Vector2D.h>

#include <EventSystem.h>
#include "InterfaceEvent.h"

InputSystem::InputSystem()
{
	
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::cleanup()
{
	
}

void InputSystem::update(float deltaTime)
{
	while (const std::optional event = GraphicsSystem::getDisplay()->pollEvent())
	{
		if (const auto* keyPressed = event->getIf <sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::SPACE_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::ESCAPE_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::D_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::A_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::L)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::L_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::J)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::J_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::LShift)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::SHIFT_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::L)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::L_KEY));
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::Num1 || keyPressed->scancode == sf::Keyboard::Scancode::Numpad1)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::NUMBER_1));
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Num2 || keyPressed->scancode == sf::Keyboard::Scancode::Numpad2)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::NUMBER_2));
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Num3 || keyPressed->scancode == sf::Keyboard::Scancode::Numpad3)
			{
				EventSystem::getInstance()->fireEvent(KeyboardEvent(Keys::NUMBER_3));
			}
		}

		if (const auto* keyReleased = event->getIf <sf::Event::KeyReleased>())
		{
			if (keyReleased->scancode == sf::Keyboard::Scancode::D)
			{
				EventSystem::getInstance()->fireEvent(ReleasedEvent(Keys::D_KEY));
			}

			else if (keyReleased->scancode == sf::Keyboard::Scancode::A)
			{
				EventSystem::getInstance()->fireEvent(ReleasedEvent(Keys::A_KEY));
			}

			else if (keyReleased->scancode == sf::Keyboard::Scancode::L)
			{
				EventSystem::getInstance()->fireEvent(ReleasedEvent(Keys::L_KEY));
			}

			else if (keyReleased->scancode == sf::Keyboard::Scancode::J)
			{
				EventSystem::getInstance()->fireEvent(ReleasedEvent(Keys::J_KEY));
			}
		}

		else if (const auto* mouseClicked = event->getIf <sf::Event::MouseButtonPressed>())
		{
			if (mouseClicked->button == sf::Mouse::Button::Left)
			{
				EventSystem::getInstance()->fireEvent(MouseEvent(MouseButtons::LEFT_MOUSE_BUTTON, getMousePosition()));
			}
		}
	}
}

/// <summary>
/// Returns whether input key is true or false
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
bool InputSystem::isKeyPressed(int key)
{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key))
		{
			return true;
		}
		
	return false;
}

/// <summary>
/// Returns whether mouse button is held down
/// </summary>
/// <param name="mouseButton"></param>
/// <returns></returns>
bool InputSystem::isMousePressed(int mouseButton)
{
	if (sf::Mouse::isButtonPressed((sf::Mouse::Button)mouseButton))
	{
		return true;
	}

	return false;
}

/// <summary>
/// Returns current mouse position
/// </summary>
/// <returns></returns>
Vector2D InputSystem::getMousePosition()
{
	Vector2D mousePosition;
	mousePosition.setX(sf::Mouse::getPosition(*GraphicsSystem::getDisplay()).x);
	mousePosition.setY(sf::Mouse::getPosition(*GraphicsSystem::getDisplay()).y);
	return Vector2D(mousePosition.getX(), mousePosition.getY());
}