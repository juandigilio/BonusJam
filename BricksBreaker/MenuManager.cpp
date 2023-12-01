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

static void InitMenu()
{
	Texture texture;

	if (!texture.loadFromFile("../Assets/Images/menuBackground.png"))
	{
		cout << ">>> MenuBackground texture load failed! <<<" << endl;
	}
	else
	{
		menuBackground.setTexture(texture);
		menuBackground.setScale(1.2f, 1.2f);
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

	if (!menuFont.loadFromFile("../Assets/Fonts/DelaGothic.ttf"))
	{
		cout << ">>> Font load failed! <<<" << endl;
	}

	menuSizeX = 200;
	menuSizeY = 85;

	acidBrick.setPosition(screenWidth / 2.0f, (screenHeight / 5.0f) * 4.0f);
	acidBrick.setScale(0.5f, 0.5f);

	iceBrick.setPosition(screenWidth / 2.0f, (screenHeight / 5.0f) * 3.0f);
	iceBrick.setScale(0.5f, 0.5f);

	bigBrick.setPosition(screenWidth / 2.0f, (screenHeight / 5.0f) * 2.0f);
	bigBrick.setScale(0.5f, 0.5f);

	stoneBrick[0].setPosition(screenWidth / 2.0f, screenHeight / 5.0f);
	stoneBrick[0].setScale(0.5f, 0.5f);

	playText.setString("Play");
	playText.setPosition(acidBrick.getPosition());
	playText.setFont(menuFont);
	playText.setCharacterSize(50);

	exitText.setString("Exit");
	exitText.setPosition(stoneBrick[0].getPosition());
	exitText.setFont(menuFont);
	exitText.setCharacterSize(50);

	creditsText.setString("Credits");
	creditsText.setPosition(bigBrick.getPosition());
	creditsText.setFont(menuFont);
	creditsText.setCharacterSize(50);

	instructionsText.setString("Istructions");
	instructionsText.setPosition(iceBrick.getPosition());
	instructionsText.setFont(menuFont);
	instructionsText.setCharacterSize(50);

}

static void Draw()
{
	window.draw(menuBackground);
	window.draw(acidBrick);
	window.draw(iceBrick);
	window.draw(bigBrick);
	window.draw(stoneBrick[0]);

	window.draw(playText);
	window.draw(exitText);	
	window.draw(creditsText);
	window.draw(instructionsText);
}

static void GetInput(GameSceen& currentSceen)
{
	Vector2f cursor = static_cast<Vector2f>(Mouse::getPosition(window));

	if (cursor.x >= acidBrick.getPosition().x &&
		cursor.x <= acidBrick.getPosition().x + acidBrick.getGlobalBounds().width &&
		cursor.y >= acidBrick.getPosition().y &&
		cursor.y <= acidBrick.getPosition().y + acidBrick.getGlobalBounds().height) 
	{

		playText.setFillColor(Color::Yellow);
		window.draw(playText);

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				currentSceen = GameSceen::GAME;
			}
		}
	}
	else 
	{
		playText.setFillColor(Color::White);
	}

	if (cursor.x >= stoneBrick[0].getPosition().x &&
		cursor.x <= stoneBrick[0].getPosition().x + stoneBrick[0].getGlobalBounds().width &&
		cursor.y >= stoneBrick[0].getPosition().y &&
		cursor.y <= stoneBrick[0].getPosition().y + stoneBrick[0].getGlobalBounds().height)
	{

		exitText.setFillColor(Color::Yellow);
		window.draw(exitText);

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				currentSceen = GameSceen::EXIT;
			}
		}
	}
	else
	{
		exitText.setFillColor(Color::White);
	}

	if (cursor.x >= bigBrick.getPosition().x &&
		cursor.x <= bigBrick.getPosition().x + bigBrick.getGlobalBounds().width &&
		cursor.y >= bigBrick.getPosition().y &&
		cursor.y <= bigBrick.getPosition().y + bigBrick.getGlobalBounds().height)
	{

		creditsText.setFillColor(Color::Yellow);
		window.draw(creditsText);

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				currentSceen = GameSceen::CREDITS;
			}
		}
	}
	else
	{
		creditsText.setFillColor(Color::White);
	}
	
	if (cursor.x >= iceBrick.getPosition().x &&
		cursor.x <= iceBrick.getPosition().x + iceBrick.getGlobalBounds().width &&
		cursor.y >= iceBrick.getPosition().y &&
		cursor.y <= iceBrick.getPosition().y + iceBrick.getGlobalBounds().height)
	{

		instructionsText.setFillColor(Color::Yellow);
		window.draw(instructionsText);

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				currentSceen = GameSceen::INSTRUCTIONS;
			}
		}
	}
	else
	{
		instructionsText.setFillColor(Color::White);
	}
}

