#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include <libdragon.h>

extern joypad_buttons_t pressed_p1;
extern joypad_buttons_t held_p1;
extern joypad_inputs_t inputs_p1;

void updateController(void);

#endif
