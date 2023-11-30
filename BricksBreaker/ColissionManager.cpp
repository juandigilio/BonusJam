#include "ColissionManager.h"

#include <iostream>

#include "sl.h"
#include "GameData.h"


using namespace Colission;
using namespace Assets;
using namespace Globals;

static void KillAcids(Brick acidBricks[])
{
	for (int i = 0; i < totalAcids; i++)
	{
		acidBricks[i].isAlive = false;
	}
}

static void RandPowerUp(Brick& brick)
{
	switch (rand() % 3)
	{
		case 0:
		{
			brick.isAcid = true;
			brick.texture = acidBrick;
			break;
		}
		case 1:
		{
			brick.isIce = true;
			brick.texture = iceBrick;
			break;
		}
		case 2:
		{
			brick.isBig = true;
			brick.texture = bigBrick;
			break;
		}
	}
}

static void CheckWalls(Player& player, Ball& ball, Brick acidBricks[])
{
	if (ball.position.x + ball.radius > screenWidth)
	{
		ball.speed.x = (ball.speed.x * -1.0f);
		ball.position.x = (screenWidth - ball.radius);
		slSoundPlay(ballWall);
	}
	else if (ball.position.x - ball.radius < 0.0f)
	{
		ball.speed.x = (ball.speed.x * -1.0f);
		ball.position.x = ball.radius;
		slSoundPlay(ballWall);
	}
	else if (ball.position.y + ball.radius > screenHeight)
	{
		ball.speed.y = ball.speed.y * -1.0f;
		ball.position.y = screenHeight - ball.radius;
		slSoundPlay(ballWall);
	}
	else if (ball.position.y < 0 && !ball.isOut)
	{
		ball.isOut = true;
		player.availableLives--;
		slSoundPlay(missBall);

		if (player.availableLives == 0)
		{
			player.isAlive = false;
			slSoundStopAll();
		}
	}
	else if (ball.position.y < -200)
	{
		if (!ball.isStoped)
		{
			slSoundPlay(ballStart);
		}

		player.textureSize.x = player.size.x;
		ball.isOut = false;
		ball.position.x = player.position.x;
		ball.position.y = player.position.y + ball.radius + (player.size.y / 2) + 10;
		ball.speed.y *= 0.0f;
		ball.speed.x = 0.0f;
		ball.isStoped = true;
		acidGame = false;
		icedGame = false;

		KillAcids(acidBricks);
		slSoundStopAll();	
	}
}

static void CheckPlayer(Player& player, Ball& ball, bool& collides)
{
	pointsQnty = 100;
	dyP1 = 0;
	dxP1 = player.textureSize.x / (float)pointsQnty;


	for (int i = 0; i <= pointsQnty; ++i)
	{
		y = player.position.y + (player.textureSize.y / 2) + i * dyP1;
		x = player.position.x - (player.textureSize.x / 2) + i * dxP1;

		hickX = abs(x - ball.position.x);
		hickY = abs(y - ball.position.y);

		hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

		if (hypotenuse <= ball.radius)
		{
			collides = true;

			ball.position.y = (player.position.y + (player.textureSize.y / 2) + ball.radius) + 10;

			if (icedGame)
			{
				ball.isStoped = true;
				ball.speed.x = 0.0f;
				ball.speed.y = 0.0f;
			}
			else
			{
				if (i < 50)
				{
					i = 50 - i;
					ball.speed.x = -1.0f;
				}
				else
				{
					i -= 50;
					ball.speed.x = 1.0f;
				}

				if (i < 10)
				{
					i = 10;
				}
				else if (i > 40)
				{
					i = 40;
				}

				ball.speed.x = ((ball.maxSpeed / 50) * i) * ball.speed.x;
				ball.speed.y = ball.maxSpeed - (ball.maxSpeed / 50) * i;
			}
			
			break;
		}		
	}
}

