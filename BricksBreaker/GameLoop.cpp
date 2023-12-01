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
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Left)
		{
			player.speed.x = -500.0f;
		}
		else if (event.key.code == Keyboard::Right)
		{
			player.speed.x = 500.0f;
		}
		else if (event.key.code == Keyboard::Escape)
		{
			//slSoundStopAll();
			currentSceen = GameSceen::MENU;
		}
		else if (event.key.code == Keyboard::RControl && ball.isStoped)
		{
			ballStart.play();
			ball.isStoped = false;
			ball.speed.x = 0.0f;
			ball.speed.y = 700.0f;
		}
		else
		{
			player.speed.x = 0.0f;
		}
	}
}

static void MoveEntities(Player& player, Ball& ball)
{
	Vector2f newPos;
	newPos.x = player.texture.getPosition().x + (player.speed.x * deltaTime.asMilliseconds());
	newPos.y = player.texture.getPosition().y + (player.speed.y * deltaTime.asMilliseconds());


	if (newPos.x < 0.0f)
	{
		newPos.x = 0.0f;
	}
	else if (newPos.x > screenWidth - (player.texture.getGlobalBounds().width))
	{
		newPos.x = screenWidth - (player.texture.getGlobalBounds().width);
	}

	player.texture.setPosition(newPos);

	if (ball.isStoped)
	{
		ball.texture.setPosition(player.texture.getPosition().x, ball.texture.getPosition().y);
	}
	else
	{
		newPos.x = ball.texture.getPosition().x + ball.speed.x * deltaTime.asMilliseconds();
		newPos.y = ball.texture.getPosition().y + ball.speed.y * deltaTime.asMilliseconds();

		ball.texture.setPosition(newPos);
	}
}

static void DrawHUD(Player& player)
{
	char numeroText[32];
	snprintf(numeroText, sizeof(numeroText), "Points: %d", player.points);

	Text line1;
	line1.setString(numeroText);
	line1.setPosition(screenWidth / 2.0f - line1.getGlobalBounds().width / 2.0f, static_cast<double>(150));
	line1.setFont(menuFont);
	line1.setCharacterSize(80);

}

static void Draw(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	window.draw(gameBackground);

	for (int i = 0; i < bricksQnty; i++)
	{
		if (bricks[i].isAlive)
		{
			window.draw(bricks[i].texture);
		}
	}

	for (int i = 0; i < totalAcids; i++)
	{
		if (acidBricks[i].isAlive)
		{
			Color color{ acidBricks[i].red, acidBricks[i].green, acidBricks[i].blue, acidBricks[i].alpha };

			acidBricks[i].texture.setColor(color);

			window.draw(acidBricks[i].texture);
		}	
	}

	window.draw(ball.texture);
	window.draw(player.texture);

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
		int elapsedTimeFromLast = Globals::clock.getElapsedTime().asMilliseconds() - acidLastDrop;

		if (elapsedTimeFromLast > 1000 && droppedAcids < totalAcids)
		{
			acidLastDrop = Globals::clock.getElapsedTime().asMilliseconds();

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
					acidBricks[i].red -= 1;
					acidBricks[i].green += 1;
					acidBricks[i].blue += 1;
					acidBricks[i].alpha -= 1;

					if (acidBricks[i].alpha <= 80)
					{
						acidBricks[i].isAlphaDown = false;
					}
				}
				else
				{
					acidBricks[i].red += 1;
					acidBricks[i].green -= 1;
					acidBricks[i].blue -= 1;
					acidBricks[i].alpha += 1;

					if (acidBricks[i].alpha >= 255)
					{
						acidBricks[i].isAlphaDown = true;
					}
				}

				Vector2f newPos;
				newPos.x = acidBricks[i].texture.getPosition().x;
				newPos.y = acidBricks[i].texture.getPosition().y + acidBricks[i].speed * deltaTime.asMilliseconds();

				acidBricks[i].texture.setPosition(newPos);
			}
		}

		if (droppedAcids == totalAcids)
		{
			if (!StillAcidsAlive(acidBricks))
			{
				acidGame = false;
				//slSoundStopAll();
			}
		}
	}
}

static void UpdateIced()
{
	if (icedGame)
	{
		int elapsedTime = Globals::clock.getElapsedTime().asMilliseconds() - icedStartPoint;

		if (elapsedTime > 10000)
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
			int elapsedTime = Globals::clock.getElapsedTime().asMilliseconds() - bricks[i].lastUpdate;

			if (elapsedTime > 100)
			{
				bricks[i].stoneTexturePos++;

				if (bricks[i].stoneTexturePos > 4)
				{
					bricks[i].stoneTexturePos = 1;
				}

				bricks[i].texture = stoneBrick[bricks[i].stoneTexturePos];

				bricks[i].lastUpdate = Globals::clock.getElapsedTime().asMilliseconds();
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
		ballStart.play();
		player.firstTime = false;
	}

	deltaTime = Globals::clock.restart();

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