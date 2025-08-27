#include "Game.h"
#include <gl/GL.h>
#include "json.hpp"



Game* Game::mpsInstance = nullptr;

Game::Game()
{}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	cleanup();

	//Initialize graphics system
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->init(mWIDTH, mHEIGHT);

	//Initialize input system
	mpInputSystem = new InputSystem();

	//hud init
	mpHud = new Hud();
	mpHud->init(10);

	//Init obstacle pool
	mpObstaclePool = new ObstaclePool();
	mpObstaclePool->init(10);

	//Init unit manager
	mpUnitManager = new UnitManager(mpHud, mpObstaclePool);
	mpUnitManager->init();

	//Init graphics buffer manager
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpGraphicsBufferManager->init();

	//Init Input translator
	mpInputTranslator = new InputTranslator();
	mpInputTranslator->init();

	//game sound amanger
	mpGameSoundManager = new GameSoundManager();
	//mpGameSoundManager->init(mSOUND_SAMPLES);



	//Add all listeners
	EventSystem* pEventSystem = EventSystem::getInstance();
	pEventSystem->addListener((EventType)CHANGE_EVENT, this);
	pEventSystem->addListener((EventType)REMOVE_UNIT_EVENT, this);
	pEventSystem->addListener((EventType)EXIT_EVENT, this);
	pEventSystem->addListener((EventType)GAME_OVER, this);
	pEventSystem->addListener((EventType)PAUSE_MOVEMENT_EVENT, this);
	pEventSystem->addListener((EventType)OPTIONS_EVENT, this);
	pEventSystem->addListener((EventType)A_EVENT, this);
	pEventSystem->addListener((EventType)D_EVENT, this);
	pEventSystem->addListener((EventType)J_EVENT, this);
	pEventSystem->addListener((EventType)L_EVENT, this);
	pEventSystem->addListener((EventType)A_EVENT_RELEASED, this);
	pEventSystem->addListener((EventType)D_EVENT_RELEASED, this);
	pEventSystem->addListener((EventType)J_EVENT_RELEASED, this);
	pEventSystem->addListener((EventType)L_EVENT_RELEASED, this);
	pEventSystem->addListener((EventType)NUM1_EVENT, this);
	pEventSystem->addListener((EventType)NUM2_EVENT, this);
	pEventSystem->addListener((EventType)NUM3_EVENT, this);

	createAssets();

	readFileData(mGAME_SETTINGS);


	mCurrentScene = Scene::SCENE_START;
	return true;
}

void Game::cleanup()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(this);

	//Cleanup in opposite order of init
	delete mpInputTranslator;
	mpInputTranslator = nullptr; 

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = nullptr;

	delete mpUnitManager;
	mpUnitManager = nullptr;

	delete mpInputSystem;
	mpInputSystem = nullptr;

	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;

	delete mpHud;
	mpHud = nullptr;

	delete mpGameSoundManager;
	mpGameSoundManager = nullptr;

	delete mpObstaclePool;
	mpObstaclePool = nullptr;
}

