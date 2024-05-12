#include "input.h"

joypad_buttons_t pressed_p1;
joypad_buttons_t held_p1;
joypad_inputs_t inputs_p1;

joypad_buttons_t pressed_p2;
joypad_buttons_t held_p2;
joypad_inputs_t inputs_p2;

void updateController()
{
    joypad_poll();
    pressed_p1 = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    held_p1 = joypad_get_buttons_held(JOYPAD_PORT_1);
    inputs_p1 = joypad_get_inputs(JOYPAD_PORT_1);
    pressed_p2 = joypad_get_buttons_pressed(JOYPAD_PORT_2);
    held_p2 = joypad_get_buttons_held(JOYPAD_PORT_2);
    inputs_p2 = joypad_get_inputs(JOYPAD_PORT_2);


	float x = inputs_p1.stick_x;
	float y = inputs_p1.stick_y;

	if(x > 60)
	{
		x = 60.0f;
	}
	else if(x < -60)
	{
		x = -60.0f;
	}
	else if((x > -5) && (x < 5))
	{
		x = 0.0f;
	}

	if(y > 60)
	{
		y = 60;
	}
	else if(y < -60)
	{
		y = -60;
	}
	else if((y > -5) && (y < 5))
	{
		y = 0;
	}

	if(x > 0)
	{
		x -= 5;
	}
	else if(x < 0)
	{
		x += 5;
	}

	if(y > 0)
	{
		y -= 5;
	}
	else if(y < 0)
	{
		y += 5;
	}

	//float distance = sqrtf((x * x) + (y * y));

	//char text[500];
	//char text2[500];
	//char text3[500];
	//sprintf(text, "x %f", x); 
	//sprintf(text2, "y %f", y); 
	//sprintf(text3, "d %f", distance); 
	//DrawText(text, 100, 10, 12, GREEN);
	//DrawText(text2, 100, 30, 12, GREEN);
	//DrawText(text3, 100, 60, 12, GREEN);

	/*
	if(distance != 0)
	{
		inputs_p1.stick_x = (x / distance) * 127.0f;
		inputs_p1.stick_y = (y / distance) * 127.0f;
	}
	*/

	inputs_p1.stick_x = x / 55.0f * 127.0f;
	inputs_p1.stick_y = y / 55.0f * 127.0f;

	x = inputs_p2.stick_x;
	y = inputs_p2.stick_y;

	if(x > 60)
	{
		x = 60.0f;
	}
	else if(x < -60)
	{
		x = -60.0f;
	}
	else if((x > -5) && (x < 5))
	{
		x = 0.0f;
	}

	if(y > 60)
	{
		y = 60;
	}
	else if(y < -60)
	{
		y = -60;
	}
	else if((y > -5) && (y < 5))
	{
		y = 0;
	}

	if(x > 0)
	{
		x -= 5;
	}
	else if(x < 0)
	{
		x += 5;
	}

	if(y > 0)
	{
		y -= 5;
	}
	else if(y < 0)
	{
		y += 5;
	}

	inputs_p2.stick_x = x / 55.0f * 127.0f;
	inputs_p2.stick_y = y / 55.0f * 127.0f;
}
