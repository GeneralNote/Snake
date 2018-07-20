#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Tile.h"

namespace sn
{
	class Snake;

	class Map
	{
	public:
		static const int Size = 16;

		inline Tile GetAt(int x, int y)
		{
			return data[x][y];
		}
		inline void SetAt(int x, int y, Tile tile)
		{
			data[x][y] = tile;
		}

		bool Trigger(int x, int y, Tile tile, Snake& snake);
		void Reset(Snake& snake);
		void PlaceFood();

		void Render(sf::RenderWindow& wnd);

	private:
		std::vector<std::pair<int, int>> getEmptyTiles();

		inline bool isSnake(Tile t)
		{
			return (t == Tile::SnakeDown || t == Tile::SnakeLeft || t == Tile::SnakeRight || t == Tile::SnakeUp);
		}

		Tile data[Size][Size] = { Tile::Empty };
	};
}
