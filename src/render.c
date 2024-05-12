#include "render.h"
#include "rlgl.h"

void
drawLine(Vector3 start, Vector3 end, float width, int up, Color color)
{
	start.x *= 100;
	start.y *= 100;
	start.z *= 100;
	end.x *= 100;
	end.y *= 100;
	end.z *= 100;
	width *= 2;
	// 2 is z up for some reason /shrug
	int ox = 0;
	int oy = 0;
	int oz = 0;

	if(up == 1)
	{
		ox = (width / 2);
	}
	else if(up == 2)
	{
		oy = (width / 2);
	}
	else if(up == 3)
	{
		oz = (width / 2);
	}
	else if(up == -1)
	{
		ox = -(width / 2);
	}
	else if(up == -2)
	{
		oy = -(width / 2);
	}
	else if(up == -3)
	{
		oz = -(width / 2);
	}


	Vector3 points[4] = {
		(Vector3){ (start.x + ox) * 1, (start.y + oy) * 1, (start.z + oz) * 1 },
		(Vector3){ (start.x - ox) * 1, (start.y - oy) * 1, (start.z - oz) * 1 },
		(Vector3){ (end.x + ox) * 1, (end.y + oy) * 1, (end.z + oz) * 1 },
		(Vector3){ (end.x - ox) * 1, (end.y - oy) * 1, (end.z - oz) * 1 },
	};

	//Vector3 points[4] = {
	//	(Vector3){ 0, 0, 0 },
	//	(Vector3){ 10, 0, 0 },
	//	(Vector3){ 0, 10, 0 },
	//	(Vector3){ 10, 10, 0 },
	//};
	rlPushMatrix();
	rlScalef(0.01, 0.01, 0.01);
	DrawTriangleStrip3D(points, 4, color);
	rlPopMatrix();
}

void
drawGrid(Vector3 position, int lines, int size, Color color)
{
	position.x -= lines * size / 2;
	position.y -= lines * size / 2;
	for(int i = 0; i < lines + 1; ++i)
	{
		float mx = position.x;
		float my = position.y + (i * size);
		float mz = position.z;
		drawLine(
				(Vector3){
				mx,
				my,
				mz
				},
				(Vector3){
				mx + (size * lines),
				my,
				mz
				},
				4.0f,
				2,
				BLACK);
	}
	for(int i = 0; i < lines + 1; ++i)
	{
		float mx = position.x + (i * size);
		float my = position.y;
		float mz = position.z;
		drawLine(
				(Vector3){
				mx,
				my,
				mz
				},
				(Vector3){
				mx,
				my + (size * lines),
				mz
				},
				4.0f,
				-1,
				BLACK);
	}
}

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

	//drawGrid((Vector3){0}, 10, 1);

	for(int i = -3; i <= 3; ++i){
		DrawCube((Vector3){i,3,3}, 0.5f, 0.5f, 0.5f, YELLOW);
		DrawCube((Vector3){i,4,3}, 0.5f, 0.5f, 0.5f, DARKPURPLE);
		//DrawCube((Vector3){i,5,3}, 0.5f, 0.5f, 0.5f, YELLOW);
		//DrawCube((Vector3){i,3,4}, 0.5f, 0.5f, 0.5f, MAGENTA);
		//DrawCube((Vector3){i,4,4}, 0.5f, 0.5f, 0.5f, GREEN);
		//DrawCube((Vector3){i,5,4}, 0.5f, 0.5f, 0.5f, MAGENTA);
		//DrawLineEx((Vector2){i, 3},(Vector2){i, -3},  5, BLACK);
		//DrawLineEx((Vector2){3, i},(Vector2){-3, i},  5, BLACK);
	}
	//drawLine((Vector3){0}, (Vector3){10,0,0}, 2.0f, 2, BLACK);

	drawGrid((Vector3){0}, 10, 1, BLACK);

	//rlPopMatrix();
	EndMode3D();
}
