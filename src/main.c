#ifdef PLATFORM_WEB
#include <stdio.h>
#else
#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <raylib.h>
#include <rlgl.h>

#ifdef PLATFORM_WEB
#include <math.h>
#else
#include <fmath.h>
#endif

#define ATTR_NINTENDO64_WIDTH 320
#define ATTR_NINTENDO64_HEIGHT 240
bool flag=true;
bool xflag=false;

#include "player.h"
#include "input.h"
#include "render.h"
#include "world.h"
#include "bullet.h"

Camera camera = { 0 };
Camera camera2 = { 0 };

#ifdef PLATFORM_WEB

#else
bool initApp()
{
	return true;
}
void finishApp()
{


}

Rectangle src={0.0f,0.0f,5.0f,10.0f};
Rectangle dst={0.0f,0.0f,32.0f,32.0f};
#endif

World world = {
	.players = {
		{ 
			.position = { 0 },
			.direction = { 1, 0, 0 },
			.speed = 1.0f/25.0f,
			.color = DARKBLUE,
			.camera_mode = 1,
		},
		{
			.position = { 2, 0, 0 },
			.direction = { -1, 0, 0 },
			.speed = 1.0f/30.0f,
			.color = DARKPURPLE,
			.camera_mode = 1,
		}
	}
};


int main(void)
{
	const int screenWidth = ATTR_NINTENDO64_WIDTH;
	const int screenHeight = ATTR_NINTENDO64_HEIGHT;


	InitWindow(screenWidth, screenHeight, "CubeSpace64");

	camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	camera2.position = (Vector3){ 1.0f, -10.0f, 5.0f };
	camera2.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera2.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera2.fovy = 35.0f;
	camera2.projection = CAMERA_PERSPECTIVE;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		updateController();

		char p1_cam = pressed_p1.r;
		char p2_cam = pressed_p2.r;
		char p1_shoot = pressed_p1.z;
		char p2_shoot = pressed_p2.z;

		if(p1_cam)
		{
			if(world.players[0].camera_mode == 0)
			{
				world.players[0].camera_mode = 1;
			}
			else
			{
				world.players[0].camera_mode = 0;
			}
		}

		if(p2_cam)
		{
			if(world.players[1].camera_mode == 0)
			{
				world.players[1].camera_mode = 1;
			}
			else
			{
				world.players[1].camera_mode = 0;
			}
		}

		if(p1_shoot)
		{
			spawn_bullet(1, world.players[0].position, world.players[0].direction);
		}
		if(p2_shoot)
		{
			spawn_bullet(2, world.players[1].position, world.players[1].direction);
		}
		bullet_collision_check();

		movePlayers();
		camera = lookThroughPlayer(camera, world.players[0]);
		camera2 = lookThroughPlayer(camera2, world.players[1]);

		BeginDrawing();

		ClearBackground(BLACK);
		BeginScissorMode(0, 0, 320/2, 240);
		rlViewport(0, 0, 320/2, 240);
		renderWorld(&world, camera);
		EndScissorMode();
		BeginScissorMode(320/2, 0, 320/2, 240);
		rlViewport(320/2, 0, 320/2, 240);
		renderWorld(&world, camera2);
		EndScissorMode();
		rlViewport(0, 0, 320, 240);
		DrawRectangle((320/2)-4, 0, 2, 240, DARKGRAY); // split screen line

		char text[50];
		sprintf(text, "Player1: %d", world.players[0].points); 
		DrawText(text, 50, 30, 12, BLUE);
		sprintf(text, "Player2: %d", world.players[1].points); 
		DrawText(text, 210, 30, 12, VIOLET);
		DrawFPS(10, 10);

		EndDrawing();
	}
	CloseWindow(); 

#ifdef PLATFORM_WEB

#else
	finishApp();
#endif
	return 0;
}
