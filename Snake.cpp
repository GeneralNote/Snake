#include "Snake.h"
#include "Map.h"

namespace sn
{
	void Snake::Spawn(int x, int y)
	{
		distance = 0;
		length = SNAKE_SPAWN_LENGTH;
		tail = position = sf::Vector2i(x, y);
	}

	void Snake::OnEvent(const sf::Event & e)
	{
		if (e.type == sf::Event::KeyPressed) {
			sf::Keyboard::Key kc = e.key.code;

			if ((kc == sf::Keyboard::Left || kc == sf::Keyboard::A) && direction != Tile::SnakeRight)
				direction = Tile::SnakeLeft;
			else if ((kc == sf::Keyboard::Right || kc == sf::Keyboard::D) && direction != Tile::SnakeLeft)
				direction = Tile::SnakeRight;
			else if ((kc == sf::Keyboard::Up || kc == sf::Keyboard::W) && direction != Tile::SnakeDown)
				direction = Tile::SnakeUp;
			else if ((kc == sf::Keyboard::Down || kc == sf::Keyboard::S) && direction != Tile::SnakeUp)
				direction = Tile::SnakeDown;
		}
	}

	void Snake::Update(Map & map)
	{
		if (!map.Trigger(position.x, position.y, direction, *this)) {
			Tile previous = map.GetAt(position.x, position.y);

			map.SetAt(position.x, position.y, direction);
			distance++;

			if (previous == Tile::Food)
				length++;
			else {
				if (distance >= length) {
					Tile tailTile = map.GetAt(tail.x, tail.y);
					map.SetAt(tail.x, tail.y, Tile::Empty);

					distance--;

					tail.x += (tailTile == Tile::SnakeLeft ? -1 : (tailTile == Tile::SnakeRight ? 1 : 0));
					tail.y += (tailTile == Tile::SnakeUp ? -1 : (tailTile == Tile::SnakeDown ? 1 : 0));
				}
			}
		}
		position.x += (direction == Tile::SnakeLeft ? -1 : (direction == Tile::SnakeRight ? 1 : 0));
		position.y += (direction == Tile::SnakeUp ? -1 : (direction == Tile::SnakeDown ? 1 : 0));
	}
}