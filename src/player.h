#include "raylib.h"

typedef
struct
{
	Vector3 position;
	Vector3 direction;
	float speed;

}
Player;

void
drawPlayer(Player *player);
