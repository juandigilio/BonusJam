#include "MenuManager.h"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameData.h"
#include "Entities.h"
#include "GameLoop.h"

using namespace std;
using namespace sf;
using namespace Assets;
using namespace Globals;

void InitMenu()
{
	Texture texture;

	if (!texture.loadFromFile("../Assets/Images/menuBackground.png"))
	{
		cout << ">>> MenuBackground texture load failed! <<<" << endl;
	}
	else
	{
		menuBackground.setTexture(texture);
	}

	if (!texture.loadFromFile("../Assets/Images/acid.png"))
	{
		cout << ">>> Acid texture load failed! <<<" << endl;
	}
	else
	{
		acidBrick.setTexture(texture);
	}

	if (!texture.loadFromFile("../Assets/Images/ice.png"))
	{
		cout << ">>> Ice texture load failed! <<<" << endl;
	}
	else
	{
		iceBrick.setTexture(texture);
	}

	if (!texture.loadFromFile("../Assets/Images/big.png"))
	{
		cout << ">>> Big texture load failed! <<<" << endl;
	}
	else
	{
		bigBrick.setTexture(texture);
	}

	if (!texture.loadFromFile("../Assets/Images/stone.png"))
	{
		cout << ">>> Stone texture load failed! <<<" << endl;
	}
	else
	{
		stoneBrick[0].setTexture(texture);
	}

	menuFont = slLoadFont("../Assets/Fonts/DelaGothic.ttf");

	slSetTextAlign(SL_ALIGN_CENTER);

	acidPosX = screenWidth / 2;
	acidPosY = ((screenHeight / 5) * 4);
	icePosX = screenWidth / 2;
	icePosY = ((screenHeight / 5) * 3);
	bigPosX = screenWidth / 2;
	bigPosY = ((screenHeight / 5) * 2);
	stonePosX = (screenWidth / 2);
	stonePosY = (screenHeight / 5);

	menuSizeX = 200;
	menuSizeY = 80;
}

void Draw()
{
	(menuBackground, screenWidth / 2, screenHeight / 2, screenWidth * 1.2, screenHeight);
	slSprite(acidBrick, acidPosX, acidPosY, menuSizeX, menuSizeY);
	slSprite(iceBrick, icePosX, icePosY, menuSizeX, menuSizeY);
	slSprite(bigBrick, bigPosX, bigPosY, menuSizeX, menuSizeY);
	slSprite(stoneBrick[0], stonePosX, stonePosY, menuSizeX, menuSizeY);

	slSetForeColor(0.471f, 0.471f, 0.471f, 1.0f);

	slSetFont(menuFont, 45);
	slText(acidPosX, acidPosY - 6, "Play");

	slSetFont(menuFont, 40);
	slText(stonePosX - 3, stonePosY - 22, "Exit");

	slSetFont(menuFont, 30);
	slText(bigPosX, bigPosY - 9, "Credits");

	slSetFont(menuFont, 25);
	slText(icePosX, icePosY - 6, "Istructions");

	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GetInput(GameSceen& currentSceen)
{
	slSetForeColor(1.0f, 0.47f, 0.0f, 1.0f);

	if ((slGetMouseX() > acidPosX - menuSizeX / 2 && slGetMouseX() < acidPosX + menuSizeX / 2) &&
		(slGetMouseY() > acidPosY - menuSizeY / 2 && slGetMouseY() < acidPosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 45);
		slText(acidPosX, acidPosY - 6, "Play");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::GAME;
		}
	}
	else if ((slGetMouseX() > stonePosX - menuSizeX / 2 && slGetMouseX() < stonePosX + menuSizeX / 2) &&
		(slGetMouseY() > stonePosY - menuSizeY / 2 && slGetMouseY() < stonePosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 40);
		slText(stonePosX - 3, stonePosY - 22, "Exit");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::EXIT;
		}
	}
	else if ((slGetMouseX() > bigPosX - menuSizeX / 2 && slGetMouseX() < bigPosX + menuSizeX / 2) &&
		(slGetMouseY() > bigPosY - menuSizeY / 2 && slGetMouseY() < bigPosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 30);
		slText(bigPosX, bigPosY - 9, "Credits");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::CREDITS;
		}
	}
	else if ((slGetMouseX() > icePosX - menuSizeX / 2 && slGetMouseX() < icePosX + menuSizeX / 2) &&
		(slGetMouseY() > icePosY - menuSizeY / 2 && slGetMouseY() < icePosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 25);
		slText(icePosX, icePosY - 6, "Istructions");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::INSTRUCTIONS;
		}
	}


	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ShowMenu(GameSceen& currentSceen)
{
	Draw();

	GetInput(currentSceen);
}

