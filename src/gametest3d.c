/**
* gametest3d
* @license The MIT License (MIT)
*   @copyright Copyright (c) 2015 EngineerOfLies
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/
#include "simple_logger.h"
#include "shader.h"
#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include "collision.h"
#include "game.h"
#include "weapon.h"
#include "client.h"

void set_camera(Vec3D position, Vec3D rotation);

int main(int argc, char *argv[])
{
	Uint32 start_time;
	int num_frames;
	double eSecs, fps;
	int curMouseX = 0;
	int curMouseY = 0;
	Vec3D cOffset = { 0, -5, 0 };

	SDL_Event events;
	GLuint vao;
	float r = 0;
	GLuint triangleBufferObject;
	char bGameLoopRunning = 1;
	Vec3D cameraPosition = { 0, -10, 0.3 };
	Vec3D cameraRotation = { 90, 0, 0 };
	SDL_Event e;
	Obj *obj, *bgobj;
	Sprite *texture, *bgtext;
	const float triangleVertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.366f, 0.0f, 1.0f,
		-0.5f, -0.366f, 0.0f, 1.0f,
		//next part contains vertex colors
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	}; //we love you vertices!
	entity* player;
	entity* test;
	entity* pickup;
	entity* platform;

	//Server* s_player;
	//Client* s_test;

	//s_player = get_server(0);
	//s_test = get_client(0);

	//server_init(s_player);
	//client_init(s_test);

	lbool rocket_fired = false;
	lbool rocket_fired2 = false;

	init_logger("gametest3d.log");
	if (graphics3d_init(1024, 768, 1, "gametest3d", 33) != 0)
	{
		return -1;
	}
	model_init();
	obj_init();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); //make our vertex array object, we need it to restore state we set after binding it. Re-binding reloads the state associated with it.

	glGenBuffers(1, &triangleBufferObject); //create the buffer
	glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //we're "using" this one now
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); //formatting the data for the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind any buffers

	obj = obj_load("models/cube.obj");
	texture = LoadSprite("models/cube_text.png", 1024, 1024);

	bgobj = obj_load("models/mountainvillage.obj");
	bgtext = LoadSprite("models/mountain_text.png", 1024, 1024);

	game_init();
	InitEntityList();

	//    obj = obj_load("models/mountainvillage.obj");
	player = CreateEntity();
	test = CreateEntity();
	platform = CreateEntity();
	pickup = CreateEntity();

	InitEntity(player, "models/cube.obj", "models/cube_text.png", 1024, 1024);
	InitEntity(test, "models/cube.obj", "models/cube_text.png", 1024, 1024);
	InitEntity(platform, "models/cube.obj", "models/cube_text.png", 1024, 1024);
	InitEntity(pickup, "models/cube.obj", "models/cube_text.png", 1024, 1024);

	num_frames = 0;
	start_time = SDL_GetTicks();

	curMouseX = 0;
	curMouseY = 0;

	vec3d_set(player->position, 0, 0, 0);
	vec3d_set(test->position, 0, 0, 0);
	vec3d_set(platform->position, 5, 5, 0);
	vec3d_set(pickup->position, 5, -5, 0);

	pickup->hb.x = 5;
	pickup->hb.y = -5;
	pickup->hb.z = 0;
	pickup->hb.w = 1;
	pickup->hb.d = 1;
	pickup->hb.h = 1;

	platform->hb.x = 5;
	platform->hb.y = 5;
	platform->hb.z = 0;
	platform->hb.w = 1;
	platform->hb.d = 1;
	platform->hb.h = 1;

	lbool connected = false;

	//server_setup();
	//client_connect(s_player);
	//server_connect();

	/*
	while (!connected)
	{
	if (server_connect())
	{
	connected = true;
	}
	}
	*/

	while (bGameLoopRunning)
	{

		//client_update(test);
		//printf("Player \n \n ");

		//test = server_update(test);
		//player = server_send(player);
		//client_recieve(player);
		//printf("Test \n \n ");


		static entity* rocket;
		static entity* rocket_2;

		++num_frames;
		Uint32 eMS = SDL_GetTicks() - start_time;
		if (eMS)
		{
			eSecs = eMS / 1000.0;
			fps = num_frames / eSecs;
			//printf("Frame Rate: %f\n", fps );
		}

		int mouseX, mouseY;
		int horiz, verti;
		int i;

		if (player->health < 0) player->health = 0;
		if (test->health < 0) test->health = 0;

		i = 0;

		vec3d_cpy(cameraPosition, player->position);
		cameraPosition.y -= 10;
		cameraPosition.z += 3;

		weapon_spawn_collision(player, pickup, WFLAG_ROCKET);

		while (SDL_PollEvent(&events))
		{

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
						if (!rocket_fired)
						{
							rocket = rocket_init(player);
							vec3d_set(rocket->position, player->position.x, player->position.y + 1, player->position.z);
						}
						rocket_fired = true;
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
				if (events.type == SDLK_ESCAPE)
				{
					bGameLoopRunning = false;
				}
			}
			//Player1Pull(events, player, test, rocket_fired);
			//Player2Pull(events, test, player, rocket_fired2);
			if (events.type == SDL_QUIT)
				bGameLoopRunning = false;
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
					//vec3d_add(player->position, player->acceleration, player->position);
					break;
				}
				case SDLK_RIGHT:
				{
					vec3d_set(test->acceleration, 4, 0, 0);
					//vec3d_add(player->position, player->acceleration, player->position);
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
						if (!rocket_fired2)
						{
							rocket_2 = rocket_init(test);
							vec3d_set(rocket_2->position, test->position.x, test->position.y + 1, test->position.z);
						}
						rocket_fired2 = true;
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
				if (events.type == SDLK_ESCAPE)
				{
					bGameLoopRunning = false;
				}
			}
		}

		player->hb.x = player->position.x;
		player->hb.y = player->position.y;
		player->hb.z = player->position.z;

		test->hb.x = test->position.x;
		test->hb.y = test->position.y;
		test->hb.z = test->position.z;

		if (Rect3D_Overlap(player->hb, platform->hb))
		{
			player->jump_flag = ENTITYFLAG_GROUNDED;
			vec3d_set(player->acceleration, 0, 0, 0);
			vec3d_set(player->position, platform->position.x, platform->position.y, platform->position.z + 2);
			printf("Called");
		}
		else if (!Rect3D_Overlap(player->hb, platform->hb) && player->position.z > platform->position.z + 2 &&
			player->jump_flag == ENTITYFLAG_GROUNDED)
		{
			player->jump_flag = ENTITYFLAG_JUMP;
			printf("Called Me");
		}

		if (rocket)
		{
			rocket_fly(rocket, player->position, test->position);

			if (Rect3D_Overlap(rocket->hb, test->hb))
			{
				rocket_touch(rocket, test);
				rocket_fired = false;
			}
			Uint32 eMS = SDL_GetTicks() - start_time;
			if (eMS)
			{
				eSecs = eMS / 1000.0;
				if ((int)eSecs % 30 == 0)
				{
					FreeEntityFromList(rocket);
					rocket_fired = false;
				}
			}
		}
		if (rocket_2)
		{
			rocket_fly(rocket_2, test->position, player->position);

			if (Rect3D_Overlap(rocket_2->hb, player->hb))
			{
				rocket_touch(rocket_2, player);
				rocket_fired2 = false;
			}
			Uint32 eMS = SDL_GetTicks() - start_time;
			if (eMS)
			{
				eSecs = eMS / 1000.0;
				if ((int)eSecs % 30 == 0)
				{
					FreeEntityFromList(rocket);
					rocket_fired = false;
				}
			}
		}


		graphics3d_frame_begin();
		game_update();

		if (player->position.z < 0)
			player->position.z = 0;

		glPushMatrix();
		set_camera(
			cameraPosition,
			cameraRotation);
		if (rocket)
		{
			obj_draw(
				obj,
				rocket->position,
				rocket->rotation,
				vec3d(1, 1, 1),
				vec4d(1, 1, 1, 1),
				texture
				);
		}
		if (rocket_2)
		{
			obj_draw(
				obj,
				rocket_2->position,
				rocket_2->rotation,
				vec3d(1, 1, 1),
				vec4d(1, 1, 1, 1),
				texture
				);
		}
		obj_draw(
			bgobj,
			vec3d(0, 0, 2),
			vec3d(90, 90, 0),
			vec3d(5, 5, 5),
			vec4d(1, 1, 1, 1),
			bgtext
			);


		obj_draw(
			obj,
			player->position,
			player->rotation,
			vec3d(1, 1, 1),
			vec4d(1, 1, 1, 1),
			texture
			);

		obj_draw(
			test->obj,
			test->position,
			test->rotation,
			vec3d(1, 1, 1),
			vec4d(1, 1, 1, 1),
			test->texture
			);
		obj_draw(
			platform->obj,
			platform->position,
			platform->rotation,
			vec3d(1, 1, 1),
			vec4d(1, 1, 1, 1),
			test->texture
			);
		if (pickup)
		{
			obj_draw(
				pickup->obj,
				pickup->position,
				pickup->rotation,
				vec3d(1, 1, 1),
				vec4d(1, 1, 1, 1),
				texture
				);
		}
		if (r > 360)r -= 360;
		glPopMatrix();
		/* drawing code above here! */
		graphics3d_next_frame();
	}
	//client_close();
	//server_close_client();
	//server_close();
	//free(s_player);
	//free(s_test);
	FreeEntityList();
	return 0;
}

void set_camera(Vec3D position, Vec3D rotation)
{
	glRotatef(-rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(-rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(-rotation.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(-position.x,
		-position.y,
		-position.z);
}

/*eol@eof*/