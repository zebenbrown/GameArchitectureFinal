#pragma once

#include <EventListener.h>

#include "Event.h"
#include <InterfaceEvent.h>

//Interprate interface events and send Game events
class InputTranslator : public EventListener
{
public:
	InputTranslator();
	~InputTranslator();

	void init();
	void cleanup();

	void update();
	void handleEvent(const Event& theEvent);
	void handleMouseEvent(const MouseEvent* mouseEvent);
	void handleKeyboardEvent(const KeyboardEvent* keyEvent);
	void handleKeyboardEvent(const ReleasedEvent* keyEvent);
private:
};