void ShowInstructions(GameSceen& currentSceen)
{
	slSetForeColor(1.0f, 1.0f, 1.0f, 0.5f);
	slSprite(menuBackground, screenWidth / 2, screenHeight / 2, screenWidth * 1.2, screenHeight);

	slSetForeColor(0.671f, 0.671f, 0.671f, 1.0f);

	slSetFont(menuFont, 25);

	slText(screenWidth / 2, static_cast<double>(600), "Use arrows to move");
	slText(screenWidth / 2, static_cast<double>(500), "Use left CTRL to start the ball when stoped");
	slText(screenWidth / 2, static_cast<double>(400), "If an acid brick hits you, you die,");
	slText(screenWidth / 2, static_cast<double>(360), "but if you dodge it you earn 200pts for each one");
	slText(screenWidth / 2, static_cast<double>(150), "Press ESC to go back to the menu");

	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (slGetKey(SL_KEY_ESCAPE))
	{
		currentSceen = GameSceen::MENU;
	}
}

void ShowCredits(GameSceen& currentSceen)
{
	string credits = "Created by";
	string credits2 = "Juan Ignacio Digilio";
	string credits3 = "Image Campus student (Sigil evaluation)";
	string credits4 = "1st year of video games development";
	string itchio = "https://juandigilio.itch.io/";
	string gitHub = "https://github.com/juandigilio";
	double itchioPosX = static_cast<double>((screenWidth / 2) - (itchio.length() / 2));
	double itchioPosY = static_cast<double>((screenHeight / 2) - 50);
	double gitPosX = static_cast<double>((screenWidth / 2) - (gitHub.length() / 2));
	double gitPosY = static_cast<double>((screenHeight / 2) - 70);;

	slSetForeColor(1.0f, 1.0f, 1.0f, 0.5f);

	slSprite(menuBackground, screenWidth / 2, screenHeight / 2, screenWidth * 1.2, screenHeight);

	slSetForeColor(0.471f, 0.471f, 0.471f, 1.0f);

	slSetFont(menuFont, 35);
	slText(static_cast<double>((screenWidth / 2) - (credits.length() / 2)), static_cast<double>((screenHeight / 2) + 50), "Created by");
	slSetFont(menuFont, 55);
	slText(static_cast<double>((screenWidth / 2) - (credits2.length() / 2)), static_cast<double>(screenHeight / 2), "Juan Ignacio Digilio");

	slSetFont(menuFont, 14);
	slText(static_cast<double>((screenWidth / 2) - (credits3.length() / 2)), static_cast<double>(50), "Image Campus student (Sigil evaluation)");
	slText(static_cast<double>((screenWidth / 2) - (credits4.length() / 2)), static_cast<double>(20), "1st year of video games development");

	slText(itchioPosX, itchioPosY, "https://juandigilio.itch.io/");
	slText(gitPosX, gitPosY, "https://github.com/juandigilio");

	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);



	if (slGetKey(SL_KEY_ESCAPE))
	{
		currentSceen = GameSceen::MENU;
	}
	else if ((slGetMouseX() > itchioPosX - 110 && slGetMouseX() < itchioPosX + 110) &&
		(slGetMouseY() > itchioPosY && slGetMouseY() < itchioPosY + 14))
	{
		slSetForeColor(1.0f, 0.47f, 0.0f, 1.0f);
		slText(itchioPosX, itchioPosY, "https://juandigilio.itch.io/");
		slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			const char* url = "https://juandigilio.itch.io/";
			char command[256];
			snprintf(command, sizeof(command), "start %s", url);
			system(command);
		}

	}
	else if ((slGetMouseX() > gitPosX - 130 && slGetMouseX() < gitPosX + 130) &&
		(slGetMouseY() > gitPosY && slGetMouseY() < gitPosY + 14))
	{
		slSetForeColor(1.0f, 0.47f, 0.0f, 1.0f);
		slText(gitPosX, gitPosY, "https://github.com/juandigilio");
		slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			const char* url = "https://github.com/juandigilio";
			char command[256];
			snprintf(command, sizeof(command), "start %s", url);
			system(command);
		}

	}
}

void RunGame()
{
	GameSceen currentSceen = GameSceen::MENU;
	Player player{};
	Brick bricks[bricksQnty];
	Brick acidBricks[totalAcids];
	Ball ball{};
	Event event;

	window.create(VideoMode(200, 200), "Banana breaker");

	InitMenu();

	while (window.isOpen())
	{
		window.clear();

		switch (currentSceen)
		{
		case GameSceen::MENU:
		{
			ShowMenu(currentSceen);
			break;
		}
		case GameSceen::GAME:
		{
			Play(player, ball, bricks, acidBricks, currentSceen);
			break;
		}
		case GameSceen::INSTRUCTIONS:
		{
			ShowInstructions(currentSceen);
			break;
		}
		case GameSceen::CREDITS:
		{
			ShowCredits(currentSceen);
			break;
		}
		case GameSceen::EXIT:
		{
			event.type = Event::Closed;
			break;
		}
		}

		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}