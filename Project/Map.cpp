#include "Map.h"

Map::Map() {
/*
//	map_image.loadFromFile("map.png"); //загружаем файл для карты
	m_mapImage.loadFromFile("grass.jpg"); //загружаем файл для карты
	m_mapTexture.loadFromImage(m_mapImage); //заряжаем текстуру картинкой
	m_mapSprite.setTexture(m_mapTexture); //заливаем текстуру спрайтом
//	map_sprite.setTextureRect(sf::IntRect(0, 160, 32, 32));
*/

	m_mapImage.loadFromFile("texture.png"); //загружаем файл для карты
	m_mapTexture.loadFromImage(m_mapImage); //заряжаем текстуру картинкой
	m_mapSprite.setTexture(m_mapTexture); //заливаем текстуру спрайтом
}

Map::~Map() {
}

void Map::Render(sf::RenderWindow& l_window) {

	for (size_t i = 0; i < MAP_HEIGHT; i++) {
		for (size_t j = 0; j < MAP_WIDTH; j++) {
			if (TileMap[i][j] == ' ') {
				m_mapSprite.setTextureRect(sf::IntRect(161, 0, 32, 32));
				m_mapSprite.setPosition(j * 32, i * 32);
				l_window.draw(m_mapSprite); //рисуем квадратики на экран
			}
			if (TileMap[i][j] == 'r') {
				m_mapSprite.setTextureRect(sf::IntRect(129, 0, 32, 32));
				m_mapSprite.setPosition(j * 32, i * 32);
				l_window.draw(m_mapSprite); //рисуем квадратики на экран
			}

		}
	}

	l_window.draw(m_mapSprite);
}