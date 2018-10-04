#include "Game.h"
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //Для закрытия консольного окна
int main(int argc, char** argv[]) {
	// Program entry point.
	Game game;
	while(!game.GetWindow()->IsDone()) { //Game loop.
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
		//sf::sleep(sf::seconds(0.2)); //Sleep for 0.2 seconds.
	}
	return 0;
}

/*
sf::Texture texture;
if (!texture.loadFromFile("filename.png") {
	// Handle an error.
}

sf::Sprite sprite(texture);
...
window.draw(sprite);
или sprite.setTexture(texture);

*/

//проверить если змейка все место занимает