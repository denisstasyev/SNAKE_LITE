#include "Snake.h"

Snake::Snake(int l_blockSize, Textbox* l_log) :
	m_size(l_blockSize),
	m_log(l_log) {
//	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1)); //m_size - 1 - чтобы блоки не сливались 

	m_snakeImage.loadFromFile("texture.png"); //загружаем файл для карты
	m_snakeImage.createMaskFromColor(sf::Color(255, 255, 255)); //чтобы убрать белый фон
	m_snakeTexture.loadFromImage(m_snakeImage); //заряжаем текстуру картинкой
	m_snakeSprite.setTexture(m_snakeTexture); //заливаем текстуру спрайтом
//	m_snakeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
//	m_snakeSprite.setRotation(45);

	Reset();
}

Snake::~Snake() {
}

void Snake::SetDirection(Direction l_dir) {
	m_dir = l_dir;
}
Direction Snake::GetDirection() {
	return m_dir;
}
int Snake::GetSpeed() {
	return m_speed;
}
sf::Vector2i Snake::GetPosition() {
	return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1,1)); //подумать над (1, 1)
}
SnakeContainer Snake::GetSnakeBody() {
	return m_snakeBody;
}

int Snake::GetLives() {
	return m_lives;
}
int Snake::GetScore() {
	return m_score;
}

void Snake::IncreaseScore() {
	m_score += 10;
	m_log->Add("Вы съели яблоко. Счет: " + std::to_string((long long)m_score));
}

bool Snake::HasLost() {
	return m_lost;
}
void Snake::Lose() {
	m_lost = true;
}
void Snake::ToggleLost() {
	m_lost = !m_lost;
}

Direction Snake::GetPhysicalDirection() {
	if (m_snakeBody.size() <= 1) {
		return Direction::None;
	}

	SnakeSegment& head = m_snakeBody[0];
	SnakeSegment& neck = m_snakeBody[1];

	if (head.position.x == neck.position.x) {
		return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
	}
	else if(head.position.y == neck.position.y) {
			return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
		}

	return Direction::None;
}

void Snake::Extend() {
	if (m_snakeBody.empty()) {
		return;
	}

	SnakeSegment tail_head_ = m_snakeBody[m_snakeBody.size() - 1];
	m_snakeBody.push_back(tail_head_); //дублируем последний = удлинение

	SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];
	if (tail_head.directionSegment == Direction::Right)
		tail_head.position.x--;
	if (tail_head.directionSegment == Direction::Left)
		tail_head.position.x++;
	if (tail_head.directionSegment == Direction::Up)
		tail_head.position.y++;
	if (tail_head.directionSegment == Direction::Down)
		tail_head.position.y--;

	/*
	if (m_snakeBody.empty()) {
		return;
	}
	SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];

	if (m_snakeBody.size() > 1) {
		SnakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 2];

		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y > tail_bone.position.y) {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1, Direction::Down));
			} 
			else {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1, Direction::Up));
			}
		} 
		else if (tail_head.position.y == tail_bone.position.y) {
				if (tail_head.position.x > tail_bone.position.x) {
					m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y, Direction::Left));
				} 
				else {
					m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y, Direction::Right));
				}
			}
	}
	else {
		if (m_dir == Direction::Up) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1, Direction::Up));
		} 
		else if (m_dir == Direction::Down) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1, Direction::Down));
		}
		else if (m_dir == Direction::Left) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y, Direction::Left));
		}
		else if (m_dir == Direction::Right) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y, Direction::Right));
		}
	}
	*/
}

void Snake::Reset(){
	m_snakeBody.clear();
	m_snakeBody.push_back(SnakeSegment(12, 10, Direction::Down)); //Для установки центра
	m_snakeBody.push_back(SnakeSegment(12, 9, Direction::Down));
	m_snakeBody.push_back(SnakeSegment(12, 8, Direction::Down));

	SetDirection(Direction::None); //Start off still.
	//Parameters
	m_speed = SNAKE_SPEED;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::CheckCollision() { //столкновение с собой
	if (m_snakeBody.size() < 5) {
		return;
	}
	SnakeSegment& head = m_snakeBody.front();
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
		if (itr->position == head.position) {
			int segments = m_snakeBody.end() - itr;
			Cut(segments);
			break;
		}
	}
}

void Snake::Move() {
	for (size_t i = m_snakeBody.size() - 1; i > 0; --i) {
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
		m_snakeBody[i].directionSegment = m_snakeBody[i - 1].directionSegment;
	}
	if (m_dir == Direction::Left) {
		--m_snakeBody[0].position.x;
		m_snakeBody[0].directionSegment = Direction::Left;
	} 
	else if (m_dir == Direction::Right) {
			++m_snakeBody[0].position.x;
			m_snakeBody[0].directionSegment = Direction::Right;
		}
		else if (m_dir == Direction::Up) {
				--m_snakeBody[0].position.y;
				m_snakeBody[0].directionSegment = Direction::Up;
			} 
			else if (m_dir == Direction::Down) {
					++m_snakeBody[0].position.y;
					m_snakeBody[0].directionSegment = Direction::Down;
				}
}

void Snake::Tick() {
	if (m_snakeBody.empty()) {
		return;
	}
	if (m_dir == Direction::None) {
		return;
	}
	Move();
	CheckCollision();
}

