#pragma once

#include <map>
#include <Trackable.h>

class Event;
class EventListener;
enum EventType;

//using namespace std;

class EventSystem:public Trackable
{
public:
	static EventSystem* getInstance();
	static void createInstance();
	static void destroyInstance();

	void init();
	void cleanup();

	void fireEvent( const Event& theEvent );
	void addListener( EventType type, EventListener* pListener );
	void removeListener( EventType type, EventListener* pListener );
	void removeListenerFromAllEvents( EventListener* pListener );

private:
	static EventSystem* mspInstance;
	std::multimap< EventType, EventListener* > mListenerMap;
	bool mIsInitted = false;

	void dispatchAllEvents( const Event& theEvent );

	EventSystem();
	~EventSystem();


};

