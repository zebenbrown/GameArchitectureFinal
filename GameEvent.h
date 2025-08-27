#pragma once
#include <Event.h>
#include <Vector2D.h>

enum GameEventType
{
	CHANGE_EVENT = 2,
	REMOVE_UNIT_EVENT,
	EXIT_EVENT,
	GAME_OVER,
	PAUSE_MOVEMENT_EVENT,
	OPTIONS_EVENT,
	NUM1_EVENT,
	NUM2_EVENT,
	NUM3_EVENT,
	NUM_GAME_EVENT_TYPES,
	SAD_SOUND,
	SELECT_SOUND,
	CAR_SOUND,
	PIRATE_SOUND,
	CRASH_SOUND,
	EXTRA_SOUND,
	HAPPY_SOUND,
	A_EVENT,
	D_EVENT,
	J_EVENT,
	L_EVENT,
	A_EVENT_RELEASED,
	D_EVENT_RELEASED,
	J_EVENT_RELEASED,
	L_EVENT_RELEASED
};

class GameEvent : public Event
{
public:
	GameEvent(GameEventType type) : Event(((EventType)type)) {}

private:
};

class ChangeEvent : public GameEvent
{
public:
	ChangeEvent(const Vector2D& movePos) : GameEvent(CHANGE_EVENT), mPos(movePos) {}

	Vector2D getLocation() const { return mPos; }
private:
	Vector2D mPos;
};

class SelectSound : public GameEvent
{
public:
	SelectSound() : GameEvent(SELECT_SOUND) {}
private:
};

class HappySound : public GameEvent
{
public:
	HappySound() : GameEvent(HAPPY_SOUND) {}
private:
};

class ExtraSound : public GameEvent
{
public:
	ExtraSound() : GameEvent(EXTRA_SOUND) {}
private:
};

class SadSound : public GameEvent
{
public:
	SadSound() : GameEvent(SAD_SOUND) {}
private:
};

class PirateSound : public GameEvent
{
public:
	PirateSound() : GameEvent(PIRATE_SOUND) {}
private:
};

class CarSound : public GameEvent
{
public:
	CarSound() : GameEvent(CAR_SOUND) {}
private:
};

class AEvent : public GameEvent
{
public:
	AEvent() : GameEvent(A_EVENT) {}
private:
};

class DEvent : public GameEvent
{
public:
	DEvent() : GameEvent(D_EVENT) {}
private:
};
class JEvent : public GameEvent
{
public:
	JEvent() : GameEvent(J_EVENT) {}
private:
};

class LEvent : public GameEvent
{
public:
	LEvent() : GameEvent(L_EVENT) {}
private:
};

class AEventReleased : public GameEvent
{
public:
	AEventReleased() : GameEvent(A_EVENT_RELEASED) {}
private:
};

class DEventReleased : public GameEvent
{
public:
	DEventReleased() : GameEvent(D_EVENT_RELEASED) {}
private:
};
class JEventReleased : public GameEvent
{
public:
	JEventReleased() : GameEvent(J_EVENT_RELEASED) {}
private:
};

class LEventReleased : public GameEvent
{
public:
	LEventReleased() : GameEvent(L_EVENT_RELEASED) {}
private:
};

class CrashSound : public GameEvent
{
public:
	CrashSound() : GameEvent(CRASH_SOUND) {}
private:
};

class RemoveUnitEvent : public GameEvent
{
public:
	RemoveUnitEvent(Vector2D movePos) : GameEvent(REMOVE_UNIT_EVENT), mPos(movePos) {}

	Vector2D getLocation() { return mPos; }
private:
	Vector2D mPos;
};

class ExitEvent : public GameEvent
{
public:
	ExitEvent() : GameEvent(EXIT_EVENT) {}
private:
};

class GameOver : public GameEvent
{
public:
	GameOver() : GameEvent(GAME_OVER) {}
private:
};

class PauseMovementEvent : public GameEvent
{
public:
	PauseMovementEvent() : GameEvent(PAUSE_MOVEMENT_EVENT) {}
private:
};

class OptionsEvent : public GameEvent
{
public:
	OptionsEvent() : GameEvent(OPTIONS_EVENT) {}
private:
};

class NumEvent1 : public GameEvent
{
public:
	NumEvent1() : GameEvent(NUM1_EVENT) {}
private:
};

class NumEvent2 : public GameEvent
{
public:
	NumEvent2() : GameEvent(NUM2_EVENT) {}
private:
};

class NumEvent3 : public GameEvent
{
public:
	NumEvent3() : GameEvent(NUM3_EVENT) {}
private:
};