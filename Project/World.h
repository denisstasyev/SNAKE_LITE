#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"

class World {
public:
	World(sf::Vector2u l_windSize, size_t l_blockSize);
	~World();

	size_t GetBlockSize();

	void RespawnApple();

	void Update(Snake& l_player);
	void Render(sf::RenderWindow& l_window);
private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	size_t m_blockSize;

//	sf::CircleShape m_appleShape;
	sf::Image m_appleImage; //объект изображения для карты
	sf::Texture m_appleTexture; //текстура карты	
	sf::Sprite m_appleSprite; //создаём спрайт для карт

	sf::RectangleShape m_bounds[4];

	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound;
};