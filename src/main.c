/*******************************************************************************************
 *
 *   raylib [models] example - Draw textured cube
 *
 *   Example originally created with raylib 4.5, last time updated with raylib 4.5
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2022-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/


#include <libdragon.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <raylib.h>
#include <rlgl.h>
#include <fmath.h>
//#include "raylib_font_RGBA16_5551.h"
#define ATTR_NINTENDO64_WIDTH 320
#define ATTR_NINTENDO64_HEIGHT 240
bool flag=true;
bool xflag=false;

#include "player.h"
#include "input.h"
#include "render.h"
#include "world.h"

Camera camera = { 0 };
Camera camera2 = { 0 };

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color); // Draw cube textured
void DrawCubeTextureRec(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, Color color); // Draw cube with a region of a texture



bool initApp()
{
	return true;
}
void finishApp()
{


}
extern Texture2D getFontGLTextureId(char *text);
Rectangle src={0.0f,0.0f,5.0f,10.0f};
Rectangle dst={0.0f,0.0f,32.0f,32.0f};


World world = {
	.players = {
		{ 
			.position = { 0 },
			.direction = { 1, 0, 0 },
			.speed = 1.0f/60.0f,
			.color = BLUE,
		},
		{
			.position = { 2, 0, 0 },
			.direction = { -1, 0, 0 },
			.speed = 1.0f/60.0f,
			.color = RED,
		}
	}
};


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = ATTR_NINTENDO64_WIDTH;
	const int screenHeight = ATTR_NINTENDO64_HEIGHT;


	InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes");

	// Define the camera to look into our 3d world
	camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	// Define the camera to look into our 3d world
	camera2.position = (Vector3){ 1.0f, -10.0f, 5.0f };
	camera2.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera2.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera2.fovy = 35.0f;
	camera2.projection = CAMERA_PERSPECTIVE;


	Texture2D texture = LoadTexture("rom:/cubicmap_atlas32x32.png");    // Load map texture
																			   //Model model = LoadModel("rom:/plane.m3d");


	//BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);   // Set model bounds



	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
									//----------------------------------------------------------

									// Main game loop
	while (flag)    // Detect window close with Start button
	{
		// Update
		//-----------------------------------------------------
		//controller_read(&controllers);

		movePlayers();
		camera = lookThroughPlayer(camera, world.players[0], world.players[1]);

		// Update
		//----------------------------------------------------------------------------------
		//UpdateCamera(&camera, CAMERA_ORBITAL);
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(DARKGRAY);

		BeginScissorMode(0, 0, 320/2, 240);
		rlViewport(0, 0, 320/2, 240);
		renderWorld(&world, camera);
		EndScissorMode();
		BeginScissorMode(320/2, 0, 320/2, 240);
		rlViewport(320/2, 0, 320/2, 240);
		renderWorld(&world, camera2);
		EndScissorMode();
		rlViewport(0, 0, 320, 240);

		// Draw cube with an applied texture
		//test();
		// Draw cube with an applied texture, but only a defined rectangle piece of the texture
		//DrawCubeTextureRec(texture, (Rectangle){ 0, texture.height/2, texture.width/2, texture.height/2 }, 
		//    (Vector3){ 2.0f, 1.0f, 0.0f }, 2.0f, 2.0f, 2.0f, WHITE);
		
		updateController();

		char text[50];
		sprintf(text, "Joystick %d,%d", inputs_p1.stick_x, inputs_p1.stick_y); 
		DrawText(text, 10, 30, 12, GREEN);
		DrawFPS(10, 10);

		EndDrawing();



		//-----------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(texture);     // Unload map texture

	CloseWindow();        // Close window and OpenGL context
						  //----------------------------------------------------------

	finishApp();
	return 0;
}
void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
	float x = position.x;
	float y = position.y;
	float z = position.z;

	// Set desired texture to be enabled while drawing following vertex data
	rlSetTexture(texture.id);

	// Vertex data transformation can be defined with the commented lines,
	// but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
	//rlPushMatrix();
	// NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
	//rlTranslatef(2.0f, 0.0f, 0.0f);
	//rlRotatef(45, 0, 1, 0);
	//rlScalef(2.0f, 2.0f, 2.0f);

	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);
	// Front Face
	rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
																						   // Back Face
	rlNormal3f(0.0f, 0.0f, - 1.0f);     // Normal Pointing Away From Viewer
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
																						   // Top Face
	rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
																						   // Bottom Face
	rlNormal3f(0.0f, - 1.0f, 0.0f);     // Normal Pointing Down
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
																						   // Right face
	rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
																						   // Left Face
	rlNormal3f( - 1.0f, 0.0f, 0.0f);    // Normal Pointing Left
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
	rlEnd();
	//rlPopMatrix();

	rlSetTexture(0);
}

// Draw cube with texture piece applied to all faces
void DrawCubeTextureRec(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, Color color)
{
	float x = position.x;
	float y = position.y;
	float z = position.z;
	float texWidth = (float)texture.width;
	float texHeight = (float)texture.height;

	// Set desired texture to be enabled while drawing following vertex data
	rlSetTexture(texture.id);

	// We calculate the normalized texture coordinates for the desired texture-source-rectangle
	// It means converting from (tex.width, tex.height) coordinates to [0.0f, 1.0f] equivalent 
	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);

	// Front face
	rlNormal3f(0.0f, 0.0f, 1.0f);
	rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x - width/2, y - height/2, z + length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x + width/2, y - height/2, z + length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
	rlVertex3f(x + width/2, y + height/2, z + length/2);
	rlTexCoord2f(source.x/texWidth, source.y/texHeight);
	rlVertex3f(x - width/2, y + height/2, z + length/2);

	// Back face
	rlNormal3f(0.0f, 0.0f, - 1.0f);
	rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x - width/2, y - height/2, z - length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
	rlVertex3f(x - width/2, y + height/2, z - length/2);
	rlTexCoord2f(source.x/texWidth, source.y/texHeight);
	rlVertex3f(x + width/2, y + height/2, z - length/2);
	rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x + width/2, y - height/2, z - length/2);

	// Top face
	rlNormal3f(0.0f, 1.0f, 0.0f);
	rlTexCoord2f(source.x/texWidth, source.y/texHeight);
	rlVertex3f(x - width/2, y + height/2, z - length/2);
	rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x - width/2, y + height/2, z + length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x + width/2, y + height/2, z + length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
	rlVertex3f(x + width/2, y + height/2, z - length/2);

	// Bottom face
	rlNormal3f(0.0f, - 1.0f, 0.0f);
	rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
	rlVertex3f(x - width/2, y - height/2, z - length/2);
	rlTexCoord2f(source.x/texWidth, source.y/texHeight);
	rlVertex3f(x + width/2, y - height/2, z - length/2);
	rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x + width/2, y - height/2, z + length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x - width/2, y - height/2, z + length/2);

	// Right face
	rlNormal3f(1.0f, 0.0f, 0.0f);
	rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x + width/2, y - height/2, z - length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
	rlVertex3f(x + width/2, y + height/2, z - length/2);
	rlTexCoord2f(source.x/texWidth, source.y/texHeight);
	rlVertex3f(x + width/2, y + height/2, z + length/2);
	rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x + width/2, y - height/2, z + length/2);

	// Left face
	rlNormal3f( - 1.0f, 0.0f, 0.0f);
	rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x - width/2, y - height/2, z - length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
	rlVertex3f(x - width/2, y - height/2, z + length/2);
	rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
	rlVertex3f(x - width/2, y + height/2, z + length/2);
	rlTexCoord2f(source.x/texWidth, source.y/texHeight);
	rlVertex3f(x - width/2, y + height/2, z - length/2);

	rlEnd();

	rlSetTexture(0);
}
