#include "entity.h"
#include "game.h"

extern Game game;

int entities_used = 0;

entity Entities[MAX_ENTITIES];

/* Initializes the fighter list that holds both of the player characters */
void InitEntityList()
{
	int i;
	for (i = 0; i<MAX_ENTITIES; ++i)
	{
		memset(&Entities[i], 0, sizeof(entity));
	}
}

entity* CreateEntity()
{
	int i;
	for (i = entities_used; i < MAX_ENTITIES; ++i)
	{
		if (getEntity(i))
		{
			entities_used = i + 1;
			return getEntity(i);
		}
		else
			printf("Cannot Create Entity, Max Entities Reached");
	}
	return NULL;
}

/* Gets the location of the fighter from the fighter list and returns the location */
entity * getEntity(int player)
{
	if (player >= MAX_ENTITIES) return NULL;
	return &Entities[player];
}
/* Sets the first player's data */
void InitEntity(entity* e, char* mod_file, char* spr_file, int spr_x, int spr_y)
{
	e->health = 100;

	vec3d_set(e->position, 0, 0, 0);
	vec3d_set(e->velocity, 0, 0, 0);
	vec3d_set(e->rotation, 0, 0, 0);
	
	e->hb.x = e->position.x;
	e->hb.y = e->position.y;
	e->hb.z = e->position.z;
	e->hb.d = 1;
	e->hb.w = 1;
	e->hb.h = 1;
	e->weapon_flag = WFLAG_RIFLE;
	e->jump_flag = ENTITYFLAG_GROUNDED;

	Vec3d_set(e->hb.bounding.vmax, 1, 1, 1);
	Vec3d_set(e->hb.bounding.vmin, -1, -1, -1);
	e->gravity = 5;
	e->obj = obj_load(mod_file);
	e->texture = LoadSprite(spr_file, spr_x, spr_y);
	SpaceAddBody(game.space, &e->body);
	e->body.owner = e;

	e->index = entities_used - 1;
}
/* Frees the memory that is held by the fighter */
void FreeEntity(entity* e)
{
	if (!e)
	{
		return;
	}
	obj_free(e->obj);
	FreeSprite(e->texture);
	e->health = 0;

	vec3d_set(e->position, 0, 0, 0);
	vec3d_set(e->velocity, 0, 0, 0);
	vec3d_set(e->rotation, 0, 0, 0);

	e->hb.x = 0;
	e->hb.y = 0;
	e->hb.z = 0;
	e->hb.d = 0;
	e->hb.w = 0;
	e->hb.h = 0;
	e->weapon_flag = NULL;
	e->jump_flag = NULL;

	Vec3d_set(e->hb.bounding.vmax, 0, 0, 0);
	Vec3d_set(e->hb.bounding.vmin, 0, 0, 0);
	e->gravity = 0;

	SpaceRemoveBody(game.space, &e->body);
	e->body.owner = NULL;

	e = NULL;
	free(e);
}