void Game::createAssets()
{
	//GLOW Grahpics buffer
	mpGraphicsBufferManager->addBuffer("GLOW", mASSET_PATH + mGLOW_FILENAME);

	mpGraphicsBufferManager->addBuffer("Car1", mLOCAL_ASSET_PATH + mCAR_PATH + mCAR1_FILENAME);
	mpGraphicsBufferManager->addBuffer("Car2", mLOCAL_ASSET_PATH + mCAR_PATH + mCAR2_FILENAME);

	mpGraphicsBufferManager->addBuffer("Cone", mLOCAL_ASSET_PATH + mCAR_PATH + mCONE_FILENAME);



	//Create animation from sprite sheet
	mGlowBlueAnimation = Animation(mMEDIUM_SPEED, true, mpGraphicsBufferManager->getBuffer("GLOW"), mGLOW_PIXEL_WIDTH, mGLOW_PIXEL_HEIGHT, mGLOW_SPRITES_ACROSS, mGLOW_SPRITES_DOWN, mGLOW_START_POINT_BLUE);

	//Create animation from graphics buffers
	mGlowRedAnimation = Animation(mMEDIUM_SPEED, true, mpGraphicsBufferManager->getBuffer("GLOW"), mGLOW_PIXEL_WIDTH, mGLOW_PIXEL_HEIGHT, mGLOW_SPRITES_ACROSS, mGLOW_SPRITES_DOWN, mGLOW_START_POINT_RED);

	mCar1Animation = Animation(mMEDIUM_SPEED, true, mpGraphicsBufferManager->getBuffer("Car1"), 32, 79);//lets say standard will be around 32, 64
	mCar2Animation = Animation(mMEDIUM_SPEED, true, mpGraphicsBufferManager->getBuffer("Car2"), 32, 74);//lets say standard will be around 32, 64

	mConeAnimation = Animation(mMEDIUM_SPEED, true, mpGraphicsBufferManager->getBuffer("Cone"), 64, 64);

	//Font
	mpUnitNumFont = new Font(mASSET_PATH + mFONT_FILENAME, mFONT_SIZE);

	//black background for game - jon
	mpGraphicsBufferManager->addBuffer("Black", mWIDTH, mHEIGHT, Color(0, 0, 0, 255));

	mpGraphicsSystem->initBackgroundShader("Assets/background.vert", "Assets/background.frag", mLOCAL_ASSET_PATH + mBACKGROUND_FILENAME);
}

void Game::spawnCone()
{	
	if (mpUnitManager->getConeCount() < 5)
	{
		mpUnitManager->createUnitInBounds(mConeAnimation, mPlayer1TopLeftBounds.getX(), mPlayer1TopLeftBounds.getY(), mPlayer1BottomRightBounds.getX(), mPlayer1BottomRightBounds.getY(), Vector2D(0, 2), "Cone");
		mpUnitManager->createUnitInBounds(mConeAnimation, mPlayer2TopLeftBounds.getX(), mPlayer2TopLeftBounds.getY(), mPlayer2BottomRightBounds.getX(), mPlayer2BottomRightBounds.getY(), Vector2D(0, 2), "Cone");
		mTimeSinceLastSpawn = 0.0f;
		mNextSpawnTime = randomFloatBetween(0.0f, mDifficulty);
	}
}

float Game::randomFloatBetween(float minTime, float maxTime)
{
	std::mt19937 randomGenerator(mGameDevice());
	std::uniform_real_distribution<float> randomSpawnTime(minTime, maxTime);
	return randomSpawnTime(randomGenerator);
}

void Game::readFileData(std::string fileName)
{
	using json = nlohmann::json;

	std::ifstream file(fileName);

	json jsonFile = json::parse(file);

	mDifficulty = jsonFile["BasicSettings"]["mInitialDifficulty"];
	mNextSpawnTime = jsonFile["BasicSettings"]["mInitialNextSpawnTime"];
	mPlayer1TopLeftBoundsX = jsonFile["BasicSettings"]["mPlayer1TopLeftBoundsX"];
	mPlayer1TopLeftBoundsY = jsonFile["BasicSettings"]["mPlayer1TopLeftBoundsY"];
	mPlayer1BottomRightBoundsX = jsonFile["BasicSettings"]["mPlayer1BottomRightBoundsX"];
	mPlayer1BottomRightBoundsY = jsonFile["BasicSettings"]["mPlayer1BottomRightBoundsY"];
	mPlayer2TopLeftBoundsX = jsonFile["BasicSettings"]["mPlayer2TopLeftBoundsX"];
	mPlayer2TopLeftBoundsY = jsonFile["BasicSettings"]["mPlayer2TopLeftBoundsY"];
	mPlayer2BottomRightBoundsX = jsonFile["BasicSettings"]["mPlayer2BottomRightBoundsX"];
	mPlayer2BottomRightBoundsY = jsonFile["BasicSettings"]["mPlayer2BottomRightBoundsY"];

	file.close();

	mPlayer1TopLeftBounds = Vector2D(mPlayer1TopLeftBoundsX, mPlayer1TopLeftBoundsY);
	mPlayer1BottomRightBounds = Vector2D(mPlayer1BottomRightBoundsX, mPlayer1BottomRightBoundsY);

	mPlayer2TopLeftBounds = Vector2D(mPlayer2TopLeftBoundsX, mPlayer2TopLeftBoundsY);
	mPlayer2BottomRightBounds = Vector2D(mPlayer2BottomRightBoundsX, mPlayer2BottomRightBoundsY);
}

