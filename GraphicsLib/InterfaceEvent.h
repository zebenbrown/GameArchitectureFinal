#pragma once
#include <Event.h>
#include <Vector2D.h>
#include "InputSystem.h"

//enum InterfaceEventTypes
//{
//	MOUSE_EVENT = 0,
//	KEYBOARD_EVENT,
//	NUM_INTERFACE_EVENT_TYPES,
//};

enum InterfaceEventTypes
{
	MOUSE_EVENT_INTERFACE = 0,
	KEYBOARD_EVENT_INTERFACE,
	KEYBOARD_RELEASE_EVENT_INTERFACE
};

class InterfaceEvent : public Event
{
public: 
	InterfaceEvent(InterfaceEventTypes type) : Event((EventType)type) {}
private:

};

class KeyboardEvent : public InterfaceEvent
{
public:
	KeyboardEvent(const Keys& pressedKey) : InterfaceEvent(KEYBOARD_EVENT_INTERFACE), mKey(pressedKey) {}

	Keys getKey() const { return mKey; };

private:
	Keys mKey;
};

class ReleasedEvent : public InterfaceEvent
{
public:
	ReleasedEvent(const Keys& pressedKey) : InterfaceEvent(KEYBOARD_RELEASE_EVENT_INTERFACE), mKey(pressedKey) {}

	Keys getKey() const { return mKey; };

private:
	Keys mKey;
};

class MouseEvent : public InterfaceEvent
{
public:
	MouseEvent(const MouseButtons& pressedButton, const Vector2D mousePos) : InterfaceEvent(MOUSE_EVENT_INTERFACE), mButton(pressedButton), mPos(mousePos) {}

	MouseButtons getPressedButton() const { return mButton; }
	Vector2D getMousePosition() const { return mPos; }
private:
	MouseButtons mButton;
	Vector2D mPos;
};