void Snake::Cut(int l_segments) {
	for (int i = 0; i < l_segments; ++i) {
		m_snakeBody.pop_back();
	}
	--m_lives;
	if (!m_lives) {
		Lose();
		return;
	}
	m_log->Add("Вы потеряли 1 жизнь! Осталось: " + std::to_string((long long)m_lives));
}

void Snake::Render(sf::RenderWindow& l_window) {
	if (m_snakeBody.empty()) {
		return;
	}
/*
	auto head = m_snakeBody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
	l_window.draw(m_bodyRect);

	m_bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
		m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
		l_window.draw(m_bodyRect);
	}
*/
	auto head = m_snakeBody.begin();
	m_snakeSprite.setTextureRect(sf::IntRect(193, 0, 32, 32));
	m_snakeSprite.setOrigin(16, 16);
	m_snakeSprite.setPosition(head->position.x * m_size + 16, head->position.y * m_size + 16);
	Direction p_dir = head->directionSegment;
	switch (p_dir) {
		case Direction::Up: {
			l_window.draw(m_snakeSprite);
			break;
		}
		case Direction::Down: {
			 m_snakeSprite.setRotation(180.F);
			 l_window.draw(m_snakeSprite);
			 m_snakeSprite.setRotation(0.F);
			 break;
		}
		case Direction::Right: {
			m_snakeSprite.setRotation(90.F);
			l_window.draw(m_snakeSprite);
			m_snakeSprite.setRotation(0.F);
			break;
		}
		case Direction::Left: {
			m_snakeSprite.setRotation(-90.F);
			l_window.draw(m_snakeSprite);
			m_snakeSprite.setRotation(0.F);
			break;
		}
		default: {
		}
	}

//центральная часть тут рисуется
	m_snakeSprite.setTextureRect(sf::IntRect(225, 0, 32, 32));
	//m_snakeSprite.setOrigin(16, 16);

	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end() - 1; ++itr) {
		m_snakeSprite.setPosition(itr->position.x * m_size + 16, itr->position.y * m_size + 16);
		if (p_dir == itr->directionSegment) {
			if (itr->directionSegment == Direction::Down) {
				m_snakeSprite.setRotation(180.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setRotation(0);
			}
			if (itr->directionSegment == Direction::Up) {
				m_snakeSprite.setRotation(0.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setRotation(0.F);
			}
			if (itr->directionSegment == Direction::Left) {
				m_snakeSprite.setRotation(90.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setRotation(0.F);
			}
			if (itr->directionSegment == Direction::Right) {
				m_snakeSprite.setRotation(-90.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setRotation(0.F);
			}
			p_dir = itr->directionSegment;
		}
		else {
			if ((p_dir == Direction::Right && itr->directionSegment == Direction::Down)
				|| (p_dir == Direction::Up && itr->directionSegment == Direction::Left)) {
				m_snakeSprite.setTextureRect(sf::IntRect(289, 0, 32, 32));
				m_snakeSprite.setRotation(-90.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setRotation(0.F);
				m_snakeSprite.setTextureRect(sf::IntRect(225, 0, 32, 32));
			}
			if ((p_dir == Direction::Up && itr->directionSegment == Direction::Right)
				|| (p_dir == Direction::Left && itr->directionSegment == Direction::Down)) {
				m_snakeSprite.setTextureRect(sf::IntRect(289, 0, 32, 32));
				m_snakeSprite.setRotation(-180.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setRotation(0.F);
				m_snakeSprite.setTextureRect(sf::IntRect(225, 0, 32, 32));
			}
			if ((p_dir == Direction::Left && itr->directionSegment == Direction::Up)
				|| (p_dir == Direction::Down && itr->directionSegment == Direction::Right)) {
				m_snakeSprite.setTextureRect(sf::IntRect(289, 0, 32, 32));
				m_snakeSprite.setRotation(-270.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setRotation(0.F);
				m_snakeSprite.setTextureRect(sf::IntRect(225, 0, 32, 32));
			}
			if ((p_dir == Direction::Down && itr->directionSegment == Direction::Left)
				|| (p_dir == Direction::Right && itr->directionSegment == Direction::Up)) {
				m_snakeSprite.setTextureRect(sf::IntRect(289, 0, 32, 32));
				m_snakeSprite.setRotation(0.F);
				l_window.draw(m_snakeSprite);
				m_snakeSprite.setTextureRect(sf::IntRect(225, 0, 32, 32));
			}
			p_dir = itr->directionSegment;
		}
	}

//ниже рисуем хвост
	auto tail = m_snakeBody.end() - 1;
	m_snakeSprite.setTextureRect(sf::IntRect(257, 0, 32, 32));
	//m_snakeSprite.setOrigin(16, 16);
	m_snakeSprite.setPosition(tail->position.x * m_size + 16, tail->position.y * m_size + 16);

	switch (p_dir) {
	case Direction::Down: {
		l_window.draw(m_snakeSprite);
		break;
	}
	case Direction::Up: {
		m_snakeSprite.setRotation(180.F);
		l_window.draw(m_snakeSprite);
		m_snakeSprite.setRotation(0.F);
		break;
	}
	case Direction::Left: {
		m_snakeSprite.setRotation(90.F);
		l_window.draw(m_snakeSprite);
		m_snakeSprite.setRotation(0.F);
		break;
	}
	case Direction::Right: {
		m_snakeSprite.setRotation(-90.F);
		l_window.draw(m_snakeSprite);
		m_snakeSprite.setRotation(0.F);
		break;
	}
	default: {
	}
	}

}