void Game::saveGameToFile()
{
	using json = nlohmann::json;

	json savedInfo;
	savedInfo["BasicSettings"]["Player1Score"] = mpHud->getScore();
	savedInfo["BasicSettings"]["Player2Score"] = mpHud->getScore2();
	savedInfo["BasicSettings"]["TimeRemaining"] = mpHud->getTimeRemaining();

	json activeUnitPositions = json::array();
	auto currentUnits = mpUnitManager->getObjectCollection();
	for (Unit* unit : currentUnits)
	{
		if (unit != nullptr)
		{
			Vector2D unitPosition = unit->getPosition();
			json jsonVector2D = json{ {"x", unitPosition.getX()}, {"y", unitPosition.getY()} };
			activeUnitPositions.push_back(jsonVector2D);
		}
	}
	savedInfo["BasicSettings"]["activeUnitPositions"] = activeUnitPositions;

	std::ofstream outputFile("SavedGame.json");
	if (outputFile.is_open())
	{
		outputFile << savedInfo.dump(4);
		outputFile.close();
		std::cout << "Game Saved" << std::endl;
	}

	else
	{
		std::cerr << "Failed to save file" << std::endl;
	}
}

void Game::loadGameFromFile(std::string fileName)
{
	using json = nlohmann::json;

	std::ifstream file(fileName);

	json jsonFile = json::parse(file);

	mpHud->setTime(jsonFile["BasicSettings"]["TimeRemaining"]);
	mpHud->setScore(jsonFile["BasicSettings"]["Player1Score"], true);
	mpHud->setScore(jsonFile["BasicSettings"]["Player2Score"], false);

	mpUnitManager->deleteAllUnits();

	auto positions = jsonFile["BasicSettings"]["activeUnitPositions"];
	for (size_t i = 0; i < positions.size(); ++i)
	{
		float x = positions[i]["x"];
		float y = positions[i]["y"];
		Vector2D pos(x, y);

		if (i == 0)
		{
			mpUnitManager->createAndAddUnit(mCar1Animation, pos, Vector2D(0, 0), "Car1");
		}
		else if (i == 1)
		{
			mpUnitManager->createAndAddUnit(mCar2Animation, pos, Vector2D(0, 0), "Car2");
		}
		else
		{
			mpUnitManager->createUnitInBounds(mConeAnimation, pos, Vector2D(0, 2), "Cone");
		}
	}
}

void Game::doLoop()
{
	std::default_random_engine randomEngine;
	randomEngine.seed((unsigned int)time(NULL));
	std::uniform_int_distribution<> distribution(1, 100000);

	//Game loop
	while (mGameLoop)
	{
		//Start tracker
		mTracker.startTracking("GameLoop");
		mLoopTimer.start();

		//check inputs
		mpInputSystem->update(mTARGET_TIME);
		//Update units
		mpUnitManager->update(mTARGET_TIME);

		//Adjust game state
		update(mTARGET_TIME);

		//Draw current game state (render)
		render();

		//Wait until target time has elapsed
		mLoopTimer.sleepUntilElapsed(mTARGET_TIME);

		//Stop and print time loop took
		mTracker.stopTracking("GameLoop");
		//std::cout << "Game Loop took: " << mTracker.getElapsedTime("GameLoop") << std::endl;

		//Reset tracker
		mTracker.clearTracker("GameLoop");
	}

	delete mpUnitNumFont;
	mpUnitNumFont = nullptr;
}

