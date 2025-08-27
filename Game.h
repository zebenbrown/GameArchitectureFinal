#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <random>
#include <ctime>
#include <fstream>

#include <PerformanceTracker.h>
#include <GraphicsBuffer.h>
#include "UnitManager.h"
#include <GraphicsBufferManager.h>
#include <Sprite.h>
#include <Color.h>
#include <Font.h>
#include <EventListener.h>

#include <Animation.h>
#include <GraphicsSystem.h>
#include <InputSystem.h>
#include <EventSystem.h>
#include "InputTranslator.h"
#include "GameEvent.h"

#include "Unit.h"

#include <Event.h>
#include "Hud.h"
#include "GameSoundManager.h"



class InputTranslator;
class InputSystem;
class GraphicsSystem;

class Game : public EventListener
{

public:
	enum class Scene
	{
		SCENE_START,
		SCENE_GAMELOOP,
		SCENE_PAUSE,
		SCENE_END,
		SCENE_OPTIONS,
		SCENE_DIFFICULTY,
		SCENE_LANGUAGE,
		SCENE_GAMEOVER,
		SCENE_MUSIC
	};

	bool init();
	void cleanup();
	void createAssets();

	void doLoop();
	void update(float deltaTime);
	void render();

	void handleEvent(const Event& theEvent);

	static Game* getInstance() { assert(mpsInstance != nullptr); return mpsInstance; }
	static void createInstance();
	static void destroyInstance();
	Scene getCurrentScene() { return mCurrentScene; };
	void sceneGameLoop();
	void scenePause();
	void sceneStart();
	void sceneGameOver();

private:
	Game();
	~Game();

	void spawnCone();
	float randomFloatBetween(float minTime, float maxTime);
	void readFileData(std::string fileName);
	void saveGameToFile();
	void loadGameFromFile(std::string fileName);

	static Game* mpsInstance;

	GraphicsSystem* mpGraphicsSystem = nullptr;
	InputSystem* mpInputSystem = nullptr;
	UnitManager* mpUnitManager = nullptr;
	ObstaclePool* mpObstaclePool = nullptr;
	GraphicsBufferManager* mpGraphicsBufferManager = nullptr;
	InputTranslator* mpInputTranslator = nullptr;
	Hud* mpHud = nullptr;
	GameSoundManager* mpGameSoundManager = nullptr;

	PerformanceTracker mTracker;
	Timer mLoopTimer;

	Scene mCurrentScene;

	bool mNoCar = true;
	bool mMusicPlaying = true;
	bool mIsMoving = false;
	bool mGameLoaded = false;
	bool mCarPressed1L = false;
	bool mCarPressed1R = false;
	bool mCarPressed2L = false;
	bool mCarPressed2R = false;
	float mCarForce = 0;
	float mCarForce2 = 0;
	float mUpwardForce = 0;
	const int mMIN_CAR_BOUNDS = -2;
	const int mMAX_CAR_BOUNDS = 2;
	const float mHORI_FORCE = 0.05;
	const Vector2D mSTARTING_LOC1 = Vector2D(300, 500);
	const Vector2D mSTARTING_LOC2 = Vector2D(550, 500);

	const Vector2D mPLAYER1_CONE_BOUNDS_TOP_LEFT = Vector2D(150, 25);
	const Vector2D mPLAYER1_CONE_BOUNDS_BOTTOM_RIGHT = Vector2D(400, 300);

	const Vector2D mPLAYER2_CONE_BOUNDS_TOP_LEFT = Vector2D(400, 25);
	const Vector2D mPLAYER2_CONE_BOUNDS_BOTTOM_RIGHT = Vector2D(650, 300);

	bool mGameLoop = true;

	const unsigned int mWIDTH = 800;
	const unsigned int mHEIGHT = 600;

	Animation mGlowBlueAnimation;
	Animation mGlowRedAnimation;
	Animation mCar1Animation;
	Animation mCar2Animation;
	Animation mConeAnimation;

	Font* mpUnitNumFont = nullptr;

	const float mFAST_SPEED = 30.0f;
	const float mMEDIUM_SPEED = 15.0f;
	const float mSLOW_SPEED = 5.0f;

	const float mTARGET_TIME = 1000.0f / 60.0f; //In miliseconds, 1000/60, 1000/desired framerate

	//variables to make game function
	int mSpawnRate = 60;//this will mean 1 in mSPAWN_RATE chance of orb spawning. This is done every frame
	float mDifficulty = 10000.0;
	std::random_device mGameDevice;
	float mTimeSinceLastSpawn = 0.0f;
	//Three seconds in milliseconds
	float mNextSpawnTime = 3000.0f;
	int mActiveCones = 0;

	//Player 1 Cone Spawn Bounds
	int mPlayer1TopLeftBoundsX = 0;
	int mPlayer1TopLeftBoundsY = 0;
	int mPlayer1BottomRightBoundsX = 0;
	int mPlayer1BottomRightBoundsY = 0;

	Vector2D mPlayer1TopLeftBounds;
	Vector2D mPlayer1BottomRightBounds;

	//Player 2 Cone Spawn Bounds
	int mPlayer2TopLeftBoundsX = 0;
	int mPlayer2TopLeftBoundsY = 0;
	int mPlayer2BottomRightBoundsX = 0;
	int mPlayer2BottomRightBoundsY = 0;

	Vector2D mPlayer2TopLeftBounds;
	Vector2D mPlayer2BottomRightBounds;
};

//Assets
const std::string mLOCAL_ASSET_PATH = "Assets\\";
const std::string mASSET_PATH = "assets\\";
const std::string mCAR_PATH = "Cars\\";
const std::string mBACKGROUND_FILENAME = "FinalProjectRoadBackground.png";

const std::string mCAR1_FILENAME = "car.png";
const std::string mCAR2_FILENAME = "car2.png";
const std::string mCONE_FILENAME = "cone.png";

const std::string mGAME_SETTINGS = "GameSettings.json";
const std::string mSAVE_SETTINGS = "SavedGame.json";

//Glow
const std::string mGLOW_FILENAME = "Glowing-balls.png";

const unsigned int mGLOW_PIXEL_WIDTH = 32;
const unsigned int mGLOW_PIXEL_HEIGHT = 32;
const unsigned int mGLOW_SPRITES_ACROSS = 6;
const unsigned int mGLOW_SPRITES_DOWN = 2;
const Vector2D mGLOW_START_POINT_BLUE = Vector2D(4, 6);
const Vector2D mGLOW_START_POINT_RED = Vector2D(4, 0);

//Googly eye
const int mGOOGLY_EYE_SPRITE_NUM = 5;
const std::string mGOOGLY_EYE[mGOOGLY_EYE_SPRITE_NUM] = { "googly-a.png","googly-b.png","googly-c.png","googly-d.png","googly-e.png" };

const unsigned int mEYE_PIXEL_WIDTH = 326;
const unsigned int mEYE_PIXEL_HEIGHT = 330;

//Font
const std::string mFONT_FILENAME = "cour.ttf";
const int mFONT_SIZE = 80;
const Color mRED = Color(255, 0, 0);

const int mSOUND_SAMPLES = 3;