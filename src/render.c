#include "render.h"

void
renderWorld(World* world, Camera* camera)
{
	customBeginMode3D(*camera);
	DrawGrid(100, 1);
	drawPlayer(&world->players[0]);
	drawPlayer(&world->players[1]);
	EndMode3D();
}