void Game::update(float deltaTime)
{
	switch (mCurrentScene)
	{
	case Scene::SCENE_GAMELOOP:
		sceneGameLoop();
		break;/*
	case Scene::SCENE_END:
		sceneGameOver();
		break;
	case Scene::SCENE_PAUSE:
		scenePause();
		break;*/
	case Scene::SCENE_START:
		sceneStart();
		break;
	}
}

void Game::sceneGameLoop()
{
	if (mGameLoaded)
	{
		loadGameFromFile(mSAVE_SETTINGS);
		mGameLoaded = false;
		mNoCar = false;
	}
	else if (mNoCar)
	{
		mpUnitManager->createAndAddUnit(mCar1Animation, mSTARTING_LOC1, Vector2D(0, 0), "Car1");
		mpUnitManager->createAndAddUnit(mCar2Animation, mSTARTING_LOC2, Vector2D(0, 0), "Car2");
		mNoCar = false;
	}



	if (mTimeSinceLastSpawn >= mNextSpawnTime)
	{
		spawnCone();
	}

	if (mCarForce < 0)
	{
		mCarForce += 0.01;
	}
	if (mCarForce > 0)
	{
		mCarForce -= 0.01;
	}

	if (mCarForce2 < 0)
	{
		mCarForce2 += 0.01;
	}
	if (mCarForce2 > 0)
	{
		mCarForce2 -= 0.01;
	}

	if (mCarPressed1L == true && mCarForce >= mMIN_CAR_BOUNDS)
	{
		mCarForce -= mHORI_FORCE;
	}
	else if (mCarPressed1R == true && mCarForce <= mMAX_CAR_BOUNDS)
	{
		mCarForce += mHORI_FORCE;
	}
	if (mCarPressed2L == true && mCarForce2 >= mMIN_CAR_BOUNDS)
	{
		mCarForce2 -= mHORI_FORCE;
	}
	else if (mCarPressed2R == true && mCarForce2 <= mMAX_CAR_BOUNDS)
	{
		mCarForce2 += mHORI_FORCE;
	}

	mDifficulty -= 0.05f;
	mpUnitManager->getUnit(0)->setVelocity(Vector2D(mCarForce, mUpwardForce));
	mpUnitManager->getUnit(1)->setVelocity(Vector2D(mCarForce2, mUpwardForce));

	if (mpUnitManager->getObjectCollection().size() > 2)
	{
		Unit* car1 = mpUnitManager->getUnit("Car1");
		Unit* car2 = mpUnitManager->getUnit("Car2");

		for (int i = mpUnitManager->getObjectCollection().size() - 1; i > 1; i--)
		{
			Unit* currentCone = mpUnitManager->getObjectCollection()[i];
			bool collisionOccured = false;
			bool car1Collision = false;

			if (currentCone == nullptr)
			{
				mpUnitManager->deleteUnit(currentCone);
				continue;
			}

			if (car1 != nullptr && car1->checkCollsion(currentCone))
			{
				collisionOccured = true;
				car1Collision = true;
			}

			else if (car2 != nullptr && car2->checkCollsion(currentCone))
			{
				collisionOccured = true;
				car1Collision = false;
			}

			if (collisionOccured)
			{
				if (mMusicPlaying)
				{
					EventSystem::getInstance()->fireEvent(CrashSound());
				}
				int score = mpHud->getScore();
				mpHud->setScore(score - 5, car1Collision);
				currentCone->setDrawable(false);
				currentCone->setAvailability(true);
				mpUnitManager->deleteUnit(currentCone);
				mpUnitManager->setConeCount(mpUnitManager->getConeCount() - 1);
				std::cout << "Collision" << std::endl;
			}
		}

	}
}

void Game::sceneStart()
{
	//restarting values
	mDifficulty = 7000.0;
	mpUnitManager->deleteAllUnits();
	mpHud->setScore(0, 1);
	mpHud->setScore(0, 0);
}
void Game::scenePause()
{
	//the game is paused
}
void Game::sceneGameOver()
{
	//the game is gameover
	mpUnitManager->deleteAllUnits();
}

