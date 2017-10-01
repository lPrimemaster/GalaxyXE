#include "playing.h"
#include "../Entities/entity.h"
#include "../Utils/math.h"

Playing::Playing() : renderer("base", "green"), blue("base", "blue"), cam(45.0f, 16.0f/9.0f, 0.1f, 100.0f) { }

void Playing::initialize(Application * app)
{
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSetInputMode(app->rWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	cam.setEye(glm::vec3(0.0f, 0.0f, -10.0f));

	keyHandler.Register("R_Mouse", [=](int) -> void {

		static GLFWwindow* sWindow = app->rWindow();
		static glm::dvec2 nd;

		static const float MX_SENSITIVITY = 0.0025f;
		static const float MY_SENSITIVITY = 0.0025f;

		glfwGetCursorPos(sWindow, &nd.x, &nd.y);

		double deltaX = glm::dvec2(nd).x - (double)(1280 / 2);
		double deltaY = glm::dvec2(nd).y - (double)(720 / 2);

		cam.setYaw(deltaX * MX_SENSITIVITY);
		cam.setPitch(deltaY * MY_SENSITIVITY);
		cam.fpsRH();

		glfwSetCursorPos(sWindow, (double)(1280 / 2), (double)(720 / 2));
	});
	keyHandler.Register("T_Move", [=](int) -> void {

		static GLFWwindow* sWindow = app->rWindow();
		static glm::vec3 neye;


		static const float MX_SENSITIVITY = 0.025f;
		static const float MY_SENSITIVITY = 0.025f;
		static const float MZ_SENSITIVITY = 0.025f;

		int forth = glfwGetKey(sWindow, GLFW_KEY_W);
		int back = glfwGetKey(sWindow, GLFW_KEY_S);
		int left = glfwGetKey(sWindow, GLFW_KEY_A);
		int right = glfwGetKey(sWindow, GLFW_KEY_D);
		int up = glfwGetKey(sWindow, GLFW_KEY_SPACE);
		int down = glfwGetKey(sWindow, GLFW_KEY_LEFT_SHIFT);

		float dx = 0.0f;
		float dy = 0.0f;
		float dz = 0.0f;

		glm::vec3 direction = cam.heading();
		glm::vec3 oeye = cam.getEye();

		if (forth == GLFW_PRESS)
		{
			dx += 2.0f;
		}
		if (back == GLFW_PRESS)
		{
			dx -= 2.0f;
		}
		if (left == GLFW_PRESS)
		{
			dy += 2.0f;
		}
		if (right == GLFW_PRESS)
		{
			dy -= 2.0f;
		}
		if (up == GLFW_PRESS)
		{
			dz += 2.0f;
		}
		if (down == GLFW_PRESS)
		{
			dz -= 2.0f;
		}

		direction.y = 0.0f;
		glm::vec3 ydir = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 newDir = math::cross(ydir, direction);
		neye = oeye + direction * dx * MX_SENSITIVITY + newDir * dy * MY_SENSITIVITY + ydir * dz * MZ_SENSITIVITY;
		cam.setEye(neye);
	});

	loader.setInternalPath("Dragon_2.5_For_Animations");
	loader.setAttributeShader(renderer.getShader());
	try
	{
		loader.loadFromObj(model[0]);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	loader.setInternalPath("floor");
	try
	{
		loader.loadFromObj(model[1]);
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

	grass[1](&model[1]);
	grass[1].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	blue.push(&grass[1]);

	grass[0](&model[0]);
	grass[0].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	grass[0] << 0.5f;
	renderer.push(&grass[0]);

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
	keyHandler.Trigger("R_Mouse", NULL);
	keyHandler.Trigger("T_Move", NULL);

	if (glfwWindowShouldClose(app->rWindow()))
	{
		app->quit();
	}
}

void Playing::update(Application * app)
{
	grass[0] << glm::vec3(0.0f, 0.1f, 0.0f);
	grass[1] << glm::vec3(0.0f, -0.1f, 0.0f);
	renderer.update(cam);
	blue.update(cam);
}

void Playing::draw(Application * app)
{
	renderer.draw();
	blue.draw();
}
