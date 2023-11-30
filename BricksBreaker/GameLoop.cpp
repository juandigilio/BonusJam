#include "Entities.h"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameFunctions.h"
#include "ColissionManager.h"

using namespace std;
using namespace Assets;
using namespace Globals;


static void GetInput(Player& player, Ball& ball, Brick bricks[], GameSceen& currentSceen)
{
	if (slGetKey(SL_KEY_LEFT))
	{
		player.speed.x = -500.0f;
	}
	else if (slGetKey(SL_KEY_RIGHT))
	{
		player.speed.x = 500.0f;
	}
	else if (slGetKey(SL_KEY_ESCAPE))
	{
		slSoundStopAll();
		currentSceen = GameSceen::MENU;
	}
	else if (slGetKey(SL_KEY_RIGHT_CONTROL) &&  ball.isStoped)
	{
		slSoundPlay(ballStart);
		ball.isStoped = false;
		ball.speed.x = 0.0f;
		ball.speed.y = 700.0f;
	}
	else
	{
		player.speed.x = 0.0f;
	}
}

static void MoveEntities(Player& player, Ball& ball)
{
	player.position.x += player.speed.x * slGetDeltaTime();
	player.position.y += player.speed.y * slGetDeltaTime();

	if (player.position.x < 0.0f + (player.size.x / 2.0f))
	{
		player.position.x = 0.0f + (player.size.x / 2.0f);
	}
	else if (player.position.x > screenWidth - (player.size.x / 2.0f))
	{
		player.position.x = screenWidth - (player.size.x / 2.0f);
	}

	if (ball.isStoped)
	{
		ball.position.x = player.position.x;
	}
	else
	{
		ball.position.x += ball.speed.x * static_cast<float>(slGetDeltaTime());
		ball.position.y += ball.speed.y * static_cast<float>(slGetDeltaTime());
	}
}

static void DrawHUD(Player& player)
{
	slSetFont(menuFont, 20);

	char numeroText[32];
	snprintf(numeroText, sizeof(numeroText), "Points: %d", player.points);
	slText(80, 10, numeroText);

}

static void Draw(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	slSprite(gameBackground, static_cast<double>(screenWidth / 2), static_cast<double>(screenHeight / 2), static_cast<double>(screenWidth * 1.8f), static_cast<double>(screenHeight * 1.5f));

	for (int i = 0; i < bricksQnty; i++)
	{
		if (bricks[i].isAlive)
		{
			slSprite(bricks[i].texture, bricks[i].position.x, bricks[i].position.y, bricks[i].textureSize.x, bricks[i].textureSize.y);
		}
	}

	for (int i = 0; i < totalAcids; i++)
	{
		if (acidBricks[i].isAlive)
		{
			slSetForeColor(acidBricks[i].red, acidBricks[i].green, acidBricks[i].blue, acidBricks[i].alpha);

			slSprite(acidBricks[i].texture, acidBricks[i].position.x, acidBricks[i].position.y, acidBricks[i].size.x, acidBricks[i].size.y);

			slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);
		}	
	}

	slSprite(ball.texture, ball.position.x, ball.position.y, ball.textureSize.x, ball.textureSize.y);
	slSprite(player.texture, player.position.x, player.position.y, player.textureSize.x, player.textureSize.y);
	slSprite(player.texture, player.position.x, player.position.y, player.textureSize.x, player.textureSize.y);

	DrawHUD(player);
}

static bool StillAcidsAlive(Brick acidBricks[])
{
	for (int i = 0; i < totalAcids; i++)
	{
		if (acidBricks[i].isAlive)
		{
			return true;
		}
	}

	return false;
}

static void UpdateAcid(Player& player, Brick bricks[], Brick acidBricks[])
{
	if (acidGame)
	{
		int elapsedTimeFromLast = slGetTime() - acidLastDrop;

		if (elapsedTimeFromLast > 1 && droppedAcids < totalAcids)
		{
			acidLastDrop = slGetTime();

			int random = rand() % bricksQnty;

			acidBricks[droppedAcids].isAlive = true;
			acidBricks[droppedAcids].position = bricks[random].position;

			droppedAcids++;
		}

		for (int i = 0; i < totalAcids; i++)
		{
			if (acidBricks[i].isAlive)
			{
				if (acidBricks[i].isAlphaDown)
				{
					acidBricks[i].red -= 0.05f;
					acidBricks[i].green += 0.05f;
					acidBricks[i].blue += 0.05f;
					acidBricks[i].alpha -= 0.05f;

					if (acidBricks[i].alpha <= 0.4f)
					{
						acidBricks[i].isAlphaDown = false;
					}
				}
				else
				{
					acidBricks[i].red += 0.05f;
					acidBricks[i].green -= 0.05f;
					acidBricks[i].blue -= 0.05f;
					acidBricks[i].alpha += 0.05f;

					if (acidBricks[i].alpha >= 1.0f)
					{
						acidBricks[i].isAlphaDown = true;
					}
				}

				acidBricks[i].position.y -= acidBricks[i].speed * slGetDeltaTime();
			}
		}

		if (droppedAcids == totalAcids)
		{
			if (!StillAcidsAlive(acidBricks))
			{
				acidGame = false;
				slSoundStopAll();
			}
		}
	}
}

static void UpdateIced()
{
	if (icedGame)
	{
		float elapsedTime = static_cast<float>(slGetTime()) - icedStartPoint;

		if (elapsedTime > 15.0f)
		{
			icedGame = false;
		}
	}
}

static void UpadteStoned(Brick bricks[])
{
	for (int i = 0; i < bricksQnty; i++)
	{
		if (bricks[i].isStone && bricks[i].availableLives == 1)
		{
			float elapsedTime = slGetTime() - bricks[i].lastUpdate;

			if (elapsedTime > 0.2f)
			{
				bricks[i].stoneTexturePos++;

				if (bricks[i].stoneTexturePos > 4)
				{
					bricks[i].stoneTexturePos = 1;
				}

				bricks[i].texture = stoneBrick[bricks[i].stoneTexturePos];

				bricks[i].lastUpdate = slGetTime();
			}
		}
	}

}

static void UpdatePowerUps(Player& player, Brick bricks[], Brick acidBricks[])
{
	UpdateAcid(player, bricks, acidBricks);
	
	UpdateIced();

	UpadteStoned(bricks);
}

static void Update(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	if (player.firstTime)
	{
		slSoundPlay(ballStart);
		player.firstTime = false;
	}

	UpdatePowerUps(player, bricks, acidBricks);

	CheckColissions(player, ball, bricks, acidBricks);

	MoveEntities(player, ball);
}

static void GameLoop(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[], GameSceen& currentSceen)
{	
	if (!player.isAlive)
	{
		InitGame(player, ball, bricks, acidBricks);
		currentSceen = GameSceen::MENU;
	}

	GetInput(player, ball, bricks, currentSceen);

	Update(player, ball, bricks, acidBricks);

	Draw(player, ball, bricks, acidBricks);
}

void Play(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[], GameSceen& currentSceen)
{
	if (player.firstTime)
	{
		InitGame(player, ball, bricks, acidBricks);
	}

	GameLoop(player, ball, bricks, acidBricks, currentSceen);
}