#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>
#include "Tile.h"
#include "Settings.h"

namespace sn
{
	class Map;

	class Snake
	{
	public:
		void Spawn(int x, int y);
		inline Tile GetDirection()
		{
			return direction;
		}

		void OnEvent(const sf::Event& e);

		void Update(Map& map);

	private:
		sf::Vector2i tail = sf::Vector2i(0, 0);
		int distance = 0;

		sf::Vector2i position = sf::Vector2i(0, 0);
		int length = SNAKE_SPAWN_LENGTH;
		Tile direction = Tile::SnakeDown;
	};
}