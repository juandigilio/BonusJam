#include "GameFunctions.h"

#include <iostream>

#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameData.h"


using namespace Assets;
using namespace Globals;
using namespace std;

static void SetEntities(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	gameBackground.setPosition(0.0f, 0.0f);

	player.texture.setPosition(screenWidth * 0.5f, - player.texture.getGlobalBounds().height / 4.0f);
	player.availableLives = 3;
	player.points = 0;
	player.speed = { 0.0f, 0.0f };
	player.texture = Assets::player;
	player.isAlive = true;

	ball.radius = 8.0f;
	ball.texture.setPosition(static_cast<float>(screenWidth / 2.0f), 35.0f);
	ball.speed = { 0.0f, 300.0f };
	ball.maxSpeed = 700.0f;
	ball.texture = Assets::ball;
	ball.isAlive = true;
	ball.isOut = false;
	ball.isStoped = true;

	Vector2f position = { 90.0f, screenHeight - 50.0f };
	int iterator = 0;
	float brickSizeX = 80;
	float brickSizeY = 23;
	int ran;

	srand(time(NULL));

	activeBricks = 0;
	droppedAcids = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bricks[activeBricks].texture.setPosition(position);
			bricks[activeBricks].isAlive = true;
			bricks[activeBricks].isAcid = false;
			bricks[activeBricks].isIce = false;
			bricks[activeBricks].isBig = false;
			bricks[activeBricks].isStone = false;
			bricks[activeBricks].availableLives = 0;

			position.x += bricks[activeBricks].texture.getGlobalBounds().width + 10.0f;

			ran = (rand() % 5) + 1;

			switch (ran)
			{
			case 1:
			{
				bricks[activeBricks].texture = brick1;
				break;
			}
			case 2:
			{
				bricks[activeBricks].texture = brick2;
				break;
			}
			case 3:
			{
				bricks[activeBricks].texture = brick3;
				break;
			}
			case 4:
			{
				bricks[activeBricks].texture = brick4;
				break;
			}
			case 5:
			{
				bricks[activeBricks].texture = brick5;
				break;
			}
			}

			activeBricks++;
		}

		position.x = 90.0f;
		position.y -= brickSizeY + 10.0f;
	}

	for (int i = 0; i < 3; i++)
	{
		do
		{
			ran = (rand() % bricksQnty);

		} while (bricks[ran].isAcid == true);

		bricks[ran].isAcid = true;
		bricks[ran].texture = acidBrick;
		activeBricks--;
	}

	for (int i = 0; i < 2; i++)
	{
		do
		{
			ran = (rand() % bricksQnty);

		} while (bricks[ran].isAcid == true || bricks[ran].isIce == true);

		bricks[ran].isIce = true;
		bricks[ran].texture = iceBrick;
		activeBricks--;
	}

	for (int i = 0; i < 2; i++)
	{
		do
		{
			ran = (rand() % bricksQnty);

		} while (bricks[ran].isAcid == true || bricks[ran].isIce == true || bricks[ran].isBig == true);

		bricks[ran].isBig = true;
		bricks[ran].texture = bigBrick;
		activeBricks--;
	}

	for (int i = 0; i < 8; i++)
	{
		do
		{
			ran = (rand() % bricksQnty);

		} while (bricks[ran].isAcid == true || bricks[ran].isIce == true || bricks[ran].isBig == true || bricks[ran].isStone == true);

		bricks[ran].isStone = true;
		bricks[ran].availableLives = 2;
		bricks[ran].texture = stoneBrick[0];
		bricks[ran].stoneTexturePos = 0;	
		bricks[ran].lastUpdate = 0;	
		activeBricks--;
	}
	
	for (int i = 0; i < totalAcids; i++)
	{
		acidBricks[i].texture = acidBrick; 
		acidBricks[i].isAlive = false;
		acidBricks[i].speed = 180.0f;
		acidBricks[i].red = 1.0f;
		acidBricks[i].green = 0.0f;
		acidBricks[i].blue = 0.0f;
		acidBricks[i].alpha = 1.0f;
		acidBricks[i].isAlphaDown = true;
	}
}

