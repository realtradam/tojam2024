
#include <stdio.h>
#include "second.h"
#include <raylib.h>

void test(void)
{
	//TraceLog(3, "Test Worked\n");
	for(float i = -2; i <= 2; ++i)
	{
		for(float j = -2; j <= 2; ++j)
		{
			//DrawCubeTexture(texture, (Vector3){ i, 0.0f, j }, 1.0f, 1.0f, 1.0f, WHITE);
			DrawCube((Vector3){ i, 0.0f, j }, 0.5f, 0.5f, 0.5f, RED);             
		}
	}
}
