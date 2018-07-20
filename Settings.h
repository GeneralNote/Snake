#pragma once

namespace sn
{
	const float UPDATE_SPEED = 0.1f;	// in 
	const int TILE_SIZE = 24;			// reserve 20 px for 
	const int TILE_MARGIN = 2;			// 20 - 2 - 2 == 16px tiles 
	const int MAP_OFFSET = TILE_SIZE;	// design thingy - offset from (0,0) window coords
	const int SNAKE_SPAWN_MARGIN = 5;	// the min distance from walls when spawning a snake
	const int SNAKE_SPAWN_LENGTH = 4;	// snake length when it spawns
}