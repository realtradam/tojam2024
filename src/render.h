#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "raylib.h"
#include "rlgl.h"
#include "world.h"

GLuint
customLoadTextureN64(char *spritePath);

void
renderSkybox(GLuint *textures, int m, int n, Camera3D camera);

void
renderWorld(World* world, Camera camera);

#endif

