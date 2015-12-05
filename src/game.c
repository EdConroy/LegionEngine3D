#include "game.h"
#include "stdio.h"

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

void game_load(entity* f, long character)
{
	char* filepath;
	if (character == FIGHT_STRIDER)
	{
		filepath = "fighters/StriderData.txt";
	}
	char buffer[255];
	FILE* pFile = NULL;
	pFile = fopen(filepath, "r");
	if (!pFile)
	{
		fprintf("character file not found: ", filepath);
		return;
	}
	if (fscanf(pFile, "%s", buffer))
	{
		if (strcmp(buffer, "health:") == 0)
		{
			fscanf(pFile, "%i", &f->health);
			fscanf(pFile, "%s", buffer);
		}
	}
	fclose(pFile);
}
/* Allows the user to edit the data of any fighter */
int game_edit()
{
	unsigned int value = 0;

	unsigned int health = 0;
	unsigned int light = 0;
	unsigned int medium = 0;
	unsigned int heavy = 0;
	unsigned int launcher = 0;
	unsigned int light_knb = 0;
	unsigned int med_knb = 0;
	unsigned int hev_knb = 0;

	fprintf(stdout, "Do you want to edit a fighter?\n 1 = no\n 0 = yes\n");
	scanf("%d", &value);
	if (value != 0)
	{
		return 1;
	}
	fprintf(stdout, "What fighter do you want to edit?:\n 1 - Strider\n 2 - Doom\n 3 - Magneto\n 4 - MegaMan\n 5 - Sentinel\n");
	scanf("%d", &value);
	char* filepath;
	if (value == 1)
	{
		filepath = "fighters/StriderData.txt";
	}
	else if (value == 2)
	{
		filepath = "fighters/DoomData.txt";
	}
	else if (value == 3)
	{
		filepath = "fighters/MegaManData.txt";
	}
	else if (value == 4)
	{
		filepath = "fighters/MagnetoData.txt";
	}
	else if (value == 5)
	{
		filepath = "fighters/SentinelData.txt";
	}
	else
	{
		printf("Invalid Selection");
	}
	FILE* pFile = NULL;
	pFile = fopen(filepath, "w+");
	if (!pFile)
	{
		fprintf(stdout, "character file not found: ", filepath);
		return 1;
	}
	fprintf(stdout, "Health: \n");
	scanf("%d", &health);

	fprintf(stdout, "Light: \n");
	scanf("%d", &light);

	fprintf(stdout, "Medium: \n");
	scanf("%d", &medium);

	fprintf(stdout, "Heavy: \n");
	scanf("%d", &heavy);

	fprintf(stdout, "Launch: \n");
	scanf("%d", &launcher);

	fprintf(stdout, "Light Knockback: \n");
	scanf("%d", &light_knb);

	fprintf(stdout, "Medium Knockback: \n");
	scanf("%d", &med_knb);

	fprintf(stdout, "Heavy Knockback: \n");
	scanf("%d", &hev_knb);

	fprintf(pFile, "health: %d", health);
	fprintf(pFile, "\n");
	fprintf(pFile, "light: %d", light);
	fprintf(pFile, "\n");
	fprintf(pFile, "medium: %d", medium);
	fprintf(pFile, "\n");
	fprintf(pFile, "heavy: %d", heavy);
	fprintf(pFile, "\n");
	fprintf(pFile, "launcher: %d", launcher);
	fprintf(pFile, "\n");
	fprintf(pFile, "lightknockback: %d", launcher);
	fprintf(pFile, "\n");
	fprintf(pFile, "mediumknockback: %d", launcher);
	fprintf(pFile, "\n");
	fprintf(pFile, "heavyknockback: %d", launcher);
	fprintf(pFile, "\n");
	fprintf(stdout, "Done!\n");

	fclose(pFile);

	return 0;
}