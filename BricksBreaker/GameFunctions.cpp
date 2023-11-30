#include "GameFunctions.h"

#include <iostream>

#include"sl.h"

#include "GameData.h"


using namespace Assets;
using namespace Globals;

static void SetEntities(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	player.size = { 100.0f, 100.0f };
	player.textureSize = { player.size.x , player.size.y };
	player.position = { screenWidth * 0.5f, -player.size.y / 4.0f };
	player.availableLives = 3;
	player.points = 0;
	player.speed = { 0.0f, 0.0f };
	player.texture = Assets::player;
	player.isAlive = true;


	ball.radius = 8.0f;
	ball.textureSize.x = ball.radius * 2;
	ball.textureSize.y = ball.radius * 2;
	ball.position = { static_cast<float>(screenWidth / 2.0f), 35.0f };
	ball.speed = { 0.0f, 300.0f };
	ball.maxSpeed = 700.0f;
	ball.texture = Assets::ball;
	ball.isAlive = true;
	ball.isOut = false;
	ball.isStoped = true;

	
	Vector2 position = { 90.0f, screenHeight - 50.0f };
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
			bricks[activeBricks].size.x = brickSizeX;
			bricks[activeBricks].size.y = brickSizeY;
			bricks[activeBricks].textureSize.x = brickSizeX;
			bricks[activeBricks].textureSize.y = brickSizeY;
			bricks[activeBricks].position = position;
			bricks[activeBricks].isAlive = true;
			bricks[activeBricks].isAcid = false;
			bricks[activeBricks].isIce = false;
			bricks[activeBricks].isBig = false;
			bricks[activeBricks].isStone = false;
			bricks[activeBricks].availableLives = 0;

			position.x += bricks[activeBricks].size.x + 10.0f;

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
		acidBricks[i].size.x = brickSizeX;
		acidBricks[i].size.y = brickSizeY;
		acidBricks[i].textureSize.x = brickSizeX;
		acidBricks[i].textureSize.y = brickSizeY;
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
	ballBrick = slLoadWAV("../Assets/Music/ballBrick.wav");
	ballStart = slLoadWAV("../Assets/Music/ballStart.wav");
	ballWall = slLoadWAV("../Assets/Music/ballWall.wav");
	missBall = slLoadWAV("../Assets/Music/missBall.wav");
	iced = slLoadWAV("../Assets/Music/iced.wav");
	danger = slLoadWAV("../Assets/Music/danger.wav");
	bigPlayer = slLoadWAV("../Assets/Music/bigPlayer.wav");
	
	
	gameBackground = slLoadTexture("../Assets/Images/gameBackground.png");
	player = slLoadTexture("../Assets/Images/Ship.png");
	playerEnd = slLoadTexture("../Assets/Images/ShipEnd.png");
	ball = slLoadTexture("../Assets/Images/Enemy.png");

	brick1 = slLoadTexture("../Assets/Images/brick1.png");
	brick2 = slLoadTexture("../Assets/Images/brick2.png");
	brick3 = slLoadTexture("../Assets/Images/brick3.png");
	brick4 = slLoadTexture("../Assets/Images/brick4.png");
	brick5 = slLoadTexture("../Assets/Images/brick5.png");
	acidBrick = slLoadTexture("../Assets/Images/acid.png");
	iceBrick = slLoadTexture("../Assets/Images/ice.png");
	bigBrick = slLoadTexture("../Assets/Images/big.png");
	stoneBrick[0] = slLoadTexture("../Assets/Images/stone.png");
	stoneBrick[1] = slLoadTexture("../Assets/Images/stone1.png");
	stoneBrick[2] = slLoadTexture("../Assets/Images/stone2.png");
	stoneBrick[3] = slLoadTexture("../Assets/Images/stone3.png");
	stoneBrick[4] = slLoadTexture("../Assets/Images/stone4.png");
}

void InitGame(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	LoadAssets();

	SetEntities(player, ball, bricks, acidBricks);
}