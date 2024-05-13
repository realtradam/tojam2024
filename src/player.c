#include "player.h"
#include "world.h"
#ifdef PLATFORM_WEB

#include <math.h>

#else

#include <fmath.h>

#endif

#include "raymath.h"

	void
drawPlayer(Player *player)
{
	DrawCube(player->position, 0.5f, 0.5f, 0.5f, player->color);
}

	Camera
lookThroughPlayer(Camera camera, Player player)
{
	if(player.camera_mode == 0)
	{
		float normalized = sqrtf(
				(player.direction.x * player.direction.x) +
				(player.direction.y * player.direction.y) +
				(player.direction.z * player.direction.z)
				);

		camera.position.x = player.position.x + player.direction.x / normalized;
		camera.position.y = player.position.y + player.direction.y / normalized;
		camera.position.z = player.position.z + player.direction.z / normalized;
		camera.target.x = player.position.x + player.direction.x * 10 / normalized;
		camera.target.y = player.position.y + player.direction.y * 10 / normalized;
		camera.target.z = player.position.z + player.direction.z * 10 / normalized;
	}
	else if(player.camera_mode == 1)
	{
		camera.position.x = player.position.x - (player.direction.x * 2);
		camera.position.y = player.position.y - (player.direction.y * 2);
		camera.position.z = player.position.z - (player.direction.z * 2) + player.camera_mode;
		camera.target.x = player.position.x;
		camera.target.y = player.position.y;
		camera.target.z = player.position.z;
	}
	camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	return camera;
}

	void
movePlayers(void)
{
	char stick[4] = {
		inputs_p1.stick_x,
		inputs_p1.stick_y,
		inputs_p2.stick_x,
		inputs_p2.stick_y
	};
	for(int i = 0; i < 2; ++i)
	{
		float xinput = stick[0 + (i * 2)] / 126.0f;
		float yinput = stick[1 + (i * 2)] / 126.0f;

		Vector2 direction = {
			world.players[i].direction.x,
			world.players[i].direction.y
		};

		direction = Vector2Rotate(direction, 0.01745329 * -xinput * 7);

		world.players[i].direction.z = yinput;
		world.players[i].direction.x = direction.x;
		world.players[i].direction.y = direction.y;

		world.players[i].position.x += world.players[i].direction.x * world.players[i].speed;
		world.players[i].position.y += world.players[i].direction.y * world.players[i].speed;
		world.players[i].position.z += world.players[i].direction.z * world.players[i].speed;
	}
}
