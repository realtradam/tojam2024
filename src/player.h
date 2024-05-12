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

Camera
lookThroughPlayer(Camera camera, Player player, Player player2);

void
drawPlayer(Player *player);

void
movePlayers(void);

#endif
