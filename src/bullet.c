#include "bullet.h"

typedef
struct
{
	int team; // 0 means not in use
	Vector3 position;
	Vector3 direction;
	int lifetime;
}
Bullet;

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
		DrawCube(bullets[i].position, 0.25, 0.25, 0.25, RED);
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
		bullets[i].position.x += bullets[i].direction.x * 0.25;
		bullets[i].position.y += bullets[i].direction.y * 0.25;
		bullets[i].position.z += bullets[i].direction.z * 0.25;
	}

}