static void LoadAssets()
{
	Texture texture;

	if (!texture.loadFromFile("../Assets/Images/gameBackground.png"))
	{
		cout << ">>> Game Background texture load failed! <<<" << endl;
	}
	else
	{
		gameBackground.setTexture(texture);
		gameBackground.setScale(1.5f, 1.5f);
	}

	if (!texture.loadFromFile("../Assets/Images/Ship.png"))
	{
		cout << ">>> Player texture load failed! <<<" << endl;
	}
	else
	{
		player.setTexture(texture);
		player.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/ShipEnd.png"))
	{
		cout << ">>> Player end texture load failed! <<<" << endl;
	}
	else
	{
		playerEnd.setTexture(texture);
		playerEnd.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/Enemy.png"))
	{
		cout << ">>> Ball texture load failed! <<<" << endl;
	}
	else
	{
		ball.setTexture(texture);
		ball.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/brick1.png"))
	{
		cout << ">>> brik1 texture load failed! <<<" << endl;
	}
	else
	{
		brick1.setTexture(texture);
		brick1.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/brick2.png"))
	{
		cout << ">>> brik2 texture load failed! <<<" << endl;
	}
	else
	{
		brick2.setTexture(texture);
		brick2.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/brick3.png"))
	{
		cout << ">>> brik3 texture load failed! <<<" << endl;
	}
	else
	{
		brick3.setTexture(texture);
		brick3.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/brick4.png"))
	{
		cout << ">>> brik4 texture load failed! <<<" << endl;
	}
	else
	{
		brick4.setTexture(texture);
		brick4.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/brick5.png"))
	{
		cout << ">>> brik5 texture load failed! <<<" << endl;
	}
	else
	{
		brick5.setTexture(texture);
		brick5.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/acid.png"))
	{
		cout << ">>> acidBrick texture load failed! <<<" << endl;
	}
	else
	{
		acidBrick.setTexture(texture);
		acidBrick.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/ice.png"))
	{
		cout << ">>> iceBrick texture load failed! <<<" << endl;
	}
	else
	{
		iceBrick.setTexture(texture);
		iceBrick.setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/big.png"))
	{
		cout << ">>> bigBrick texture load failed! <<<" << endl;
	}
	else
	{
		bigBrick.setTexture(texture);
		bigBrick.setScale(1.2f, 1.2f);
	}
	
	if (!texture.loadFromFile("../Assets/Images/stone.png"))
	{
		cout << ">>> stoneBrick[0] texture load failed! <<<" << endl;
	}
	else
	{
		stoneBrick[0].setTexture(texture);
		stoneBrick[0].setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/stone1.png"))
	{
		cout << ">>> stoneBrick[1] texture load failed! <<<" << endl;
	}
	else
	{
		stoneBrick[1].setTexture(texture);
		stoneBrick[1].setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/stone2.png"))
	{
		cout << ">>> stoneBrick[2] texture load failed! <<<" << endl;
	}
	else
	{
		stoneBrick[2].setTexture(texture);
		stoneBrick[2].setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/stone3.png"))
	{
		cout << ">>> stoneBrick[3] texture load failed! <<<" << endl;
	}
	else
	{
		stoneBrick[3].setTexture(texture);
		stoneBrick[3].setScale(1.2f, 1.2f);
	}

	if (!texture.loadFromFile("../Assets/Images/stone4.png"))
	{
		cout << ">>> stoneBrick[4] texture load failed! <<<" << endl;
	}
	else
	{
		stoneBrick[4].setTexture(texture);
		stoneBrick[4].setScale(1.2f, 1.2f);
	}

	SoundBuffer buffer;

	if (!buffer.loadFromFile("../Assets/Music/ballBrick.wav")) 
	{
		cout << ">>> ballBrick.wav sound load failed! <<<" << endl;
	}
	else
	{
		ballBrick.setBuffer(buffer);
	}

	if (!buffer.loadFromFile("../Assets/Music/ballStart.wav"))
	{
		cout << ">>> ballStart.wav sound load failed! <<<" << endl;
	}
	else
	{
		ballStart.setBuffer(buffer);
	}

	if (!buffer.loadFromFile("../Assets/Music/ballWall.wav"))
	{
		cout << ">>> ballWall.wav sound load failed! <<<" << endl;
	}
	else
	{
		ballWall.setBuffer(buffer);
	}

	if (!buffer.loadFromFile("../Assets/Music/missBall.wav"))
	{
		cout << ">>> missBall.wav sound load failed! <<<" << endl;
	}
	else
	{
		missBall.setBuffer(buffer);
	}
	
	if (!buffer.loadFromFile("../Assets/Music/iced.wav"))
	{
		cout << ">>> iced.wav sound load failed! <<<" << endl;
	}
	else
	{
		iced.setBuffer(buffer);
	}
	
	if (!buffer.loadFromFile("../Assets/Music/danger.wav"))
	{
		cout << ">>> danger.wav sound load failed! <<<" << endl;
	}
	else
	{
		danger.setBuffer(buffer);
	}

	if (!buffer.loadFromFile("../Assets/Music/bigPlayer.wav"))
	{
		cout << ">>> bigPlayer.wav sound load failed! <<<" << endl;
	}
	else
	{
		bigPlayer.setBuffer(buffer);
	}
}

void InitGame(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	LoadAssets();

	SetEntities(player, ball, bricks, acidBricks);
}