#pragma once

#include <EventSystem.h>
#include "GameEvent.h"
#include "Trackable.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "Font.h"
#include "Color.h"


class Hud : public Trackable
{

public:
	Hud();
	~Hud();

	bool init(int startScore);
	void setScore(int newScore, bool playerSelect);
	void setLanguage(int newLanguage);
	int getScore() { return mScore; };
	int getScore2() { return mScore2; };
	float getTimeRemaining() { return mTime; };
	void setTime(float time);
	void setFinalScores();
	void cleanup();
	void update(float deltaTime);
	
	void drawSceneOver(GraphicsSystem* pGraphicsSystem);
	void drawScenePause(GraphicsSystem* pGraphicsSystem);
	void drawSceneStart(GraphicsSystem* pGraphicsSystem);
	void drawSceneOptions(GraphicsSystem* pGraphicsSystem);
	void drawSceneDifficulty(GraphicsSystem* pGraphicsSystem);
	void drawSceneLanguage(GraphicsSystem* pGraphicsSystem);
	void drawSceneWin(GraphicsSystem* pGraphicsSystem, int winner);
	void drawSceneMusic(GraphicsSystem* pGraphicsSystem);
	
	void drawSceneLoop(GraphicsSystem* pGraphicsSystem);

private:
	int mFPS;
	int mScore;
	int mScore2;
	int mScoreFinal;
	int mScoreFinal2;
	int mInitScore;
	int mLanguage;
	float mTime = 120;
	float mTimer = 0.0f;

	const unsigned int mWIDTH = 800;
	const unsigned int mHEIGHT = 600;

	std::string timeFormatChange();
	std::string scoreFormatChange(bool playerSelect);
	Font* mpFont = nullptr;
};