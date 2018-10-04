#include "World.h"

World::World(sf::Vector2u l_windSize, size_t l_blockSize) :
	m_windowSize(l_windSize),
	m_blockSize(l_blockSize) {
	//m_blockSize - размер в пикселях границы (стороны составных квадратиков)
	srand(time(nullptr));
	RespawnApple();
//	m_appleShape.setFillColor(sf::Color::Red);
//	m_appleShape.setRadius(m_blockSize / 2);

	m_appleImage.loadFromFile("texture.png"); //загружаем файл для карты
	m_appleImage.createMaskFromColor(sf::Color(255, 255, 255)); //чтобы убрать белый фон
	m_appleTexture.loadFromImage(m_appleImage); //заряжаем текстуру картинкой
	m_appleSprite.setTexture(m_appleTexture); //заливаем текстуру спрайтом
	m_appleSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_appleSprite.setOrigin(16, 16);

	for (int i = 0; i < 4; ++i) {
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)) {
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		}
		else {
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}
		if (i < 2) {
			m_bounds[i].setPosition(0, 0);
		}
		else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}

	m_soundBuffer.loadFromFile("chewing_apple.ogg");
	m_sound.setBuffer(m_soundBuffer);
}

World::~World() {
}

size_t World::GetBlockSize() {
	return m_blockSize;
}

void World::RespawnApple() {
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_item = sf::Vector2i((rand() % maxX + 1), (rand() % maxY + 1));
//	m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
	m_appleSprite.setPosition(m_item.x * m_blockSize + 16, m_item.y * m_blockSize + 16);

}

void World::Update(Snake& l_player) {
	//ПРОВЕРКА НА ПОПАДАНИЕ ЯБЛОКА НА ЗМЕЮ
	for (size_t i = 1; i < l_player.GetSnakeBody().size(); ++i) {
		if (l_player.GetSnakeBody()[i].position == m_item)
			RespawnApple();
	}

	//Далее
	if (l_player.GetPosition() == m_item) {
		l_player.Extend();

		m_sound.setVolume(100);
		m_sound.play();

		l_player.IncreaseScore();
		RespawnApple();
	}

	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;

	if ((l_player.GetPosition().x <= 0) ||
		(l_player.GetPosition().y <= 0) ||
		(l_player.GetPosition().x >= gridSize_x - 1) ||
		(l_player.GetPosition().y >= gridSize_y - 1)) {
			l_player.Lose();
	}
}

void World::Render(sf::RenderWindow& l_window) {
	for (size_t i = 0; i < 4; ++i) {
		l_window.draw(m_bounds[i]);
	}
	l_window.draw(m_appleSprite);
//	l_window.draw(m_appleShape);
}