#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "raylib.h"
#include "input.h"

// for camera_style
// 0 = first person
// 1 = third person
typedef
struct
{
	Vector3 position;
	Vector3 direction;
	float speed;
	Color color;
	int camera_mode;
}
Player;

Camera
lookThroughPlayer(Camera camera, Player player);

void
drawPlayer(Player *player);

void
movePlayers(void);

#endif
