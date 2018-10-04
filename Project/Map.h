#pragma once
#include <SFML\Graphics.hpp>

#define MAP_WIDTH 25 //размер карты ширина
#define MAP_HEIGHT 19 //размер карты высота

class Map {
public:
	Map();
	~Map();

	//rock - "r"
	//sand - " "
	sf::String TileMap[MAP_HEIGHT] = {
		"0000000000000000000000000",
		"0                       0",
		"0                       0",
		"0                   r   0",
		"0                       0",
		"0         r             0",
		"0        r              0",
		"0       rr              0",
		"0        r              0",
		"0              r        0",
		"0             rr        0",
		"0              rr       0",
		"0                       0",
		"0                       0",
		"0                       0",
		"0       r               0",
		"0      rr               0",
		"0                       0",
		"0000000000000000000000000"
	};

	void Render(sf::RenderWindow& l_window);

private:


	sf::Image m_mapImage; //объект изображения для карты
	sf::Texture m_mapTexture; //текстура карты	
	sf::Sprite m_mapSprite; //создаём спрайт для карт
};