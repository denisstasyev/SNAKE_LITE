#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "Textbox.h"
#include "Map.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 608
#define BLOCK_SIZE 32 //размер в пиксел€х границы (стороны составных квадратиков)

class Game {
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	sf::Time GetElapsed();
	void RestartClock();

	Window* GetWindow();
private:
	Window m_window;

	sf::Clock m_clock;
	float m_elapsed;
//— точки зрени€ структурированности ниже - лучше, но так менее "интуитивно"
//	sf::Time m_elapsed;
//	float fElapsed = m_elapsed.asSeconds();

	World m_world;
	Snake m_snake;
	Textbox m_textbox;
	Map m_map;
};