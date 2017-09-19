#include "playing.h"
#include "../Entities/entity.h"

Playing::Playing() : renderer("base", "blue"), cam(45.0f, 16.0f/9.0f, 0.1f, 100.0f) { }

void Playing::initialize()
{
	keyHandler.Register("R_X-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		printf("Events!\n");
	});

	keyHandler.Register("R_Y-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		printf("Events!\n");
	});

	loader.setInternalPath("stall");
	loader.setAttributeShader(renderer.getShader());
	try
	{
		loader.loadFromObj(model[0]);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	//try
	//{
	//	loader.loadtexture2D(model[0]);
	//}
	//catch (std::runtime_error& e)
	//{
	//	std::cout << e.what() << std::endl;
	//}

	grass[0](&model[0]);
	grass[0].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	grass[0] << 0.5f;
	renderer.push(&grass[0]);
	cam.debug();

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
		keyHandler.Trigger("R_X-Axis", data);
		x += 20;
	}
	else if (down == GLFW_PRESS)
	{
		keyHandler.Trigger("R_X-Axis", data);
		x -= 20;
	}
	if (left == GLFW_PRESS)
	{
		keyHandler.Trigger("R_Y-Axis", data);
		y += 20;
	}
	else if (right == GLFW_PRESS)
	{
		keyHandler.Trigger("R_Y-Axis", data);
		y -= 20;
	}

	if (glfwWindowShouldClose(app->rWindow()))
	{
		app->quit();
	}
}

void Playing::update(Application * app)
{
	static float x = 0.0f;
	static float ry = 0.0f;
	static float rz = -10.0f;
	cam.lookAt(glm::vec3(x, ry, rz), glm::vec3(0.0f, 0.0f, 0.0f));

	grass[0] << glm::vec3(0.0f, 0.1f, 0.0f);



	renderer.update(cam);
}

void Playing::draw(Application * app)
{
	renderer.draw();
}
