#include "bullet.h"
#include "world.h"
#include "raymath.h"

typedef
struct
{
	int team; // 0 means not in use
	Vector3 position;
	Vector3 direction;
	int lifetime;
}
Bullet;

float bullet_speed = 0.5;

Bullet bullets[100];

	void
spawn_bullet(int team, Vector3 position, Vector3 direction)
{
	if(team == 0)
	{
		return;
	}
	for(int i = 0; i < 100; ++i)
	{
		if(bullets[i].team != 0)
		{
			continue;
		}
		bullets[i].team = team;
		bullets[i].position = position;
		bullets[i].direction = direction;
		bullets[i].lifetime = 100;
		return;
	};
}

	void
render_bullets(void)
{
	for(int i = 0; i < 100; ++i)
	{
		if(bullets[i].team == 0)
		{
			continue;
		}
		else if(bullets[i].team == 1)
		{
			DrawCube(bullets[i].position, 0.25, 0.25, 0.25, BLUE);
		}
		else if(bullets[i].team == 2)
		{
			DrawCube(bullets[i].position, 0.25, 0.25, 0.25, VIOLET);
		}
	}
}

void
bullet_collision_check(void)
{
	for(int i = 0; i < 100; ++i)
	{
		if(bullets[i].team == 0)
		{
			continue;
		}
		bullets[i].lifetime -= 1;
		if(bullets[i].lifetime <= 0)
		{
			bullets[i].team = 0;
		}
		bullets[i].position.x += bullets[i].direction.x * bullet_speed;
		bullets[i].position.y += bullets[i].direction.y * bullet_speed;
		bullets[i].position.z += bullets[i].direction.z * bullet_speed;
		Vector3 enemypos = { 0 };
		if (bullets[i].team == 1)
		{
			enemypos = world.players[1].position;
			if (Vector3Distance(bullets[i].position, enemypos) < 1)
			{
				world.players[0].points++;
				bullets[i].team = 0;
			}
		}
		else if (bullets[i].team == 2)
		{
			enemypos = world.players[0].position;
			if (Vector3Distance(bullets[i].position, enemypos) < 1)
			{
				world.players[1].points++;
				bullets[i].team = 0;
			}
		}
	}

}
