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
void game_pull1(entity* player, entity* test, entity* rocket)
{
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_w:
			{
				vec3d_set(player->acceleration, 0, 4, 0);
				break;
			}
			case SDLK_s:
			{
				vec3d_set(player->acceleration, 0, -4, 0);
				break;
			}
			case SDLK_a:
			{
				vec3d_set(player->acceleration, -4, 0, 0);
				break;
			}
			case SDLK_d:
			{
				vec3d_set(player->acceleration, 4, 0, 0);
				break;
			}
			case SDLK_f:
			{
				vec3d_set(player->acceleration, 0, 0, 10);
				player->jump_flag = ENTITYFLAG_GROUNDED;
				break;
			}
			case SDLK_g:
			{
				if (player->weapon_flag == WFLAG_KNIFE) printf("Current Weapon Flag: KNIFE\n");
				else if (player->weapon_flag == WFLAG_RIFLE) printf("Current Weapon Flag: RIFLE\n");
				else if (player->weapon_flag == WFLAG_ROCKET) printf("Current Weapon Flag: ROCKET\n");
				break;
			}
			case SDLK_q:
			{
				if (player->weapon_flag == WFLAG_RIFLE)
				{
					player->weapon_flag = WFLAG_KNIFE;
					printf("Current Weapon Flag: Knife \n");
				}
				else if (player->weapon_flag == WFLAG_ROCKET)
				{
					player->weapon_flag = WFLAG_RIFLE;
					printf("Current Weapon Flag: Rifle \n");
				}
				break;
			}
			case SDLK_e:
			{
				if (player->weapon_flag == WFLAG_KNIFE)
				{
					player->weapon_flag = WFLAG_RIFLE;
					printf("Current Weapon Flag: Rifle \n");
				}
				else if (player->weapon_flag == WFLAG_RIFLE)
				{
					player->weapon_flag = WFLAG_ROCKET;
					printf("Current Weapon Flag: Rocket \n");
				}
				break;
			}
			case SDLK_SPACE:
			{
				if (player->weapon_flag == WFLAG_ROCKET)
				{
					if (!player->rocket_fired)
					{
						rocket = rocket_init(player);
						vec3d_set(rocket->position, player->position.x, player->position.y + 1, player->position.z);
					}
					player->rocket_fired = true;
				}
				else if (player->weapon_flag == WFLAG_KNIFE)
					use_knife(player, test);
				else if (player->weapon_flag == WFLAG_RIFLE)
				{
					printf("Start \n");
					Vec3 v0;
					Vec3 v1;
					Vec3d_set(v0, player->position.x, player->position.y, player->position.z);
					Vec3d_set(v1, player->position.x, player->position.y + 100, player->position.z);
					printf("Line Box pending \n");
					fire_weapon(player, test, v0, v1, 25, 0);
					printf("Cool \n");
				}
				printf("Enemy Health: %i\n", test->health);
				printf("My Health: %i\n", player->health);
				break;
			}
			}
		}

		if (events.type == SDL_KEYUP)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_w:
			{
				player->acceleration.y = 0;
				break;
			}
			case SDLK_s:
			{
				player->acceleration.y = 0;
				break;
			}
			case SDLK_a:
			{
				player->acceleration.x = 0;
				break;
			}
			case SDLK_d:
			{
				player->acceleration.x = 0;
				break;
			}
			case SDLK_f:
			{
				player->acceleration.z = 0;
				player->jump_flag = ENTITYFLAG_JUMP;
				break;
			}
			}
		}
	}
}
void game_pull2(entity* test, entity* player, entity* rocket_2)
{
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
				case SDLK_UP:
				{
					vec3d_set(test->acceleration, 0, 4, 0);
					break;
				}
				case SDLK_DOWN:
				{
					vec3d_set(test->acceleration, 0, -4, 0);
					//vec3d_add(player->position, player->acceleration, player->position);
					break;
				}
				case SDLK_LEFT:
				{
					vec3d_set(test->acceleration, -4, 0, 0);
					break;
				}
				case SDLK_RIGHT:
				{
					vec3d_set(test->acceleration, 4, 0, 0);
					break;
				}
				case SDLK_z:
				{
					if (test->weapon_flag == WFLAG_RIFLE)
					{
						test->weapon_flag = WFLAG_KNIFE;
						printf("Current Weapon Flag: Knife \n");
					}
					else if (test->weapon_flag == WFLAG_ROCKET)
					{
						test->weapon_flag = WFLAG_RIFLE;
						printf("Current Weapon Flag: Rifle \n");
					}
					break;
				}
				case SDLK_c:
				{
					if (test->weapon_flag == WFLAG_KNIFE)
					{
						test->weapon_flag = WFLAG_RIFLE;
						printf("Current Weapon Flag: Rifle \n");
					}
					else if (test->weapon_flag == WFLAG_RIFLE)
					{
						test->weapon_flag = WFLAG_ROCKET;
						printf("Current Weapon Flag: Rocket \n");
					}
					break;
				}
				case SDLK_F11:
				{
					if (test->weapon_flag == WFLAG_ROCKET)
					{
						if (!test->rocket_fired)
						{
							rocket_2 = rocket_init(test);
							vec3d_set(rocket_2->position, test->position.x, test->position.y + 1, test->position.z);
						}
						test->rocket_fired = true;
					}
					else if (test->weapon_flag == WFLAG_KNIFE)
						use_knife(test, player);
					else if (test->weapon_flag == WFLAG_RIFLE)
					{
						printf("Start \n");
						Vec3 v0;
						Vec3 v1;
						Vec3d_set(v0, test->position.x, test->position.y, test->position.z);
						Vec3d_set(v1, test->position.x, test->position.y + 100, test->position.z);
						printf("Line Box pending \n");
						fire_weapon(test, player, v0, v1, 25, 0);
						printf("Cool \n");
					}
					printf("Enemy Health: %i\n", player->health);
					break;
				}
			}
		}

		if (events.type == SDL_KEYUP)
		{
			switch (events.key.keysym.sym)
			{
				case SDLK_UP:
				{
					test->acceleration.y = 0;
					break;
				}
				case SDLK_DOWN:
				{
					test->acceleration.y = 0;
					break;
				}
				case SDLK_LEFT:
				{
					test->acceleration.x = 0;
					break;
				}
				case SDLK_RIGHT:
				{
					test->acceleration.x = 0;
					break;
				}
			}
		}
	}
}
void game_update()
{
	space_do_step(game.space);
}

