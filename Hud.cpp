#include "Hud.h"

const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
const std::string FONT_FILENAME = "cour.ttf";
const int FONT_SIZE = 30;
const Color FONT_COLOR(255, 255, 255);

Hud::Hud()
{
}

Hud::~Hud()
{
	cleanup();
}

bool Hud::init(int startScore)
{
	cleanup();
	mpFont = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE);
	mScore = startScore;
	mScore2 = startScore;
	mInitScore = startScore;
	mLanguage = 0;

	return true;
}

void Hud::cleanup()
{
	if (mpFont != nullptr)
	{
		delete mpFont;
		mpFont = nullptr;
	}
}

void Hud::drawSceneLoop(GraphicsSystem* pGraphicsSystem)
{
	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(0, 560), *mpFont, FONT_COLOR, "FPS: " + std::to_string(mFPS));
		pGraphicsSystem->writeText(Vector2D(0, 0), *mpFont, FONT_COLOR, "P1 Score: " + scoreFormatChange(1));
		pGraphicsSystem->writeText(Vector2D(560, 0), *mpFont, FONT_COLOR, scoreFormatChange(0) + " :P2 Score");
		pGraphicsSystem->writeText(Vector2D(325, 0), *mpFont, FONT_COLOR, timeFormatChange());
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(0, 560), *mpFont, FONT_COLOR, "Chase: " + std::to_string(mFPS));
		pGraphicsSystem->writeText(Vector2D(0, 0), *mpFont, FONT_COLOR, "P1 Booty: " + scoreFormatChange(1));
		pGraphicsSystem->writeText(Vector2D(560, 0), *mpFont, FONT_COLOR, scoreFormatChange(0) + " :P2 Booty");
		pGraphicsSystem->writeText(Vector2D(325, 0), *mpFont, FONT_COLOR, timeFormatChange());
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(0, 560), *mpFont, FONT_COLOR, "MPH: " + std::to_string(mFPS));
		pGraphicsSystem->writeText(Vector2D(0, 0), *mpFont, FONT_COLOR, "P1 Miles: " + scoreFormatChange(1));
		pGraphicsSystem->writeText(Vector2D(560, 0), *mpFont, FONT_COLOR, scoreFormatChange(0) + " :P2 Miles");
		pGraphicsSystem->writeText(Vector2D(325, 0), *mpFont, FONT_COLOR, timeFormatChange());
		break;
	}
}
void Hud::drawScenePause(GraphicsSystem* pGraphicsSystem)
{
	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.25f), *mpFont, FONT_COLOR, "You have paused the game!");
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.5f), *mpFont, FONT_COLOR, "Press 'SPACE' to unpause.");
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.75f), *mpFont, FONT_COLOR, "Press 'ESCAPE' to return to start menu.");
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.25f), *mpFont, FONT_COLOR, "All hands on deck!!");
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.5f), *mpFont, FONT_COLOR, "Press 'SPACE' to raise anchor.");
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.75f), *mpFont, FONT_COLOR, "Press 'ESCAPE' to spring upon 'er.");
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.25f), *mpFont, FONT_COLOR, "You came to a full stop!");
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.5f), *mpFont, FONT_COLOR, "Step on the 'Space'!");
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.25f, mHEIGHT * 0.75f), *mpFont, FONT_COLOR, "Reverse with 'ESCAPE'");
		break;
	}
}
void Hud::drawSceneOver(GraphicsSystem* pGraphicsSystem)
{
	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.25f), *mpFont, FONT_COLOR, "You have lost the game!", Font::CENTER);
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.5f), *mpFont, FONT_COLOR, "Thanks for playing!", Font::CENTER);
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.75f), *mpFont, FONT_COLOR, "Press 'SPACE' to return to main menu.", Font::CENTER);
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.25f), *mpFont, FONT_COLOR, "Shiver me timbers!", Font::CENTER);
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.5f), *mpFont, FONT_COLOR, "You have fallen into Davy Jones’ locker..", Font::CENTER);
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.75f), *mpFont, FONT_COLOR, "Press 'SPACE' to scourge of the 7 seas!", Font::CENTER);
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.25f), *mpFont, FONT_COLOR, "You crashed.", Font::CENTER);
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.5f), *mpFont, FONT_COLOR, "Rev up those engines anew!", Font::CENTER);
		pGraphicsSystem->writeText(Vector2D(mWIDTH * 0.5f, mHEIGHT * 0.75f), *mpFont, FONT_COLOR, "Vroom Vroom with 'SPACE'", Font::CENTER);
		break;
	}
}
void Hud::drawSceneStart(GraphicsSystem* pGraphicsSystem)
{
	mTime = 120 * 1000;//start time

	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(0, 560), *mpFont, FONT_COLOR, "FPS: " + std::to_string(mFPS));
		pGraphicsSystem->writeText(Vector2D(0, 0), *mpFont, FONT_COLOR, "P1 Score: " + scoreFormatChange(1));
		pGraphicsSystem->writeText(Vector2D(560, 0), *mpFont, FONT_COLOR, scoreFormatChange(0) + " :P2 Score");
		pGraphicsSystem->writeText(Vector2D(325, 0), *mpFont, FONT_COLOR, timeFormatChange());
		pGraphicsSystem->writeText(Vector2D(250, 120), *mpFont, FONT_COLOR, "Welcome to race game!");
		pGraphicsSystem->writeText(Vector2D(240, 140), *mpFont, FONT_COLOR, "--------------------");
		pGraphicsSystem->writeText(Vector2D(300, 175), *mpFont, FONT_COLOR, "SELECT ONE:");
		pGraphicsSystem->writeText(Vector2D(250, 225), *mpFont, FONT_COLOR, "Space - Play New Game");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "L - Load Game From File");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "LShift - Options");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Quit Game");
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(0, 560), *mpFont, FONT_COLOR, "Chase: " + std::to_string(mFPS));
		pGraphicsSystem->writeText(Vector2D(0, 0), *mpFont, FONT_COLOR, "P1 Booty: " + scoreFormatChange(1));
		pGraphicsSystem->writeText(Vector2D(560, 0), *mpFont, FONT_COLOR, scoreFormatChange(0) + " :P2 Booty");
		pGraphicsSystem->writeText(Vector2D(325, 0), *mpFont, FONT_COLOR, timeFormatChange());
		pGraphicsSystem->writeText(Vector2D(250, 120), *mpFont, FONT_COLOR, "Ahoy, me hearties!");
		pGraphicsSystem->writeText(Vector2D(240, 140), *mpFont, FONT_COLOR, "-------------------");
		pGraphicsSystem->writeText(Vector2D(300, 175), *mpFont, FONT_COLOR, "AVAST YE:");
		pGraphicsSystem->writeText(Vector2D(250, 225), *mpFont, FONT_COLOR, "Space - Landlubber Route");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "L - Old Salt Route");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "LShift - Crow's Nest");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Walk the plank");
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(0, 560), *mpFont, FONT_COLOR, "MPH: " + std::to_string(mFPS));
		pGraphicsSystem->writeText(Vector2D(0, 0), *mpFont, FONT_COLOR, "P1 Miles: " + scoreFormatChange(1));
		pGraphicsSystem->writeText(Vector2D(560, 0), *mpFont, FONT_COLOR, scoreFormatChange(0) + " :P2 Miles");
		pGraphicsSystem->writeText(Vector2D(325, 0), *mpFont, FONT_COLOR, timeFormatChange());
		pGraphicsSystem->writeText(Vector2D(300, 120), *mpFont, FONT_COLOR, "Grand Prix!");
		pGraphicsSystem->writeText(Vector2D(275, 140), *mpFont, FONT_COLOR, "----------------");
		pGraphicsSystem->writeText(Vector2D(300, 175), *mpFont, FONT_COLOR, "Gear Shift:");
		pGraphicsSystem->writeText(Vector2D(250, 225), *mpFont, FONT_COLOR, "Space - Ready, Set, Go!");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "L - Victory Lap!");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "LShift - Pit Stop");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Retire");
		break;
	}
}
void Hud::drawSceneOptions(GraphicsSystem* pGraphicsSystem)
{
	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(350, 120), *mpFont, FONT_COLOR, "OPTIONS");
		pGraphicsSystem->writeText(Vector2D(300, 140), *mpFont, FONT_COLOR, "------------");
		pGraphicsSystem->writeText(Vector2D(300, 175), *mpFont, FONT_COLOR, "SELECT ONE:");
		pGraphicsSystem->writeText(Vector2D(250, 225), *mpFont, FONT_COLOR, "Space - Starting Difficulty");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "L - Language Select");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "LShift - Sound/Music");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Start Menu");
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(300, 120), *mpFont, FONT_COLOR, "CROW'S NEST");
		pGraphicsSystem->writeText(Vector2D(275, 140), *mpFont, FONT_COLOR, "-------------");
		pGraphicsSystem->writeText(Vector2D(300, 175), *mpFont, FONT_COLOR, "AVAST YE:");
		pGraphicsSystem->writeText(Vector2D(250, 225), *mpFont, FONT_COLOR, "Space - Wave Strength");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "L - Go On Account");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "LShift - Sea Shanty");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Jacob's Ladder");
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(350, 120), *mpFont, FONT_COLOR, "PIT STOP");
		pGraphicsSystem->writeText(Vector2D(325, 140), *mpFont, FONT_COLOR, "-----------");
		pGraphicsSystem->writeText(Vector2D(300, 175), *mpFont, FONT_COLOR, "GEAR SHIFT:");
		pGraphicsSystem->writeText(Vector2D(250, 225), *mpFont, FONT_COLOR, "Space - CC");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "L - Horn Choice");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "LShift - Radio");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Set Up");
		break;
	}
}
void Hud::drawSceneDifficulty(GraphicsSystem* pGraphicsSystem)
{
	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(250, 120), *mpFont, FONT_COLOR, "STARTING DIFFICULTY");
		pGraphicsSystem->writeText(Vector2D(225, 140), *mpFont, FONT_COLOR, "---------------------");
		pGraphicsSystem->writeText(Vector2D(100, 175), *mpFont, FONT_COLOR, "This will adjust starting cone freq.");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "SELECT ONE:");
		pGraphicsSystem->writeText(Vector2D(250, 275), *mpFont, FONT_COLOR, "1 - Easy");
		pGraphicsSystem->writeText(Vector2D(250, 325), *mpFont, FONT_COLOR, "2 - Medium");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "3 - Hard");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Options Menu");
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(300, 120), *mpFont, FONT_COLOR, "WAVE STRENGTH");
		pGraphicsSystem->writeText(Vector2D(275, 140), *mpFont, FONT_COLOR, "----------------");
		pGraphicsSystem->writeText(Vector2D(250, 175), *mpFont, FONT_COLOR, "Buccaneer Experience");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "AVAST YE:");
		pGraphicsSystem->writeText(Vector2D(250, 275), *mpFont, FONT_COLOR, "1 - Calm");
		pGraphicsSystem->writeText(Vector2D(250, 325), *mpFont, FONT_COLOR, "2 - Rough");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "3 - Piracy");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Jacob's Ladder");
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(400, 120), *mpFont, FONT_COLOR, "CC");
		pGraphicsSystem->writeText(Vector2D(375, 140), *mpFont, FONT_COLOR, "-----");
		pGraphicsSystem->writeText(Vector2D(200, 175), *mpFont, FONT_COLOR, "Just like Mario Kart");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "GEAR SHIFT:");
		pGraphicsSystem->writeText(Vector2D(250, 275), *mpFont, FONT_COLOR, "1 - 100 CC");
		pGraphicsSystem->writeText(Vector2D(250, 325), *mpFont, FONT_COLOR, "2 - 150 CC");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "3 - 200 CC");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Set Up");
		break;
	}
}
void Hud::drawSceneLanguage(GraphicsSystem* pGraphicsSystem)
{
	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "SELECT YOUR LANGUAGE");
		pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "-----------------------");
		pGraphicsSystem->writeText(Vector2D(100, 175), *mpFont, FONT_COLOR, "This is the language of the game.");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "SELECT ONE:");
		pGraphicsSystem->writeText(Vector2D(250, 275), *mpFont, FONT_COLOR, "1 - English");
		pGraphicsSystem->writeText(Vector2D(250, 325), *mpFont, FONT_COLOR, "2 - Pirate");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "3 - Car");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Options Menu");
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(300, 120), *mpFont, FONT_COLOR, "GO ON ACCOUNT");
		pGraphicsSystem->writeText(Vector2D(250, 140), *mpFont, FONT_COLOR, "-------------------");
		pGraphicsSystem->writeText(Vector2D(200, 175), *mpFont, FONT_COLOR, "How to splice the mainbrace!");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "AVAST YE:");
		pGraphicsSystem->writeText(Vector2D(250, 275), *mpFont, FONT_COLOR, "1 - Privateer");
		pGraphicsSystem->writeText(Vector2D(250, 325), *mpFont, FONT_COLOR, "2 - Yo-Ho-Ho!");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "3 - Vessel");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Jacob's Ladder");
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(300, 120), *mpFont, FONT_COLOR, "HORN CHOICE");
		pGraphicsSystem->writeText(Vector2D(250, 140), *mpFont, FONT_COLOR, "-----------------");
		pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "The language your car speaks.");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "GEAR SHIFT:");
		pGraphicsSystem->writeText(Vector2D(250, 275), *mpFont, FONT_COLOR, "1 - Beep");
		pGraphicsSystem->writeText(Vector2D(250, 325), *mpFont, FONT_COLOR, "2 - Beeeeep Beeeeep");
		pGraphicsSystem->writeText(Vector2D(250, 375), *mpFont, FONT_COLOR, "3 - La Cucaracha");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Set Up");
		break;
	}
}
void Hud::drawSceneWin(GraphicsSystem* pGraphicsSystem, int winner)
{
	switch (mLanguage)
	{
	case 0:
		//English
		switch (winner)
		{
		case 1:
			//player 1 wins
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "PLAYER ONE WINS");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "--------------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Final Score: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Player 2 Score: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Start Menu");
			break;
		case 2:
			//player 2 wins
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "PLAYER TWO WINS");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "------------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Final Score: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Player 1 Score: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Start Menu");
			break;
		case 3:
			//tie
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "IT'S A TIE!");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "-----------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Player 1 Score: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Player 2 Score: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Start Menu");
			break;
		}
		break;
	case 1:
		//Pirate
		switch (winner)
		{
		case 1:
			//player 1 wins
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "PIRATE ONE WINS");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "--------------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Final Booty: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Pirate 2 Booty: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Back to the ship!");
			break;
		case 2:
			//player 2 wins
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "PIRATE TWO WINS");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "---------------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Final Booty: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Pirate 1 Booty: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Back to the ship!");
			break;
		case 3:
			//tie
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "IT'S A TIE!");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "--------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Pirate 1 Booty: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Pirate 2 Booty: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Back to the ship!");
			break;
		}
		break;
	case 2:
		//Car
		switch (winner)
		{
		case 1:
			//player 1 wins
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "RACER ONE WINS");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "---------------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Final Miles: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Racer 2 Miles: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Set Up");
			break;
		case 2:
			//player 2 wins
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "RACER TWO WINS");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "---------------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Final Miles: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Racer 1 Miles: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Set Up");
			break;
		case 3:
			//tie
			pGraphicsSystem->writeText(Vector2D(225, 120), *mpFont, FONT_COLOR, "IT'S A TIE!");
			pGraphicsSystem->writeText(Vector2D(200, 140), *mpFont, FONT_COLOR, "-------------------");
			pGraphicsSystem->writeText(Vector2D(150, 175), *mpFont, FONT_COLOR, "Racer 1 Miles: " + scoreFormatChange(1));
			pGraphicsSystem->writeText(Vector2D(150, 275), *mpFont, FONT_COLOR, "Racer 2 Miles: " + scoreFormatChange(0));
			pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Set Up");
			break;
		}
		break;
	}
}
void Hud::drawSceneMusic(GraphicsSystem* pGraphicsSystem)
{
	switch (mLanguage)
	{
	case 0:
		//English
		pGraphicsSystem->writeText(Vector2D(275, 120), *mpFont, FONT_COLOR, "SOUND/MUSIC MENU");
		pGraphicsSystem->writeText(Vector2D(250, 140), *mpFont, FONT_COLOR, "-------------------");
		pGraphicsSystem->writeText(Vector2D(175, 175), *mpFont, FONT_COLOR, "Toggle the sounds and music.");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "SELECT ONE:");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "Space - On");
		pGraphicsSystem->writeText(Vector2D(250, 350), *mpFont, FONT_COLOR, "LShift - Off");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Options Menu");
		break;
	case 1:
		//Pirate
		pGraphicsSystem->writeText(Vector2D(350, 120), *mpFont, FONT_COLOR, "SEA SHANTY");
		pGraphicsSystem->writeText(Vector2D(300, 140), *mpFont, FONT_COLOR, "--------------");
		pGraphicsSystem->writeText(Vector2D(200, 175), *mpFont, FONT_COLOR, "The volume of instruments!");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "AVAST YE:");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "Space - Forte");
		pGraphicsSystem->writeText(Vector2D(250, 350), *mpFont, FONT_COLOR, "LShift - Piano");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Jacob's Ladder");
		break;
	case 2:
		//Car
		pGraphicsSystem->writeText(Vector2D(375, 120), *mpFont, FONT_COLOR, "RADIO");
		pGraphicsSystem->writeText(Vector2D(350, 140), *mpFont, FONT_COLOR, "--------");
		pGraphicsSystem->writeText(Vector2D(250, 175), *mpFont, FONT_COLOR, "Turn down for what?");
		pGraphicsSystem->writeText(Vector2D(300, 225), *mpFont, FONT_COLOR, "GEAR SHIFT:");
		pGraphicsSystem->writeText(Vector2D(250, 300), *mpFont, FONT_COLOR, "Space - Blasting");
		pGraphicsSystem->writeText(Vector2D(250, 350), *mpFont, FONT_COLOR, "LShift - Serious Drive");
		pGraphicsSystem->writeText(Vector2D(250, 450), *mpFont, FONT_COLOR, "Escape - Set Up");
		break;
	}
}

