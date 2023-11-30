#include "GameData.h"

namespace Globals
{
	extern RenderWindow window;

	extern const int screenWidth = 1024;
	extern const int screenHeight = 768;
	extern int activeBricks = 0;
	extern int activeAcids = 0;
	extern int droppedAcids = 0;
	extern float acidLastDrop = 0.0f;
	extern float icedStartPoint = 0.0f;
	extern bool acidGame = false;
	extern bool icedGame = false;
}

namespace Colission
{
	extern int pointsQnty{};
	extern float dyP1{};
	extern float dxP1{};
	extern float y{};
	extern float x{};
	extern float hickX{};
	extern float hickY{};
	extern float hypotenuse{};
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

	//Assets
	extern Sprite menuBackground{};

	extern Sprite gameBackground{};
	extern Sprite player{};
	extern Sprite playerEnd{};
	extern Sprite ball{};

	extern Sprite brick1{};
	extern Sprite brick2{};
	extern Sprite brick3{};
	extern Sprite brick4{};
	extern Sprite brick5{};
	extern Sprite acidBrick{};
	extern Sprite iceBrick{};
	extern Sprite bigBrick{};
	extern Sprite stoneBrick[5]{};

	extern int acidPosX{};
	extern int acidPosY{};
	extern int icePosX{};
	extern int icePosY{};
	extern int bigPosX{};
	extern int bigPosY{};
	extern int stonePosX{};
	extern int stonePosY{};

	extern int menuSizeX{};
	extern int menuSizeY{};


	//Fonts
	extern int menuFont{};
};