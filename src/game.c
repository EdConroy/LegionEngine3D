#include "game.h"

Game game;
SDL_Event events;

entity*	player;

GList	*it;

// extern: game
int		game_running;

// extern: entity/weapon
extern Vec3D	offset;

// private declarations: camera
int		curMouseX, curMouseY;
Vec3D	camera_position;
Vec3D	camera_rotation;

void game_init()
{
	game.space = NewSpace();
	SpaceSetSteps(game.space, 100);
}
void game_pull(entity* player)
{

}

void game_update()
{
	space_do_step(game.space);
}

