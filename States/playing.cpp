#include "playing.h"
#include "../Entities/entity.h"
#include "../Utils/math.h"

Playing::Playing() : renderer("base", "base"), blue("base", "blue"), cam(45.0f, 16.0f/9.0f, 0.1f, 100.0f) { }

void Playing::initialize(Application * app)
{
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSetInputMode(app->rWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	cam.setEye(glm::vec3(0.0f, 0.0f, 0.0f));

	/* KeyHandler */ //TODO - Make key getters static...
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
	keyHandler.Register("ToggleRenderer", [=](int) -> void {
		int z = glfwGetKey(app->rWindow(), GLFW_KEY_Z);
		int x = glfwGetKey(app->rWindow(), GLFW_KEY_X);
		int z1 = glfwGetKey(app->rWindow(), GLFW_KEY_C);
		int x1 = glfwGetKey(app->rWindow(), GLFW_KEY_V);
		int z2 = glfwGetKey(app->rWindow(), GLFW_KEY_B);
		int x2 = glfwGetKey(app->rWindow(), GLFW_KEY_N);
		static float r = 1.0f;
		static float g = 1.0f;
		static float b = 1.0f;
		float ramp = 0.1f;
		auto l = [=](float& var) -> void { if (var > 1.0f) var = 1.0f; else if (var < 0.0f) var = 0.0f; };
		l(r); l(g); l(b);
		if (z == GLFW_PRESS)
		{
			//blue.push(&grass[0]);
			//blue.push(&grass[1]);
			ambiance[0].setProperties(LightProperties(GXE_DIRECTIONAL_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(r -= ramp, g, b), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));
		}
		else if (x == GLFW_PRESS)
		{
			//blue.remove(&grass[0]);
			//blue.remove(&grass[1]);
			ambiance[0].setProperties(LightProperties(GXE_DIRECTIONAL_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(r += ramp, g, b), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));
		}
		if (z1 == GLFW_PRESS)
		{
			//blue.push(&grass[0]);
			//blue.push(&grass[1]);
			ambiance[0].setProperties(LightProperties(GXE_DIRECTIONAL_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(r, g -= ramp, b), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));
		}
		else if (x1 == GLFW_PRESS)
		{
			//blue.remove(&grass[0]);
			//blue.remove(&grass[1]);
			ambiance[0].setProperties(LightProperties(GXE_DIRECTIONAL_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(r, g += ramp, b), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));
		}
		if (z2 == GLFW_PRESS)
		{
			//blue.push(&grass[0]);
			//blue.push(&grass[1]);
			ambiance[0].setProperties(LightProperties(GXE_DIRECTIONAL_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(r, g, b -= ramp), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));
		}
		else if (x2 == GLFW_PRESS)
		{
			//blue.remove(&grass[0]);
			//blue.remove(&grass[1]);
			ambiance[0].setProperties(LightProperties(GXE_DIRECTIONAL_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(r, g, b += ramp), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));
		}
	});

	//Add model and texture managers
	modelmanager.createModelType("creatures");
	texturemanager.createTextureType("creatures");

	texturemanager.paths()["creatures"].push_back("beacon");
	modelmanager.paths()["creatures"].push_back("dragon");
	modelmanager.paths()["creatures"].push_back("beacon");

	modelmanager.loadModels();
	texturemanager.loadTextures();

	//FIX Spot Light and standart half vector for directional light
	ambiance[0].setProperties(LightProperties(GXE_DIRECTIONAL_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(1.0f), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));
	//ambiance[1].setProperties(LightProperties(GXE_POINT_LIGHT, glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(1.0f), glm::vec3(0.1f), 0.7f, 0.0f, 0.2f));

	renderer.push(&ambiance[0]);
	//renderer.push(&ambiance[1]);

	//use nullptr for models and textures handling
	grass[0](modelmanager()["creatures"]["dragon"]);
	//grass[0](texturemanager()["creatures"]["beacon"]);
	grass[0].setPosition(glm::vec3(0.0f, -3.0f, -5.0f));
	renderer.push(&grass[0]);

	//grass[1](modelmanager()["creatures"]["beacon"]);
	//grass[1](texturemanager()["creatures"]["beacon"]);
	//grass[1].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//renderer.push(&grass[1]);
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
	keyHandler.Trigger("ToggleRenderer", NULL);

	if (glfwWindowShouldClose(app->rWindow()))
	{
		app->quit();
	}
}

void Playing::update(Application * app)
{
	grass[0] << glm::vec3(0.0f, 0.0f, 0.0f);
	//grass[1] << glm::vec3(0.0f, 0.0f, 0.0f);
	renderer.update(cam);
	blue.update(cam);
}

void Playing::draw(Application * app)
{
	blue.draw();
	renderer.draw();
}
