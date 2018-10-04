#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)),
	m_world(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT), BLOCK_SIZE),
	m_snake(m_world.GetBlockSize(), &m_textbox) {
	// Setting up class members.
	m_clock.restart();

	m_textbox.Setup(5, 16, 480, sf::Vector2f(168, 0));
	m_elapsed = 0.0f;

	m_textbox.Add("Игра \"Snake Unlimited\" - испытай себя!");
//	m_textbox.Add("Генератор случайных чисел с числом: " + std::to_string(time(nullptr)));
}

Game::~Game() {
}

void Game::HandleInput(){
	//Input handling.
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		&& m_snake.GetPhysicalDirection() != Direction::Down) {
		m_snake.SetDirection(Direction::Up);
	} 
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		&& m_snake.GetPhysicalDirection() != Direction::Up) {
		m_snake.SetDirection(Direction::Down);
	} 
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		&& m_snake.GetPhysicalDirection() != Direction::Right) {
		m_snake.SetDirection(Direction::Left);
	} 
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		&& m_snake.GetPhysicalDirection() != Direction::Left) {
		m_snake.SetDirection(Direction::Right);
	}
//	else m_snake.SetDirection(Direction::None); //чтобы змея останавливалась
}

void Game::Update() {
	m_window.Update();
	float timestep = 1.0f / m_snake.GetSpeed();
	if (m_elapsed >= timestep) {
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timestep;
		if (m_snake.HasLost()) { //"Что делать после проигрыша?" - здесь лежит.
			m_textbox.Add("GAME OVER! Счет: " + std::to_string((long long)m_snake.GetScore()));
			m_snake.Reset();
		}
	}
}

void Game::Render(){
	m_window.BeginDraw();
	//Render here.
//	m_window.Draw(m_world); //Подумать о таком вызове

	m_map.Render(*m_window.GetRenderWindow());
	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());
	m_textbox.Render(*m_window.GetRenderWindow());

	m_window.EndDraw();
}

sf::Time Game::GetElapsed() {
	return m_clock.getElapsedTime();
//	return m_elapsed;
}

void Game::RestartClock() {
//	m_elapsed += m_clock.restart();
	m_elapsed += m_clock.restart().asSeconds();
}

Window* Game::GetWindow() {
	return &m_window;
}