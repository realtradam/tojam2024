#include "render.h"
#include "rlgl.h"

void
renderWorld(World* world, Camera camera)
{
	//Vector3 lookat = camera.target;
	//camera.target = (Vector3){0};
	//camera.position.x -= lookat.x;
	//camera.position.y -= lookat.y;
	//camera.position.z -= lookat.z;
	customBeginMode3D(camera);
	//rlPushMatrix();
	//rlTranslatef(
	//		-lookat.x,
	//		-lookat.y,
	//		-lookat.z
	//		);
	drawPlayer(&world->players[0]);
	drawPlayer(&world->players[1]);

	for(int i = 0; i < 11; ++i){
		//DrawCube((Vector3){i,3,3}, 0.5f, 0.5f, 0.5f, YELLOW);
		//DrawCube((Vector3){i,4,3}, 0.5f, 0.5f, 0.5f, DARKPURPLE);
		//DrawCube((Vector3){i,5,3}, 0.5f, 0.5f, 0.5f, YELLOW);
		//DrawCube((Vector3){i,3,4}, 0.5f, 0.5f, 0.5f, MAGENTA);
		//DrawCube((Vector3){i,4,4}, 0.5f, 0.5f, 0.5f, GREEN);
		DrawCube((Vector3){i,5,4}, 0.5f, 0.5f, 0.5f, MAGENTA);
		DrawLineV((Vector2){i, 0}, (Vector2){i, 10}, BLACK);
		DrawLineV((Vector2){0, i}, (Vector2){10, i}, BLACK);
	}
	//rlPopMatrix();
	EndMode3D();
}
