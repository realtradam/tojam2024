#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include <libdragon.h>

extern joypad_buttons_t pressed_p1;
extern joypad_buttons_t held_p1;
extern joypad_inputs_t inputs_p1;

extern joypad_buttons_t pressed_p2;
extern joypad_buttons_t held_p2;
extern joypad_inputs_t inputs_p2;

void updateController(void);

#endif
