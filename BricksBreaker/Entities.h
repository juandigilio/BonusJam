#pragma once

#include "GameData.h"

#include <SFML/Graphics.hpp>

struct Player
{
	Sprite texture;
	Vector2f speed;
	int availableLives;
	int points;
	int ammo;
	bool isAlive;
	bool firstTime = true;
};

struct Ball
{
	Sprite texture;
	Vector2f speed;
	float maxSpeed;
	bool isAlive;
	bool isOut;
	bool isStoped;
};

struct Brick
{
	Sprite texture;
	int availableLives;
	int stoneTexturePos;
	float lastUpdate;
	float speed;
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;
	bool isAlphaDown;
	bool isAlive;
	bool isAcid;
	bool isIce;
	bool isBig;
	bool isStone;
};