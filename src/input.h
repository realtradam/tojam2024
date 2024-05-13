#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#ifdef PLATFORM_WEB

typedef
struct
{
	char r;
	char z;
}
joypad_buttons_t;
typedef
struct
{
	char stick_x;
	char stick_y;
}
joypad_inputs_t;

#else

#include <libdragon.h>

#endif

extern joypad_buttons_t pressed_p1;
extern joypad_buttons_t held_p1;
extern joypad_inputs_t inputs_p1;

extern joypad_buttons_t pressed_p2;
extern joypad_buttons_t held_p2;
extern joypad_inputs_t inputs_p2;

void updateController(void);

#endif
