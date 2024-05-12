#include "player.h"
#include "world.h"
#include <fmath.h>

	void
drawPlayer(Player *player)
{
	//DrawCube(player->position, 1.0f, 1.0f, 1.0f, BLUE);
	//DrawSphereEx(player->position, 0.5f, 3, 3, player->color);
	DrawCube(player->position, 0.5f, 0.5f, 0.5f, player->color);
}

Camera
lookThroughPlayer(Camera camera, Player player, Player player2)
{
	//camera.position = player.position;
	camera.position.x = player.position.x - (player.direction.x * 2);
	camera.position.y = player.position.y - (player.direction.y * 2);
	camera.position.z = player.position.z - (player.direction.z * 2);
	camera.target.x = player.position.x;
	camera.target.y = player.position.y;
	camera.target.z = player.position.z;
	camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
	//camera.target = player2.position;
	//camera.target = (Vector3){
	//	0, 0, 0
	//};
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	return camera;
}

	void
movePlayers(void)
{
	float x = inputs_p1.stick_x / 126.0f;
	float y = -inputs_p1.stick_y / 126.0f;

	//float x = world.players[0].direction.x;
	//float y = world.players[0].direction.z;

	float distance = sqrtf(x * x + y * y);

	if(distance != 0)
	{
		world.players[0].direction.x = x / distance;
		world.players[0].direction.y = y / distance;
	}

	world.players[1].direction.y = inputs_p2.stick_x / 126.0f;
	world.players[1].direction.z = -inputs_p2.stick_y / 126.0f;

	world.players[0].position.x += world.players[0].direction.x * world.players[0].speed;
	world.players[0].position.y += world.players[0].direction.y * world.players[0].speed;
	world.players[0].position.z += world.players[0].direction.z * world.players[0].speed;
	world.players[1].position.x += world.players[1].direction.x * world.players[1].speed;
	world.players[1].position.y += world.players[1].direction.y * world.players[1].speed;
	world.players[1].position.z += world.players[1].direction.z * world.players[1].speed;
}
