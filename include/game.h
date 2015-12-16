#include <glib.h>
#include "weapon.h"

typedef struct GameData_T
{
	space* space;

}Game;

void game_init();
void game_pull1(entity* player, entity* test, entity* rocket);
void game_pull2(entity* test, entity* player, entity* rocket_2);
void game_update();
void game_draw();
void game_load(entity* f, long character);
int game_edit();