static void CheckBricks(Player& player, Ball& ball, Brick& brick, bool& collides)
{
	pointsQnty = 100;
	dyP1 = 0;
	dxP1 = brick.size.x / (float)pointsQnty;

	for (int i = 0; i <= pointsQnty; ++i)
	{
		y = brick.position.y - (brick.size.y / 2) + i * dyP1;
		x = brick.position.x - (brick.size.x / 2) + i * dxP1;

		hickX = abs(x - ball.position.x);
		hickY = abs(y - ball.position.y);

		hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

		if (hypotenuse <= ball.radius)
		{
			ball.speed.y *= - 1.0f;

			if (!brick.isStone)
			{
				player.points += 20;
				brick.isAlive = false;
			}
			

			collides = true;
			ball.position.y = brick.position.y - (brick.size.y / 2) - ball.radius;


			if (i < 10)
			{
				if (ball.speed.x > 0.0f)
				{
					ball.speed.x *= -1.0f;
				}

				if (ball.speed.y > 0)
				{
					ball.speed.y *= -1.0f;
				}
			}
			else if (i > 90)
			{
				if (ball.speed.x < 0)
				{
					ball.speed.x *= -1.0f;

				}

				if (ball.speed.y > 0)
				{
					ball.speed.y *= -1.0f;
				}
			}

			break;
		}
	}

	if (!collides)
	{
		for (int i = 0; i <= pointsQnty; ++i)
		{
			y = brick.position.y + (brick.size.y / 2) + i * dyP1;
			x = brick.position.x - (brick.size.x / 2) + i * dxP1;

			hickX = abs(x - ball.position.x);
			hickY = abs(y - ball.position.y);

			hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

			if (hypotenuse <= ball.radius)
			{
				ball.speed.y *= -1.0f;
				ball.speed.x *= -1.0f;
				collides = true;
				ball.position.y = brick.position.y + (brick.size.y / 2) + ball.radius;

				if (!brick.isStone)
				{
					player.points += 20;
					brick.isAlive = false;
				}
				

				if (i < 10)
				{
					if (ball.speed.x > 0.0f)
					{
						ball.speed.x *= -1.0f;
					}

					if (ball.speed.y > 0)
					{
						ball.speed.y *= -1.0f;
					}
				}
				else if (i > 90)
				{
					if (ball.speed.x < 0)
					{
						ball.speed.x *= -1.0f;

					}

					if (ball.speed.y > 0)
					{
						ball.speed.y *= -1.0f;
					}
				}

				break;
			}
		}
	}

	if (!collides)
	{
		dyP1 = brick.size.y / (float)pointsQnty;
		dxP1 = 0;

		for (int i = 0; i <= pointsQnty; ++i)
		{
			y = brick.position.y - (brick.size.y / 2) + i * dyP1;
			x = brick.position.x - (brick.size.x / 2) + i * dxP1;

			hickX = abs(x - ball.position.x);
			hickY = abs(y - ball.position.y);

			hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

			if (hypotenuse <= ball.radius)
			{
				ball.speed.x *= -1.0f;
				ball.speed.y = abs(ball.speed.y) * -1.0f;
				collides = true;
				ball.position.x = brick.position.x - (brick.size.x / 2) - ball.radius;

				if (!brick.isStone)
				{
					player.points += 20;
					brick.isAlive = false;
				}

				if (ball.speed.y > 0.0f)
				{

				}
				break;
			}
		}
	}

	if (!collides)
	{
		for (int i = 0; i <= pointsQnty; ++i)
		{
			y = brick.position.y - (brick.size.y / 2) + i * dyP1;
			x = brick.position.x + (brick.size.x / 2) + i * dxP1;

			hickX = abs(x - ball.position.x);
			hickY = abs(y - ball.position.y);

			hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

			if (hypotenuse <= ball.radius)
			{
				ball.speed.x *= -1.0f;
				ball.speed.y = abs(ball.speed.y) * -1.0f;
				collides = true;
				ball.position.x = brick.position.x + (brick.size.x / 2) + ball.radius;

				if (!brick.isStone)
				{
					player.points += 20;
					brick.isAlive = false;
				}
				

				break;
			}
		}
	}
}

static void CheckPowerUps(Player& player, Brick& brick)
{
	if (brick.isAcid)
	{
		slSoundLoop(danger);
		droppedAcids = 0;
		acidGame = true;
	}
	else if (brick.isIce)
	{
		slSoundPlay(iced);
		icedStartPoint = slGetTime();
		icedGame = true;
	}
	else if (brick.isBig)
	{
		slSoundPlay(bigPlayer);
		player.textureSize.x = player.size.x * 2;
	}
	else if (brick.isStone)
	{
		slSoundPlay(ballWall);

		brick.availableLives--;

		if (brick.availableLives == 0)
		{
			brick.isStone = false;

			RandPowerUp(brick);
		}
	}
	else
	{
		slSoundPlay(ballBrick);
	}
}

static void CheckAcids(Player& player, Brick acidBricks[], Ball& ball)
{
	for (int i = 0; i < totalAcids; i++)
	{
		if (acidBricks[i].isAlive)
		{
			bool collidesX = false;
			bool collidesY = false;

			Vector2 vertex[4];
			vertex[0] = { player.position.x - (player.textureSize.x / 2), player.position.y - (player.textureSize.y / 2) };
			vertex[1] = { player.position.x + (player.textureSize.x / 2), player.position.y - (player.textureSize.y / 2) };
			vertex[2] = { player.position.x - (player.textureSize.x / 2), player.position.y + (player.textureSize.y / 2) };
			vertex[3] = { player.position.x + (player.textureSize.x / 2), player.position.y + (player.textureSize.y / 2) };
			
			for (int j = 0; j < 4; j++)
			{
				if (vertex[j].x > (acidBricks[i].position.x - acidBricks[i].textureSize.x / 2) && vertex[j].x < (acidBricks[i].position.x + acidBricks[i].textureSize.x / 2))
				{
					collidesX = true;
				}

				if (vertex[j].y > (acidBricks[i].position.y - acidBricks[i].textureSize.y / 2) && vertex[j].y < (acidBricks[i].position.y + acidBricks[i].textureSize.y / 2))
				{
					collidesY = true;
				}

				if (collidesX && collidesY)
				{
					break;
				}
			}

			if (collidesX && collidesY)
			{
				player.availableLives--;
				slSoundStopAll();
				slSoundPlay(missBall);

				if (player.availableLives == 0)
				{
					player.isAlive = false;
				}
				else
				{
					player.textureSize.x = player.size.x;
					ball.position.x = player.position.x;
					ball.position.y = player.position.y + ball.radius + (player.size.y / 2);
					ball.speed.y *= 0.0f;
					ball.speed.x = 0.0f;
					ball.isStoped = true;
					acidGame = false;
					icedGame = false;

					KillAcids(acidBricks);

					slSoundStopAll();
					slSoundPlay(ballStart);
				}

				break;
			}
			else if (acidBricks[i].position.y < -10.0f)
			{
				player.points += 200;
				acidBricks[i].isAlive = false;
			}
		}
		
	}
}

void CheckColissions(Player& player, Ball& ball, Brick bricks[], Brick acidBricks[])
{
	bool collides = false;

	CheckWalls(player, ball, acidBricks);

	CheckPlayer(player, ball, collides);

	for (int i = 0; i < bricksQnty; i++)
	{
		if (bricks[i].isAlive)
		{
			CheckBricks(player, ball, bricks[i], collides);

			if (collides)
			{
				CheckPowerUps(player, bricks[i]);
				break;
			}
		}
	}

	CheckAcids(player, acidBricks, ball);
}
