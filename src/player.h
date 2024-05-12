#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "raylib.h"
#include "input.h"

typedef
struct
{
	Vector3 position;
	Vector3 direction;
	float speed;
	Color color;
}
Player;

void
drawPlayer(Player *player);

void
movePlayer(Player *player);

#endif
