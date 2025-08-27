#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Trackable.h>
#include "GraphicsSystem.h"

class Vector2D;
class EventSystem;

enum Keys
{
	A_KEY = sf::Keyboard::Key::A,
	B_KEY = sf::Keyboard::Key::B,
	C_KEY = sf::Keyboard::Key::C,
	D_KEY = sf::Keyboard::Key::D,
	E_KEY = sf::Keyboard::Key::E,
	F_KEY = sf::Keyboard::Key::F,
	H_KEY = sf::Keyboard::Key::H,
	I_KEY = sf::Keyboard::Key::I,
	J_KEY = sf::Keyboard::Key::J,
	K_KEY = sf::Keyboard::Key::K,
	L_KEY = sf::Keyboard::Key::L,
	M_KEY = sf::Keyboard::Key::M,
	N_KEY = sf::Keyboard::Key::N,
	O_KEY = sf::Keyboard::Key::O,
	P_KEY = sf::Keyboard::Key::P,
	Q_KEY = sf::Keyboard::Key::Q,
	R_KEY = sf::Keyboard::Key::R,
	S_KEY = sf::Keyboard::Key::S,
	T_KEY = sf::Keyboard::Key::T,
	U_KEY = sf::Keyboard::Key::U,
	V_KEY = sf::Keyboard::Key::V,
	X_KEY = sf::Keyboard::Key::X,
	Y_KEY = sf::Keyboard::Key::Y,
	Z_KEY = sf::Keyboard::Key::Z,

	NUMBER_0 = sf::Keyboard::Key::Num0,
	NUMBER_1 = sf::Keyboard::Key::Num1,
	NUMBER_2 = sf::Keyboard::Key::Num2,
	NUMBER_3 = sf::Keyboard::Key::Num3,
	NUMBER_4 = sf::Keyboard::Key::Num4,
	NUMBER_5 = sf::Keyboard::Key::Num5,
	NUMBER_6 = sf::Keyboard::Key::Num6,
	NUMBER_7 = sf::Keyboard::Key::Num7,
	NUMBER_8 = sf::Keyboard::Key::Num8,
	NUMBER_9 = sf::Keyboard::Key::Num9,

	NUMPAD_0 = sf::Keyboard::Key::Numpad0,
	NUMPAD_1 = sf::Keyboard::Key::Numpad1,
	NUMPAD_2 = sf::Keyboard::Key::Numpad2,
	NUMPAD_3 = sf::Keyboard::Key::Numpad3,
	NUMPAD_4 = sf::Keyboard::Key::Numpad4,
	NUMPAD_5 = sf::Keyboard::Key::Numpad5,
	NUMPAD_6 = sf::Keyboard::Key::Numpad6,
	NUMPAD_7 = sf::Keyboard::Key::Numpad7,
	NUMPAD_8 = sf::Keyboard::Key::Numpad8,
	NUMPAD_9 = sf::Keyboard::Key::Numpad9,


	SPACE_KEY = sf::Keyboard::Key::Space,
	ESCAPE_KEY = sf::Keyboard::Key::Escape,
	SHIFT_KEY = sf::Keyboard::Key::LShift,
};

enum MouseButtons
{
	LEFT_MOUSE_BUTTON = sf::Mouse::Button::Left,
	RIGHT_MOUSE_BUTTON = sf::Mouse::Button::Right,
	MIDDLE_MOUSE_BUTTON = sf::Mouse::Button::Middle,
};

class InputSystem: public Trackable
{
public:
	InputSystem();
	~InputSystem();
	bool init();
	void cleanup();
	void update(float deltaTime);
	bool isKeyPressed(int key);
	bool isMousePressed(int mouseButton);
	Vector2D getMousePosition();

private:
	//ALLEGRO_KEYBOARD_STATE mKeyboardState;
	//ALLEGRO_MOUSE_STATE mMouseState;
	//ALLEGRO_EVENT_QUEUE* mpEventQueue = nullptr;

};