static void ShowMenu(GameSceen& currentSceen)
{
	Draw();

	GetInput(currentSceen);
}

static void ShowInstructions(GameSceen& currentSceen)
{
	Text line1;
	line1.setString("Use arrows to move");
	line1.setPosition(screenWidth / 2, static_cast<double>(150));
	line1.setFont(menuFont);
	line1.setCharacterSize(50);

	Text line2;
	line2.setString("Use left CTRL to start the ball when stoped");
	line2.setPosition(screenWidth / 2, static_cast<double>(360));
	line2.setFont(menuFont);
	line2.setCharacterSize(50);

	Text line3;
	line3.setString("If an acid brick hits you, you die,");
	line3.setPosition(screenWidth / 2, static_cast<double>(400));
	line3.setFont(menuFont);
	line3.setCharacterSize(50);

	Text line4;
	line4.setString("but if you dodge it you earn 200pts for each one");
	line4.setPosition(screenWidth / 2, static_cast<double>(500));
	line4.setFont(menuFont);
	line4.setCharacterSize(50);

	Text line5;
	line5.setString("Press ESC to go back to the menu");
	line5.setPosition(screenWidth / 2, static_cast<double>(600));
	line5.setFont(menuFont);
	line5.setCharacterSize(50);

	window.draw(menuBackground);

	window.draw(line1);
	window.draw(line2);
	window.draw(line3);
	window.draw(line4);
	window.draw(line5);

	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			currentSceen = GameSceen::MENU;
		}
	}
}

static void ShowCredits(GameSceen& currentSceen)
{
	float center = static_cast<float>(screenWidth) / 2.0f;

	Text line1;
	line1.setString("Created by");
	line1.setPosition(center - (line1.getGlobalBounds().width / 2.0f), 20.0f);
	line1.setFont(menuFont);
	line1.setCharacterSize(50);

	Text line2;
	line2.setString("Juan Ignacio Digilio && Mateo Viko Monastra");
	line2.setPosition(center - (line2.getGlobalBounds().width / 2.0f), 40.0f);
	line2.setFont(menuFont);
	line2.setCharacterSize(50);

	Text line3;
	line3.setString("Image Campus students (First time with SFML)");
	line3.setPosition(center - (line3.getGlobalBounds().width / 2.0f), 60.0f);
	line3.setFont(menuFont);
	line3.setCharacterSize(50);

	Text line4;
	line4.setString("1st year of video games development");
	line4.setPosition(center - (line4.getGlobalBounds().width / 2.0f), 80.0f);
	line4.setFont(menuFont);
	line4.setCharacterSize(50);

	Text line5;
	line5.setString("https://juandigilio.itch.io/");
	line5.setPosition(center - (line5.getGlobalBounds().width / 2.0f), 100.0f);
	line5.setFont(menuFont);
	line5.setCharacterSize(50);

	Text line6;
	line6.setString("https://github.com/juandigilio");
	line6.setPosition(center - (line6.getGlobalBounds().width / 2.0f), 120.0f);
	line6.setFont(menuFont);
	line6.setCharacterSize(50);


	window.draw(menuBackground);
	window.draw(line1);
	window.draw(line2);
	window.draw(line3);
	window.draw(line4);
	window.draw(line5);
	window.draw(line6);

	Vector2f cursor = static_cast<Vector2f>(Mouse::getPosition(window));

	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			currentSceen = GameSceen::MENU;
		}
	}

	if (cursor.x >= line5.getPosition().x &&
		cursor.x <= line5.getPosition().x + line5.getGlobalBounds().width &&
		cursor.y >= line5.getPosition().y &&
		cursor.y <= line5.getPosition().y + line5.getGlobalBounds().height)
	{

		line5.setFillColor(Color::Yellow);
		window.draw(line5);

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				const char* url = "https://juandigilio.itch.io/";
				char command[256];
				snprintf(command, sizeof(command), "start %s", url);
				system(command);
			}
		}
	}

	if (cursor.x >= line6.getPosition().x &&
		cursor.x <= line6.getPosition().x + line6.getGlobalBounds().width &&
		cursor.y >= line6.getPosition().y &&
		cursor.y <= line6.getPosition().y + line6.getGlobalBounds().height)
	{

		line6.setFillColor(Color::Yellow);
		window.draw(line6);

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				const char* url = "https://github.com/juandigilio";
				char command[256];
				snprintf(command, sizeof(command), "start %s", url);
				system(command);
			}
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
			if (event.type == Event::Closed)
				window.close();
		}
	}
}