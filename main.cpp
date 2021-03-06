#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Map.h"
#include "Settings.h"

int main()
{
	srand(time(NULL));

	sf::RenderWindow wnd(sf::VideoMode((sn::Map::Size + 2) * sn::TILE_SIZE, (sn::Map::Size + 2) * sn::TILE_SIZE), "Snake", sf::Style::Titlebar | sf::Style::Close);
	sf::Event e;
	sf::Clock clock;

	float totalTime = 0;
	sn::Map map;
	sn::Snake snake;
	map.Reset(snake);

	while (wnd.isOpen()) {
		while (wnd.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				wnd.close();
			snake.OnEvent(e);
		}

		totalTime += clock.restart().asSeconds();
		while (totalTime >= sn::UPDATE_SPEED) {
			snake.Update(map);
			totalTime -= sn::UPDATE_SPEED;
		}

		wnd.clear();
		map.Render(wnd);
		wnd.display();
	}


    return 0;
}

