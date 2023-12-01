#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;

const int bricksQnty = 80;
const int totalAcids = 10;


struct Vector2
{
	float x;
	float y;
};

enum class GameSceen
{
	MENU,
	GAME,
	INSTRUCTIONS,
	CREDITS,
	EXIT,
};

namespace Globals
{
	extern RenderWindow window;

	extern Event event;

	extern Clock clock;
	extern Time deltaTime;

	extern const int screenWidth;
	extern const int screenHeight;
	extern int activeBricks;
	extern int activeAcids;
	extern int droppedAcids;
	extern float acidLastDrop;
	extern float icedStartPoint;
	extern bool acidGame;
	extern bool icedGame;
}

namespace Colission
{
	extern int pointsQnty;
	extern float dyP1;
	extern float dxP1;
	extern float y;
	extern float x;
	extern float hickX;
	extern float hickY;
	extern float hypotenuse;
};

namespace Assets
{
	//sounds
	extern Sound ballBrick;
	extern Sound ballStart;
	extern Sound ballWall;
	extern Sound missBall;
	extern Sound iced;
	extern Sound danger;
	extern Sound bigPlayer;

	//textures
	extern Sprite menuBackground;

	extern Sprite gameBackground;
	extern Sprite player;
	extern Sprite playerEnd;
	extern Sprite ball;

	extern Sprite brick1;
	extern Sprite brick2;
	extern Sprite brick3;
	extern Sprite brick4;
	extern Sprite brick5;
	extern Sprite acidBrick;
	extern Sprite iceBrick;
	extern Sprite bigBrick;
	extern Sprite stoneBrick[5];

	extern Text playText;
	extern Text exitText;
	extern Text creditsText;
	extern Text instructionsText;

	extern int menuSizeX;
	extern int menuSizeY;

	//Fonts
	extern Font menuFont;
};