void Hud::update(float deltaTime)
{
	mTimer += deltaTime;
	if (mTimer >= 1000.0f)
	{
		mTime -= mTimer;
		mScore += 1;
		mScore2 += 1;
		mTimer -= 1000.0f;
	}

	mFPS = 1000 / deltaTime;

	if (mTime <= 0)
	{
		/*int tempScore1 = mScore;
		int tempScore2 = mScore2;
		mScoreFinal = tempScore1;
		mScoreFinal2 = tempScore2;
		mScore = mInitScore;
		mScore2 = mInitScore;*/
		EventSystem::getInstance()->fireEvent(GameOver());
	}
}

void Hud::setScore(int newScore, bool playerSelect)
{
	if (playerSelect)
	{
		mScore = newScore;
	}
	else if (!playerSelect)
	{
		mScore2 = newScore;
	}
}

void Hud::setTime(float time)
{
	mTime = time;
}

void Hud::setFinalScores()
{
	mScoreFinal = 0;
	mScoreFinal2 = 0;
}

void Hud::setLanguage(int newLanguage)
{
	mLanguage = newLanguage;
}

std::string Hud::timeFormatChange()
{
	int time = static_cast<int>(mTime);
	int seconds = time / 1000;
	int remainingTime = seconds % 60;
	int minutes = time / (1000 * 60);

	std::string str;

	str = "Time: " + std::to_string(minutes) + ":" + std::to_string(remainingTime);

	return str;
}

std::string Hud::scoreFormatChange(bool playerSelect)
{
	/*int score = static_cast<int>(mScore);
	int smallScore = score / 1000;
	int actualPoints = smallScore % 60;*/

	std::string str;

	if (playerSelect)
	{
		str = std::to_string(mScore);
	}
	else if (!playerSelect)
	{
		str = std::to_string(mScore2);
	}

	return str;
}