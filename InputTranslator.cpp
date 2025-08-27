#include "InputTranslator.h"
#include <EventSystem.h>
#include "GameEvent.h"

InputTranslator::InputTranslator()
{
}


InputTranslator::~InputTranslator()
{
	cleanup();
}

void InputTranslator::init()
{
	//Set all listeners
	EventSystem* pInstance = EventSystem::getInstance();
	pInstance->addListener((EventType)MOUSE_EVENT_INTERFACE, this);
	pInstance->addListener((EventType)KEYBOARD_EVENT_INTERFACE, this);
	pInstance->addListener((EventType)KEYBOARD_RELEASE_EVENT_INTERFACE, this);
}

void InputTranslator::cleanup()
{
	//Remove this listener
	EventSystem::getInstance()->removeListenerFromAllEvents(this);
}

void InputTranslator::update()
{

}

void InputTranslator::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case MOUSE_EVENT_INTERFACE:
		handleMouseEvent((const MouseEvent*)&theEvent);
		break;
	case KEYBOARD_EVENT_INTERFACE:
		handleKeyboardEvent((const KeyboardEvent*)&theEvent);
		break;
	case KEYBOARD_RELEASE_EVENT_INTERFACE:
		handleKeyboardEvent((const ReleasedEvent*)&theEvent);
		break;
	}
}

void InputTranslator::handleMouseEvent(const MouseEvent* mouseEvent)
{
	switch (mouseEvent->getPressedButton())
	{
		//Fire move game event
		case LEFT_MOUSE_BUTTON:
			EventSystem::getInstance()->fireEvent(ChangeEvent(mouseEvent->getMousePosition()));
			break;
			//Kill units at mouse position
		case RIGHT_MOUSE_BUTTON:
			EventSystem::getInstance()->fireEvent(RemoveUnitEvent(mouseEvent->getMousePosition()));
			break;
	}
}

void InputTranslator::handleKeyboardEvent(const KeyboardEvent* keyEvent)
{
	switch (keyEvent->getKey())
	{
		//End game event
	case ESCAPE_KEY:
		EventSystem::getInstance()->fireEvent(ExitEvent());
		break;
		//movement
	case D_KEY:
		EventSystem::getInstance()->fireEvent(DEvent());
		break;
	case A_KEY:
		EventSystem::getInstance()->fireEvent(AEvent());
		break;
	case J_KEY:
		EventSystem::getInstance()->fireEvent(JEvent());
		break;
	case L_KEY:
		EventSystem::getInstance()->fireEvent(LEvent());
		break;
		//Pause movement event
	case SPACE_KEY:
		EventSystem::getInstance()->fireEvent(PauseMovementEvent());
		break;
	case SHIFT_KEY:
		EventSystem::getInstance()->fireEvent(OptionsEvent());
		break;
	case NUMBER_1:
		EventSystem::getInstance()->fireEvent(NumEvent1());
		break;
	case NUMBER_2:
		EventSystem::getInstance()->fireEvent(NumEvent2());
		break;
	case NUMBER_3:
		EventSystem::getInstance()->fireEvent(NumEvent3());
		break;
	}
}

void InputTranslator::handleKeyboardEvent(const ReleasedEvent* keyEvent)
{
	switch (keyEvent->getKey())
	{
		//movement
	case D_KEY:
		EventSystem::getInstance()->fireEvent(DEventReleased());
		break;
	case A_KEY:
		EventSystem::getInstance()->fireEvent(AEventReleased());
		break;
	case L_KEY:
		EventSystem::getInstance()->fireEvent(LEventReleased());
		break;
	case J_KEY:
		EventSystem::getInstance()->fireEvent(JEventReleased());
		break;
	}
}