int oldObjectNum;
void Game::render()
{
	//Renders a black background
	mpGraphicsSystem->getDisplay()->clear();
	mpGraphicsSystem->drawBackgroundWithShaders();
	//mpGraphicsSystem->flip();

	switch (mCurrentScene)
	{
	case Scene::SCENE_GAMELOOP:

		//Draw Score
		mpHud->update(mTARGET_TIME);
		mpHud->drawSceneLoop(mpGraphicsSystem);
		//Draw units
		mpUnitManager->draw();
		mTimeSinceLastSpawn += 16.7;

		break;

	case Scene::SCENE_END:
		mpHud->drawSceneOver(mpGraphicsSystem);
		break;

	case Scene::SCENE_PAUSE:
		mpHud->drawScenePause(mpGraphicsSystem);
		break;

	case Scene::SCENE_START:
		mpHud->drawSceneStart(mpGraphicsSystem);
		break;

	case Scene::SCENE_OPTIONS:
		mpHud->drawSceneOptions(mpGraphicsSystem);
		break;

	case Scene::SCENE_DIFFICULTY:
		mpHud->drawSceneDifficulty(mpGraphicsSystem);
		break;

	case Scene::SCENE_MUSIC:
		mpHud->drawSceneMusic(mpGraphicsSystem);
		break;

	case Scene::SCENE_LANGUAGE:
		mpHud->drawSceneLanguage(mpGraphicsSystem);
		break;

	case Scene::SCENE_GAMEOVER:
		if (mpHud->getScore() > mpHud->getScore2())
		{
			mpHud->drawSceneWin(mpGraphicsSystem, 1);
		}
		else if (mpHud->getScore() < mpHud->getScore2())
		{
			mpHud->drawSceneWin(mpGraphicsSystem, 2);
		}
		else if (mpHud->getScore() == mpHud->getScore2())
		{
			mpHud->drawSceneWin(mpGraphicsSystem, 3);
		}
		break;
	}

	//Flip backbuffer
	mpGraphicsSystem->flip();
}

