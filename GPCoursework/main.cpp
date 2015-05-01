#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include <string>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "frogGame.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{
	float timer = 0;
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\car1.png", "Images\\car2.png", "Images\\car3.png", "Images\\car4.png", "Images\\Log1.png", "Images\\Log2.png" };
	for (int tCount = 0; tCount < 6; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/Theme.wav", "Audio/CarSplat.wav", "Audio/CarEnter.wav"};

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("CarSplat", gameSounds[1]);
	theSoundMgr->add("CarEnter", gameSounds[2]);
	//Loop main music
	theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	// Creating an array of Logs
	for (int logs = 0; logs < 4; logs++)
	{
		theLogs.push_back(new cLog);
		theLogs[logs]->setSpritePos(glm::vec2(0 + (logs * 300), 150));
		theLogs[logs]->setSpriteTranslation(glm::vec2(10, 0));
		int randLog = rand() % 2 + 4;
		theLogs[logs]->setTexture(theGameTextures[randLog]->getTexture());
		theLogs[logs]->setTextureDimensions(theGameTextures[randLog]->getTWidth(), theGameTextures[randLog]->getTHeight());
		theLogs[logs]->setSpriteCentre();
		theLogs[logs]->setLogVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theLogs[logs]->setActive(true);
		theLogs[logs]->setMdlRadius();
	}


	//Creating an array of Cars
	for (int cars = 0; cars < 5; cars++)
	{
		theCars.push_back(new cCar);
		theCars[cars]->attachSoundMgr(theSoundMgr); // Attach the sound manager to the sprite
		theCars[cars]->setSpritePos(glm::vec2(768 - (cars * 300), 552));
		theCars[cars]->setSpriteTranslation(glm::vec2(-10, 0));
		int randCar = rand() % 2;
		theCars[cars]->setTexture(theGameTextures[randCar]->getTexture());
		theCars[cars]->setTextureDimensions(theGameTextures[randCar]->getTWidth(), theGameTextures[randCar]->getTHeight());
		theCars[cars]->setSpriteCentre();
		theCars[cars]->setCarVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theCars[cars]->setActive(true);
		theCars[cars]->setMdlRadius();
	}
	
	for (int cars2 = 0; cars2 < 5; cars2++)
	{
		theCars2.push_back(new cCar2);
		theCars2[cars2]->attachSoundMgr(theSoundMgr); // Attach the sound manager to the sprite
		theCars2[cars2]->setSpritePos(glm::vec2(768 - (cars2 * 250), 465));
		theCars2[cars2]->setSpriteTranslation(glm::vec2(20, 0));
		int randCar2 = rand() % 2 + 2;
		theCars2[cars2]->setTexture(theGameTextures[randCar2]->getTexture());
		theCars2[cars2]->setTextureDimensions(theGameTextures[randCar2]->getTWidth(), theGameTextures[randCar2]->getTHeight());
		theCars2[cars2]->setSpriteCentre();
		theCars2[cars2]->setCarVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theCars2[cars2]->setActive(true);
		theCars2[cars2]->setMdlRadius();
	}


	//Rendering background images
	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\BackGround.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

	cTexture MainMenu2;
	MainMenu2.createTexture("Images\\MainMenu.png");
	cBkGround mainMenu;
	mainMenu.setSpritePos(glm::vec2(0.0f, 0.0f));
	mainMenu.setTexture(MainMenu2.getTexture());
	mainMenu.setTextureDimensions(MainMenu2.getTWidth(), MainMenu2.getTHeight());

	cTexture GameOver2;
	GameOver2.createTexture("Images\\GameOver.png");
	cBkGround GameOver;
	GameOver.setSpritePos(glm::vec2(0.0f, 0.0f));
	GameOver.setTexture(GameOver2.getTexture());
	GameOver.setTextureDimensions(GameOver2.getTWidth(), GameOver2.getTHeight());

	cTexture GameWin2;
	GameWin2.createTexture("Images\\GameWin.png");
	cBkGround GameWin;
	GameWin.setSpritePos(glm::vec2(0.0f, 0.0f));
	GameWin.setTexture(GameWin2.getTexture());
	GameWin.setTextureDimensions(GameWin2.getTWidth(), GameWin2.getTHeight());

	//Creating the Frog sprite
	cTexture FrogTxt;
	FrogTxt.createTexture("Images\\Frog.png");
	cFrog FrogSprite;
	FrogSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	FrogSprite.setSpritePos(glm::vec2(496.0f, 715.0f));
	FrogSprite.setTexture(FrogTxt.getTexture());
	FrogSprite.setTextureDimensions(FrogTxt.getTWidth(), FrogTxt.getTHeight());
	FrogSprite.setSpriteCentre();
	FrogSprite.setFrogVelocity(glm::vec2(0.0f, 0.0f));

	// Attach sound manager to Frog sprite
	FrogSprite.attachSoundMgr(theSoundMgr);

    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Switch to control the scenes
		switch (game_state)
		{ 
		//Main Menu scene
		case MENU:
		{			
			//Rendering the background
			mainMenu.render();
			//Changing game state when Enter is hit
			if (theInputMgr->isKeyDown(VK_RETURN))
			{
				game_state = PLAYING;
			}

			break;
		}
			//Main Game scene
		case PLAYING:
		{

			//Adding to the timer
			timer += elapsedTime;

			spriteBkgd.render();

			FrogSprite.update(elapsedTime);


			vector<cLog*>::iterator logIterator = theLogs.begin();
			while (logIterator != theLogs.end())
			{
				if ((*logIterator)->isActive() == false)
				{
					logIterator = theLogs.erase(logIterator);
				}
				else
				{
					(*logIterator)->update(elapsedTime);
					(*logIterator)->render();
					++logIterator;
				}
			}

			vector<cCar*>::iterator carIterator = theCars.begin();
			while (carIterator != theCars.end())
			{
				if ((*carIterator)->isActive() == false)
				{
					carIterator = theCars.erase(carIterator);
				}
				else
				{
					(*carIterator)->update(elapsedTime);
					(*carIterator)->render();
					++carIterator;
				}
			}

			vector<cCar2*>::iterator car2Iterator = theCars2.begin();
			while (car2Iterator != theCars2.end())
			{
				if ((*car2Iterator)->isActive() == false)
				{
					car2Iterator = theCars2.erase(car2Iterator);
				}
				else
				{
					(*car2Iterator)->update(elapsedTime);
					(*car2Iterator)->render();
					++car2Iterator;
				}
			}

			FrogSprite.render();
			//Converting the name of game and timer to string
			theFontMgr->getFont("Space")->printText((std::string("Frog Life    ") + std::to_string(timer)).c_str(), glm::vec2(10.0f, 50.0f));

			break;

		}
		//Game Over scene
		case GAMEOVER:
		{
			GameOver.render();
			//Changing game state when Enter is hit
			if (theInputMgr->isKeyDown(VK_RETURN))
			{
				game_state = PLAYING;
				FrogSprite.setSpritePos(glm::vec2(496.0f, 715.0f)); //Resetting the Frog position
				timer = 0;

			}

			break;
		}
		// Winning scene
		case WIN:
		{
			GameWin.render();
			theFontMgr->getFont("Space")->printText((std::string("Your score is:    ") + std::to_string(timer)).c_str(), glm::vec2(550.0f, 300.0f));
			//Changing game state when Enter is hit
			if (theInputMgr->isKeyDown(VK_RETURN))
			{
				game_state = PLAYING;
				FrogSprite.setSpritePos(glm::vec2(496.0f, 715.0f)); //Resetting the Frog position
				timer = 0;
			}
			break;
		}
		}

		
		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