void FreeEntityList()
{
	int i;
	for (i = 0; i < MAX_ENTITIES; ++i)
	{
		FreeEntity(&Entities[i]);
	}
	entities_used = 0;
}
void FreeEntityFromList(entity* e)
{
	if (&Entities[e->index] == NULL)
		printf("No such entity exists");
	FreeEntity(&Entities[e->index]);
	--entities_used;
}
void Player1Pull(SDL_Event events, entity* player, entity* enemy, lbool rocket_fired, Vec3D cameraPosition)
{
	static entity* rocket;
	Vec3D cOffset = { 0, -5, 0 };

		char bGameLoopRunning = 1;

		if (events.type == SDL_QUIT)
			bGameLoopRunning = false;
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
					//vec3d_add(player->position, player->acceleration, player->position);
					break;
				}
				case SDLK_a:
				{
					vec3d_set(player->acceleration, -4, 0, 0);
					//vec3d_add(player->position, player->acceleration, player->position);
					break;
				}
				case SDLK_d:
				{
					vec3d_set(player->acceleration, 4, 0, 0);
					//vec3d_add(player->position, player->acceleration, player->position);
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
						if (!rocket_fired)
						{
							rocket = rocket_init(player);
							vec3d_set(rocket->position, player->position.x, player->position.y + 1, player->position.z);
						}
						rocket_fired = true;
					}
					else if (player->weapon_flag == WFLAG_KNIFE)
						use_knife(player, enemy);
					else if (player->weapon_flag == WFLAG_RIFLE)
					{
						printf("Start \n");
						Vec3 v0;
						Vec3 v1;
						Vec3d_set(v0, player->position.x, player->position.y, player->position.z);
						Vec3d_set(v1, player->position.x, player->position.y + 100, player->position.z);
						printf("Line Box pending \n");
						fire_weapon(player, enemy, v0, v1, 25, 0);
						printf("Cool \n");
					}
					printf("Enemy Health: %i\n", enemy->health);
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
			}
		if (events.type == SDLK_ESCAPE)
		{
			bGameLoopRunning = false;
		}
	}
}
void Player2Pull(SDL_Event events, entity* player, entity* enemy, lbool rocket_fired, Vec3D cameraPosition)
{
	static entity* rocket2;

	char bGameLoopRunning = 1;

	if (events.type == SDL_QUIT)
		bGameLoopRunning = false;
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
		{
			vec3d_set(player->acceleration, 0, 4, 0);
			break;
		}
		case SDLK_DOWN:
		{
			vec3d_set(player->acceleration, 0, -4, 0);
			//vec3d_add(player->position, player->acceleration, player->position);
			break;
		}
		case SDLK_LEFT:
		{
			vec3d_set(player->acceleration, -4, 0, 0);
			//vec3d_add(player->position, player->acceleration, player->position);
			break;
		}
		case SDLK_RIGHT:
		{
			vec3d_set(player->acceleration, 4, 0, 0);
			//vec3d_add(player->position, player->acceleration, player->position);
			break;
		}
		case SDLK_z:
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
		case SDLK_c:
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
		case SDLK_F11:
		{
			if (player->weapon_flag == WFLAG_ROCKET)
			{
				if (!rocket_fired)
				{
					rocket2 = rocket_init(player);
					vec3d_set(rocket2->position, player->position.x, player->position.y + 1, player->position.z);
				}
				rocket_fired = true;
			}
			else if (player->weapon_flag == WFLAG_KNIFE)
				use_knife(player, enemy);
			else if (player->weapon_flag == WFLAG_RIFLE)
			{
				printf("Start \n");
				Vec3 v0;
				Vec3 v1;
				Vec3d_set(v0, player->position.x, player->position.y, player->position.z);
				Vec3d_set(v1, player->position.x, player->position.y + 100, player->position.z);
				printf("Line Box pending \n");
				fire_weapon(player, enemy, v0, v1, 25, 0);
				printf("Cool \n");
			}
			printf("Enemy Health: %i\n", enemy->health);
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
			player->acceleration.y = 0;
			break;
		}
		case SDLK_DOWN:
		{
			player->acceleration.y = 0;
			break;
		}
		case SDLK_LEFT:
		{
			player->acceleration.x = 0;
			break;
		}
		case SDLK_RIGHT:
		{
			player->acceleration.x = 0;
			break;
		}
		}
		if (events.type == SDLK_ESCAPE)
		{
			bGameLoopRunning = false;
		}
	}
}
void update_rocket(entity* rocket, entity* player, entity* enemy, double time, lbool fired)
{
	if (rocket)
	{
		rocket_fly(rocket, player->position, enemy->position);

		if (Rect3D_Overlap(rocket->hb, enemy->hb))
		{
			rocket_touch(rocket, enemy);
			fired = false;
		}
		if ((int)time % 30 == 0)
		{
			FreeEntityFromList(rocket);
			fired = false;
		}
	}
}
/* Loads the fighter from a text file into the game */
void LoadEntity(entity* e, long character)
{

}
/* Allows the user to edit the data of any fighter */
int EditEntity()
{
	return 0;
}
