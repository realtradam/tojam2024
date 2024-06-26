#include "render.h"
#include "rlgl.h"
#include "bullet.h"

void customBeginMode3D(Camera camera);

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
	position.x += lines * size / 2;
	position.y -= (lines * size / 2);
	rlPushMatrix();
	//rlTranslatef(-(lines * size / 2), -(lines * size / 2), 0);
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
				color);
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
				color);
	}
	rlPopMatrix();
}

void
renderWorld(World* world, Camera camera)
{
	customBeginMode3D(camera);
	drawPlayer(&world->players[0]);
	drawPlayer(&world->players[1]);

	render_bullets();

	int space = 3;

	rlPushMatrix();
	rlTranslatef(0,0,-space);
	drawGrid((Vector3){0}, 5, 1, RAYWHITE);
	rlPopMatrix();

	rlPushMatrix();
	rlTranslatef(0,0,space);
	rlRotatef(180,0,1,0);
	drawGrid((Vector3){0}, 5, 1, GREEN);
	rlPopMatrix();

	rlPushMatrix();
	rlTranslatef(0,space,0);
	rlRotatef(90,1,0,0);
	drawGrid((Vector3){0}, 5, 1, YELLOW);
	rlPopMatrix();

	rlPushMatrix();
	rlRotatef(90,-1,0,0);
	rlTranslatef(0,0,-space);
	drawGrid((Vector3){0}, 5, 1, ORANGE);
	rlPopMatrix();

	EndMode3D();
}
