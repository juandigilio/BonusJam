#include "ColissionManager.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	float ballRadius = ball.texture.getGlobalBounds().width / 2.0f;
	float ballX = ball.texture.getPosition().x;
	float ballY = ball.texture.getPosition().y;

	if (ballX + ballRadius * 2.0f > screenWidth)
	{
		ball.speed.x = (ball.speed.x * -1.0f);
		ball.texture.setPosition(screenWidth - ballRadius, ballY);
		ballWall.play();
	}
	else if (ballX - ballRadius < 0.0f)
	{
		ball.speed.x = (ball.speed.x * -1.0f);
		ball.texture.setPosition(ballRadius, ballY);
		ballWall.play();
	}
	else if (ballY < 0.0f)
	{
		ball.speed.y = ball.speed.y * -1.0f;
		ball.texture.setPosition(ballX, 0.0f);
		ballWall.play();
	}
	else if (ballY < 0 && !ball.isOut)
	{
		ball.isOut = true;
		player.availableLives--;
		ballWall.play();

		if (player.availableLives == 0)
		{
			player.isAlive = false;
			//slSoundStopAll();
		}
	}
	else if (ballY > screenHeight + 200)
	{
		if (!ball.isStoped)
		{
			ballStart.play();
		}

		float newY = player.texture.getPosition().y + ballRadius + (player.texture.getGlobalBounds().height / 2.0f) + 10.0f;

		player.texture.setScale(1.0f, 1.0f);
		ball.isOut = false;
		ball.texture.setPosition(player.texture.getPosition().x, newY);
		ball.speed.y *= 0.0f;
		ball.speed.x = 0.0f;
		ball.isStoped = true;
		acidGame = false;
		icedGame = false;

		KillAcids(acidBricks);
		//slSoundStopAll();	
	}
}

