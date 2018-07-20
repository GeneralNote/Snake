#include "Map.h"
#include "Snake.h"
#include "Settings.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace sn
{
	bool Map::Trigger(int x, int y, Tile tile, Snake & snake)
	{
		if (x < 0 || x >= Size || y < 0 || y >= Size || (isSnake(GetAt(x, y)) && isSnake(tile))) {
			Reset(snake);
			return true;
		}
		else if (GetAt(x, y) == Tile::Food)
			PlaceFood();

		return false;
	}

	void Map::Reset(Snake & snake)
	{
		int snakeNewX = SNAKE_SPAWN_MARGIN + rand() % (Size - SNAKE_SPAWN_MARGIN * 2);
		int snakeNewY = SNAKE_SPAWN_MARGIN + rand() % (Size - SNAKE_SPAWN_MARGIN * 2);

		snake.Spawn(snakeNewX, snakeNewY);

		for (int x = 0; x < Size; x++) {
			for (int y = 0; y < Size; y++) {
				data[x][y] = Tile::Empty;
			}
		}
		data[snakeNewX][snakeNewY] = snake.GetDirection();

		PlaceFood();
	}

	void Map::PlaceFood()
	{
		std::vector<std::pair<int, int>> moves = getEmptyTiles();

		std::pair<int, int>& move = moves[rand() % moves.size()];

		data[move.first][move.second] = Tile::Food;
	}

	void Map::Render(sf::RenderWindow & wnd)
	{
		sf::RectangleShape tile;
		for (int x = 0; x < Size; x++) {
			for (int y = 0; y < Size; y++) {
				Tile t = GetAt(x, y);

				if (t == Tile::Empty)
					tile.setFillColor(sf::Color(30, 30, 30));
				else if (t == Tile::Food)
					tile.setFillColor(sf::Color::Red);
				else if (isSnake(t))
					tile.setFillColor(sf::Color::White);

				if (t == Tile::Empty || t == Tile::Food) {
					tile.setPosition(x*TILE_SIZE + TILE_MARGIN + MAP_OFFSET, y*TILE_SIZE + TILE_MARGIN + MAP_OFFSET);
					tile.setSize(sf::Vector2f(TILE_SIZE - TILE_MARGIN * 2, TILE_SIZE - TILE_MARGIN * 2));
				}
				else if (t == Tile::SnakeDown) {
					tile.setPosition(x*TILE_SIZE + TILE_MARGIN + MAP_OFFSET, y*TILE_SIZE + TILE_MARGIN + MAP_OFFSET);
					tile.setSize(sf::Vector2f(TILE_SIZE - TILE_MARGIN * 2, TILE_SIZE));
				}
				else if (t == Tile::SnakeRight) {
					tile.setPosition(x*TILE_SIZE + TILE_MARGIN + MAP_OFFSET, y*TILE_SIZE + TILE_MARGIN + MAP_OFFSET);
					tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE - TILE_MARGIN * 2));
				}
				else if (t == Tile::SnakeLeft) {
					tile.setPosition(x*TILE_SIZE - TILE_MARGIN + MAP_OFFSET, y*TILE_SIZE + TILE_MARGIN + MAP_OFFSET);
					tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE - TILE_MARGIN * 2));
				}
				else if (t == Tile::SnakeUp) {
					tile.setPosition(x*TILE_SIZE + TILE_MARGIN + MAP_OFFSET, y*TILE_SIZE - TILE_MARGIN + MAP_OFFSET);
					tile.setSize(sf::Vector2f(TILE_SIZE - TILE_MARGIN * 2, TILE_SIZE));
				}

				wnd.draw(tile);
			}
		}
	}

	std::vector<std::pair<int, int>> Map::getEmptyTiles()
	{
		int freeTiles = 0;

		// first count all empty tiles (note: using this, we wont have to reallocate memory at all)
		for (int x = 0; x < Size; x++)
			for (int y = 0; y < Size; y++)
				if (data[x][y] == Tile::Empty)
					freeTiles++;

		// allocate enough memory
		std::vector<std::pair<int, int>> ret(freeTiles);

		// add those empty tiles to the memory
		int i = 0;
		for (int x = 0; x < Size; x++)
			for (int y = 0; y < Size; y++)
				if (data[x][y] == Tile::Empty) {
					ret[i] = std::make_pair(x, y);
					i++;
				}

		return ret;
	}
}