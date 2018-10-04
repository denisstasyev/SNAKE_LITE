#pragma once
#include <SFML/Graphics.hpp>
#include "Textbox.h"
//#include <vector>
#include <deque>

#define SNAKE_SPEED 15

enum class Direction { None, Up, Down, Left, Right };

struct SnakeSegment {
	SnakeSegment(int x, int y, Direction l_dir) : 
		position(x,y), 
		directionSegment(l_dir) {
	}
	sf::Vector2i position;
	Direction directionSegment; //�������� �� ����������� �������� ������� �������� ���� (��� ����������� �������)
};

//using SnakeContainer = std::vector<SnakeSegment>;
using SnakeContainer = std::deque<SnakeSegment>; //��� ����� define???
//std::deque (������������ �������) ������������ ����� ���������������� ��������������� ���������,
//������� ��������� ������ ��������� � ������� �������� � ������ � � �����.
//����� �������� �����������.

class Snake{
public:
	Snake(int l_blockSize, Textbox* l_log);
	~Snake();

	// Helper methods.
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	SnakeContainer GetSnakeBody();

	int GetLives();
	int GetScore();

	void IncreaseScore();

	bool HasLost();
	void Lose(); //Handle losing here.
	void ToggleLost();

	Direction GetPhysicalDirection();

	void Extend(); //Grow the snake.
	void Reset(); //Reset to starting position.

	void Move(); //Movement method.
	void Tick(); //Update method.
	void Cut(int l_segments); //Method for cutting snake.
	void Render(sf::RenderWindow& l_window);
private:
	void CheckCollision(); //Checking collisions.

	SnakeContainer m_snakeBody; //Segment vector.
	int m_size; //Size of the graphics.
	Direction m_dir; //Current direction of head part of snake.
	int m_speed; //Speed of the snake. �� ���� ���������� � �������
	int m_lives; //Lives.
	int m_score; //Score.
	bool m_lost; //Losing state.
//	sf::RectangleShape m_bodyRect; //Shape used in rendering.
	sf::Image m_snakeImage; //������ ����������� ��� ����
	sf::Texture m_snakeTexture; //�������� ��� ����
	sf::Sprite m_snakeSprite; //������ ������ ��� ����

	Textbox* m_log;
};