#include "player.h"

void
drawPlayer(Player *player)
{
	//DrawCube(player->position, 1.0f, 1.0f, 1.0f, BLUE);
	DrawSphereEx(player->position, 0.5f, 3, 3, BLUE);
}

void
movePlayer(Player *player)
{
	player->position.x += player->direction.x * player->speed;
	player->position.y += player->direction.y * player->speed;
	player->position.z += player->direction.z * player->speed;
}
