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

	lbool rocket_fired = false;

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

	InitEntity(player, "models/cube.obj", "models/cube_text.png", 1024, 1024);
	InitEntity(test, "models/cube.obj", "models/cube_text.png", 1024, 1024);

	num_frames = 0;
	start_time = SDL_GetTicks();

	curMouseX = 0;
	curMouseY = 0;

	vec3d_set(player->position, 0, 0, 0);
	vec3d_set(test->position, 0, 0, 0);

	while (bGameLoopRunning)
	{
		static entity* rocket;
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

		i = 0;
		
		vec3d_cpy(cameraPosition, player->position);
		cameraPosition.y -= 10;
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
						use_knife(player, test);
					}
					case SDLK_SPACE:
					{
						if (!rocket_fired)
						{
							rocket = rocket_init(player);
							vec3d_set(rocket->position, player->position.x, player->position.y + 1, player->position.z);
						}
						rocket_fired = true;
						//use_knife(player, test);
						printf("Enemy Health: %i\n", test->health);
						/*
						printf("Start \n");
						Cube sample;
						Vec3d_set(sample.bounding.vmax, 1, 1, 1);
						Vec3d_set(sample.bounding.vmin, -1, -1, -1);
						sample.x = 0;
						sample.y = 0;
						sample.z = 0;
						Vec3 v0;
						Vec3 v1;
						Vec3d_set(v0, 2, 0, 3);
						Vec3d_set(v1, -2, 0, -3);
						printf("Line Box pending \n");
						LineBoxOverlap(sample.bounding, v0, v1);
						printf("Cool \n");
						*/
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
			}

			if (events.type == SDL_MOUSEMOTION)
			{
				//mouseOnCamera();

				SDL_GetMouseState(&mouseX, &mouseY);

				// get new positions
				// highly inaccurate
				horiz = ((((curMouseX - mouseX)) + (1024 / 2)));
				verti = ((curMouseY - mouseY) - (768 / 2)) * .8;

				// set new positions
				//player->rotation.z = horiz;
				//player->rotation.x = verti;

				// clamping
				/*
				if (player->rotation.x <= -650)
					player->rotation.x = -650;
				if (player->rotation.x >= -610)
					player->rotation.x = -610;
				*/
				//if (player->rot.z >= -300)
				//player->rot.z = -300;
				//if (player->rot.z <= -400)
				//player->rot.z = -400;

				// save old positions
				curMouseX = mouseX;
				curMouseY = mouseY;
			}
			if (events.type == SDLK_ESCAPE)
			{
				bGameLoopRunning = false;
			}
		}
		player->hb.x = player->position.x;
		player->hb.y = player->position.y;
		player->hb.z = player->position.z;

		if (rocket)
		{
			rocket_fly(rocket, player->position, test->position);

			if (Rect3D_Overlap(rocket->hb, test->hb))
			{
				rocket_touch(rocket, test);
				rocket_fired = false;
			}
			if ((int)eSecs % 30 == 0)
			{
				FreeEntityFromList(rocket);
				rocket_fired = false;
			}
		}
		
		graphics3d_frame_begin();
		game_update();

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
		if (r > 360)r -= 360;
		glPopMatrix();
		/* drawing code above here! */
		graphics3d_next_frame();
	}
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