static void CheckPlayer(Player& player, Ball& ball, bool& collides)
{
	float playerWidth = player.texture.getGlobalBounds().width;
	float playerHeight = player.texture.getGlobalBounds().height;
	float playerX = player.texture.getPosition().x;
	float playerY = player.texture.getPosition().y;

	float ballRadius = ball.texture.getGlobalBounds().width / 2.0f;
	float ballX = ball.texture.getPosition().x;
	float ballY = ball.texture.getPosition().y;

	pointsQnty = 100;
	dyP1 = 0;
	dxP1 = playerWidth / (float)pointsQnty;


	for (int i = 0; i <= pointsQnty; ++i)
	{
		y = playerY + (playerHeight / 2.0f) + i * dyP1;
		x = playerX - (playerWidth / 2.0f) + i * dxP1;

		hickX = abs(x - ballX);
		hickY = abs(y - ballY);

		hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

		if (hypotenuse <= ballRadius)
		{
			collides = true;

			ballY = (playerY + (playerHeight / 2.0f) + ballRadius) + 10.0f;

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
	float ballRadius = ball.texture.getGlobalBounds().width / 2.0f;
	float ballX = ball.texture.getPosition().x;
	float ballY = ball.texture.getPosition().y;

	float brickWidth = brick.texture.getGlobalBounds().width;
	float brickHeight = brick.texture.getGlobalBounds().height;
	float brickX = brick.texture.getPosition().x;
	float brickY = brick.texture.getPosition().y;

	pointsQnty = 100;
	dyP1 = 0;
	dxP1 = brickWidth / static_cast<float>(pointsQnty);

	for (int i = 0; i <= pointsQnty; ++i)
	{
		y = brickY - (brickHeight / 2) + i * dyP1;
		x = brickX - (brickWidth / 2) + i * dxP1;

		hickX = abs(x - ballX);
		hickY = abs(y - ballY);

		hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

		if (hypotenuse <= ballRadius)
		{
			ball.speed.y *= - 1.0f;

			if (!brick.isStone)
			{
				player.points += 20;
				brick.isAlive = false;
			}
			

			collides = true;
			ballY = brickY - (brickHeight / 2.0f) - ballRadius;


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
			y = brickY + (brickHeight / 2.0f) + i * dyP1;
			x = brickX - (brickWidth / 2.0f) + i * dxP1;

			hickX = abs(x - ballX);
			hickY = abs(y - ballY);

			hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

			if (hypotenuse <= ballRadius)
			{
				ball.speed.y *= -1.0f;
				ball.speed.x *= -1.0f;
				collides = true;
				ballY = brickY + (brickHeight / 2) + ballRadius;

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
		dyP1 = brickHeight / (float)pointsQnty;
		dxP1 = 0;

		for (int i = 0; i <= pointsQnty; ++i)
		{
			y = brickY - (brickHeight / 2.0f) + i * dyP1;
			x = brickX - (brickWidth / 2.0f) + i * dxP1;

			hickX = abs(x - ballX);
			hickY = abs(y - ballY);

			hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

			if (hypotenuse <= ballRadius)
			{
				ball.speed.x *= -1.0f;
				ball.speed.y = abs(ball.speed.y) * -1.0f;
				collides = true;
				ballX = brickX - (brickWidth / 2.0f) - ballRadius;

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
			y = brickY - (brickHeight / 2.0f) + i * dyP1;
			x = brickX + (brickWidth / 2.0f) + i * dxP1;

			hickX = abs(x - ballX);
			hickY = abs(y - ballY);

			hypotenuse = sqrt((hickY * hickY) + (hickX * hickX));

			if (hypotenuse <= ballRadius)
			{
				ball.speed.x *= -1.0f;
				ball.speed.y = abs(ball.speed.y) * -1.0f;
				collides = true;
				ballX = brickX + (brickWidth / 2.0f) + ballRadius;

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
		danger.play();
		droppedAcids = 0;
		acidGame = true;
	}
	else if (brick.isIce)
	{
		iced.play();
		icedStartPoint = Globals::clock.getElapsedTime().asMilliseconds();
		icedGame = true;
	}
	else if (brick.isBig)
	{
		bigPlayer.play();
		player.texture.setScale(1.0f, 1.0f);
	}
	else if (brick.isStone)
	{
		ballWall.play();

		brick.availableLives--;

		if (brick.availableLives == 0)
		{
			brick.isStone = false;

			RandPowerUp(brick);
		}
	}
	else
	{
		ballBrick.play();
	}
}

static void CheckAcids(Player& player, Brick acidBricks[], Ball& ball)
{
	float playerWidth = player.texture.getGlobalBounds().width;
	float playerHeight = player.texture.getGlobalBounds().height;
	float playerX = player.texture.getPosition().x;
	float playerY = player.texture.getPosition().y;

	for (int i = 0; i < totalAcids; i++)
	{
		float brickX = acidBricks[i].texture.getPosition().x;
		float brickY = acidBricks[i].texture.getPosition().y;
		float brickWidth = acidBricks[i].texture.getGlobalBounds().width;
		float brickHeight = acidBricks[i].texture.getGlobalBounds().height;

		if (acidBricks[i].isAlive)
		{
			bool collidesX = false;
			bool collidesY = false;

			Vector2f vertex[4];
			vertex[0] = { playerX - (playerWidth / 2.0f), playerWidth - (playerHeight / 2.0f) };
			vertex[1] = { playerX + (playerWidth / 2.0f), playerWidth - (playerHeight / 2.0f) };
			vertex[2] = { playerX - (playerWidth / 2.0f), playerWidth + (playerHeight / 2.0f) };
			vertex[3] = { playerX + (playerWidth / 2.0f), playerWidth + (playerHeight / 2.0f) };
			
			for (int j = 0; j < 4; j++)
			{
				if (vertex[j].x > (brickX - brickWidth / 2.0f) && vertex[j].x < (brickX + brickWidth / 2.0f))
				{
					collidesX = true;
				}

				if (vertex[j].y > (brickY - brickHeight / 2.0f) && vertex[j].y < (brickY + brickHeight / 2.0f))
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
				//slSoundStopAll();
				missBall.play();

				if (player.availableLives == 0)
				{
					player.isAlive = false;
				}
				else
				{
					float ballRadius = ball.texture.getGlobalBounds().width / 2.0f;

					player.texture.setScale(1.0f, 1.0f);
					ball.texture.setPosition(playerX, playerY + ballRadius + (playerHeight / 2.0f));
					ball.speed.y *= 0.0f;
					ball.speed.x = 0.0f;
					ball.isStoped = true;
					acidGame = false;
					icedGame = false;

					KillAcids(acidBricks);

					//slSoundStopAll();
					ballStart.play();
				}

				break;
			}
			else if (brickY < -10.0f)
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
