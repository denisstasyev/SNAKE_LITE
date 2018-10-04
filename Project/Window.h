#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void Update();
	void ToggleFullscreen();

	void BeginDraw(); //очистка окна
	void EndDraw(); //отображение изменений


	bool IsDone();
	bool IsFullscreen();
	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();

	void Draw(sf::Drawable& l_drawable);

private:
	void Setup(const std::string title, const sf::Vector2u& size);
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
};