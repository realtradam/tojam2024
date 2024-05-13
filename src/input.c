#include "input.h"
#ifdef PLATFORM_WEB
#include "raylib.h"
#include <stdio.h>
#else
#endif

joypad_buttons_t pressed_p1 = {0};
joypad_buttons_t held_p1 = {0};
joypad_inputs_t inputs_p1 = {0};

joypad_buttons_t pressed_p2 = {0};
joypad_buttons_t held_p2 = {0};
joypad_inputs_t inputs_p2 = {0};

void updateController()
{
#ifdef PLATFORM_WEB
	static int previous_x_p1 = 0;
	static int previous_y_p1 = 0;
	static int previous_x_p2 = 0;
	static int previous_y_p2 = 0;

	pressed_p1.z = IsKeyPressed(KEY_E);
	pressed_p1.r = IsKeyPressed(KEY_Q);
	pressed_p2.z = IsKeyPressed(KEY_O);
	pressed_p2.r = IsKeyPressed(KEY_U);

	static int turn_speed = 5;

	if(IsKeyDown(KEY_W))
	{
		previous_y_p1 += turn_speed;
		if(previous_y_p1 > 100)
		{
			previous_y_p1 = 100;
		}
	}
	if(IsKeyDown(KEY_A))
	{
		previous_x_p1 -= turn_speed;
		if(previous_x_p1 < -100)
		{
			previous_x_p1 = -100;
		}
	}
	if(IsKeyDown(KEY_S))
	{
		previous_y_p1 -= turn_speed;
		if(previous_y_p1 < -100)
		{
			previous_y_p1 = -100;
		}
	}
	if(IsKeyDown(KEY_D))
	{
		previous_x_p1 += turn_speed;
		if(previous_x_p1 > 100)
		{
			previous_x_p1 = 100;
		}
	}

	if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
	{
		previous_y_p1 *= 2.0f/3.0f;
	}
	if(!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
	{
		previous_x_p1 *= 2.0f/3.0f;
	}

	if(IsKeyDown(KEY_I))
	{
		previous_y_p2 += turn_speed;
		if(previous_y_p2 > 100)
		{
			previous_y_p2 = 100;
		}
	}
	if(IsKeyDown(KEY_J))
	{
		previous_x_p2 -= turn_speed;
		if(previous_x_p2 < -100)
		{
			previous_x_p2 = -100;
		}
	}
	if(IsKeyDown(KEY_K))
	{
		previous_y_p2 -= turn_speed;
		if(previous_y_p2 < -100)
		{
			previous_y_p2 = -100;
		}
	}
	if(IsKeyDown(KEY_L))
	{
		previous_x_p2 += turn_speed;
		if(previous_x_p2 > 100)
		{
			previous_x_p2 = 100;
		}
	}

	if(!IsKeyDown(KEY_I) && !IsKeyDown(KEY_K))
	{
		previous_y_p2 *= 2.0f/3.0f;
	}
	if(!IsKeyDown(KEY_J) && !IsKeyDown(KEY_L))
	{
		previous_x_p2 *= 2.0f/3.0f;
	}

	inputs_p1.stick_y = previous_y_p1;
	inputs_p1.stick_x = previous_x_p1;

	inputs_p2.stick_y = previous_y_p2;
	inputs_p2.stick_x = previous_x_p2;
#else
    joypad_poll();
    pressed_p1 = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    held_p1 = joypad_get_buttons_held(JOYPAD_PORT_1);
    inputs_p1 = joypad_get_inputs(JOYPAD_PORT_1);
    pressed_p2 = joypad_get_buttons_pressed(JOYPAD_PORT_2);
    held_p2 = joypad_get_buttons_held(JOYPAD_PORT_2);
    inputs_p2 = joypad_get_inputs(JOYPAD_PORT_2);
#endif

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

	inputs_p1.stick_x = x / 55.0f * 127.0f;
	inputs_p1.stick_y = y / 55.0f * 127.0f;

	printf("Input %f\n", x);
	printf("Input %d\n", inputs_p1.stick_x);

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
