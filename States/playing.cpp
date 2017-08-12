#include "playing.h"
#include "../Entities/entity.h"

Playing Playing::playingState;

Playing::Playing() { }

void Playing::initialize()
{
	events.Register("R_X-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		printf("Events!\n");
	});

	events.Register("R_Y-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		printf("Events!\n");
	});

	loader.setInternalPath("cube");
	loader.loadFromObj(ab);
}

void Playing::cleanup()
{
}

void Playing::pause()
{
}

void Playing::resume()
{
}

void Playing::handleEvents(Application * app)
{
	static int x = 0, y = 0;
	static float scale = 1.0f;
	char* data = (char*)malloc(sizeof(int) * 2); //Data buffer for x and y coordinates

	memcpy(data, &x, sizeof(int));
	memcpy(data + sizeof(int), &y, sizeof(int));


	int up = glfwGetKey(app->rWindow(), GLFW_KEY_UP);
	int down = glfwGetKey(app->rWindow(), GLFW_KEY_DOWN);
	int left = glfwGetKey(app->rWindow(), GLFW_KEY_LEFT);
	int right = glfwGetKey(app->rWindow(), GLFW_KEY_RIGHT);

	if (up == GLFW_PRESS)
	{
		events.Trigger("R_X-Axis", data);
		x += 20;
	}
	else if (down == GLFW_PRESS)
	{
		events.Trigger("R_X-Axis", data);
		x -= 20;
	}
	if (left == GLFW_PRESS)
	{
		events.Trigger("R_Y-Axis", data);
		y += 20;
	}
	else if (right == GLFW_PRESS)
	{
		events.Trigger("R_Y-Axis", data);
		y -= 20;
	}

	if (glfwWindowShouldClose(app->rWindow()))
	{
		app->quit();
	}
}

void Playing::update(Application * app)
{
}

void Playing::draw(Application * app)
{
}
