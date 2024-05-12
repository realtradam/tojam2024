#include "player.h"

void
drawPlayer(Player *player)
{
	//DrawCube(player->position, 1.0f, 1.0f, 1.0f, BLUE);
	DrawSphereEx(player->position, 0.5f, 3, 3, player->color);
}

void
movePlayer(Player *player)
{
	player->direction.x = inputs_p1.stick_x / 126.0f;
	player->direction.z = -inputs_p1.stick_y / 126.0f;
	player->position.x += player->direction.x * player->speed;
	player->position.y += player->direction.y * player->speed;
	player->position.z += player->direction.z * player->speed;
}
