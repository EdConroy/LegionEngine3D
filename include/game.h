#include <glib.h>
#include "entity.h"

typedef struct GameData_T
{
	space* space;

}Game;

void game_init();
void game_pull(entity* player);
void game_update();
void game_draw();
void game_load(entity* f, long character);
int game_edit();