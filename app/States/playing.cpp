#include "playing.h"

Playing Playing::playingState;

Playing::Playing() { }

void Playing::initialize()
{
	monkey = new Object(new Model("models/monkey"), new Shader*[2]{ new Shader(GL_VERTEX_SHADER, "media/triangles.vert"),
		new Shader(GL_FRAGMENT_SHADER, "media/triangles.frag") }, "model");

	latus = new Object(new Model("models/latus"), new Shader*[2]{ new Shader(GL_VERTEX_SHADER, "media/triangles.vert"),
		new Shader(GL_FRAGMENT_SHADER, "media/triangles.frag") }, "model");

	gun = new Object(new Model("models/gun"), new Shader*[2]{ new Shader(GL_VERTEX_SHADER, "media/triangles.vert"),
		new Shader(GL_FRAGMENT_SHADER, "media/triangles.frag") }, "model");

	events = new Handler();

	events->Register("R_X-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		gun->modelTransform(0.5f, vmath::vec3((float)x, (float)y, 0), vmath::vec3(0, 0, 0));
	});

	events->Register("R_Y-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		gun->modelTransform(0.5f, vmath::vec3((float)x, (float)y, 0), vmath::vec3(0, 0, 0));
	});
}

void Playing::cleanup()
{
#pragma message WARN("Fix after this line need to be done!")
	//delete[] monkey;
	//delete[] gun;
	//delete[] latus;
	//delete[] events;
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
		events->Trigger("R_X-Axis", data);
		x += 20;
	}
	else if (down == GLFW_PRESS)
	{
		events->Trigger("R_X-Axis", data);
		x -= 20;
	}
	if (left == GLFW_PRESS)
	{
		events->Trigger("R_Y-Axis", data);
		y += 20;
	}
	else if (right == GLFW_PRESS)
	{
		events->Trigger("R_Y-Axis", data);
		y -= 20;
	}

	if (glfwWindowShouldClose(app->rWindow()))
	{
		app->quit();
	}
}

void Playing::update(Application * app)
{
	gun->update();
	//monkey->update();
	//latus->update();
}

void Playing::draw(Application * app)
{
	gun->render();
	//monkey->render();
	//latus->render();
}
