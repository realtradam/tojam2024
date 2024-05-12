#ifndef GAME_BULLET_H
#define GAME_BULLET_H
#include "raylib.h"

void
spawn_bullet(int team, Vector3 position, Vector3 direction);

void
render_bullets(void);

	void
bullet_collision_check(void);
#endif