void Game::handleEvent(const Event& theEvent)
{
	EventType eventType = theEvent.getType();

	if (eventType == EXIT_EVENT)//when the player clicks esc
	{
		if (mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			//pause game
			mpUnitManager->setMovementAllUnits();
			mCurrentScene = Scene::SCENE_PAUSE;
			saveGameToFile();
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(ExtraSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_START)
		{//quit game
			mNoCar = true;
			mGameLoop = false;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SelectSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_GAMEOVER)
		{//back to menu
			mCurrentScene = Scene::SCENE_START;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SelectSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_OPTIONS || mCurrentScene == Scene::SCENE_PAUSE)
		{//back to menu
			mCurrentScene = Scene::SCENE_START;
			mNoCar = true;
			mpUnitManager->deleteAllUnits();
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SelectSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_DIFFICULTY || mCurrentScene == Scene::SCENE_LANGUAGE || mCurrentScene == Scene::SCENE_MUSIC)
		{//back to options
			mCurrentScene = Scene::SCENE_OPTIONS;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SelectSound());
			}
		}
	}
	else if (eventType == PAUSE_MOVEMENT_EVENT)//space clicked
	{
		if (mCurrentScene == Scene::SCENE_PAUSE)
		{
			//unpause everything
			mpUnitManager->setMovementAllUnits();
			mCurrentScene = Scene::SCENE_GAMELOOP;
		}
		else if (mCurrentScene == Scene::SCENE_END)
		{//try again
			mCurrentScene = Scene::SCENE_START;
		}
		else if (mCurrentScene == Scene::SCENE_START)
		{//play game
			mCurrentScene = Scene::SCENE_GAMELOOP;
			//if (mGameLoaded)
			//{
			//	//loading stuff
			//}
		}
		else if (mCurrentScene == Scene::SCENE_OPTIONS)
		{//difficulty for game select
			mCurrentScene = Scene::SCENE_DIFFICULTY;
		}
		else if (mCurrentScene == Scene::SCENE_MUSIC)
		{
			//set music on
			mMusicPlaying = true;
		}
		if (mMusicPlaying)
		{
			EventSystem::getInstance()->fireEvent(SelectSound());
		}
	}
	else if (eventType == OPTIONS_EVENT)//shift click
	{
		if (mCurrentScene == Scene::SCENE_START)
		{//options
			mCurrentScene = Scene::SCENE_OPTIONS;
		}
		else if (mCurrentScene == Scene::SCENE_OPTIONS)
		{//music from options
			mCurrentScene = Scene::SCENE_MUSIC;
		}
		else if (mCurrentScene == Scene::SCENE_MUSIC)
		{
			//set music off
			mMusicPlaying = false;
		}
		if (mMusicPlaying)
		{
			EventSystem::getInstance()->fireEvent(SelectSound());
		}
	}
	else if (eventType == NUM1_EVENT)//1 click
	{
		if (mCurrentScene == Scene::SCENE_LANGUAGE)
		{
			//change to english
			mpHud->setLanguage(0);
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SadSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_DIFFICULTY)
		{
			//change to english
			mDifficulty = 7000.0;
			std::cout << "Difficulty Swithed" << std::endl;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SadSound());
			}
		}
	}
	else if (eventType == NUM2_EVENT)//2 click
	{
		if (mCurrentScene == Scene::SCENE_LANGUAGE)
		{
			//change to english
			mpHud->setLanguage(1);
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(PirateSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_DIFFICULTY)
		{
			//change to english
			mDifficulty = 4000.0;
			std::cout << "Difficulty Swithed" << std::endl;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SadSound());
			}
		}
	}
	else if (eventType == NUM3_EVENT)//3 click
	{
		if (mCurrentScene == Scene::SCENE_LANGUAGE)
		{
			//change to english
			mpHud->setLanguage(2);
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(CarSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_DIFFICULTY)
		{
			//change to english
			mDifficulty = 2500.0;
			std::cout << "Difficulty Swithed" << std::endl;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SadSound());
			}
		}
	}
	else if (eventType == GAME_OVER)
	{
		//game over ):

		mpUnitManager->setMovementAllUnits();
		mCurrentScene = Scene::SCENE_GAMEOVER;
		if (mMusicPlaying)
		{
			EventSystem::getInstance()->fireEvent(HappySound());
		}
	}
	else if (eventType == A_EVENT)//a click
	{
		if (mCarForce > mMIN_CAR_BOUNDS && mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed1L = true;
		}
	}
	else if (eventType == D_EVENT)//d click
	{
		if (mCarForce < mMAX_CAR_BOUNDS && mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed1R = true;
		}
	}
	else if (eventType == J_EVENT)//j click
	{
		if (mCarForce2 > mMIN_CAR_BOUNDS && mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed2L = true;
		}
	}
	else if (eventType == L_EVENT)//L click
	{
		if (mCarForce2 < mMAX_CAR_BOUNDS && mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed2R = true;
		}
		else if (mCurrentScene == Scene::SCENE_START)
		{
			//load menu for zeben
			mGameLoaded = true;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SelectSound());
			}
		}
		else if (mCurrentScene == Scene::SCENE_OPTIONS)
		{
			//options
			mCurrentScene = Scene::SCENE_LANGUAGE;
			if (mMusicPlaying)
			{
				EventSystem::getInstance()->fireEvent(SelectSound());
			}
		}
	}
	else if (eventType == A_EVENT_RELEASED)//a released
	{
		if (mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed1L = false;
		}
	}
	else if (eventType == D_EVENT_RELEASED)//d released
	{
		if (mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed1R = false;
		}
	}
	else if (eventType == J_EVENT_RELEASED)//j released
	{
		if (mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed2L = false;
		}
	}
	else if (eventType == L_EVENT_RELEASED)//l released
	{
		if (mCurrentScene == Scene::SCENE_GAMELOOP)
		{
			mCarPressed2R = false;
		}
	}
}

void Game::createInstance()
{
	//If instance already exisits, return
	if (mpsInstance != nullptr) return;

	mpsInstance = new Game();
}

void Game::destroyInstance()
{
	mpsInstance->cleanup();

	delete mpsInstance;
	mpsInstance = nullptr;
}
