#include "playing.h"
#include "../Entities/entity.h"
#include "../Utils/math.h"

Playing::Playing() : renderer("base", "base"), blue("base", "blue"), cam(45.0f, 16.0f/9.0f, 0.1f, 100.0f) { }

void Playing::initialize(Application * app)
{
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSetInputMode(app->rWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	cam.setEye(glm::vec3(0.0f, 0.0f, 0.0f));

	/* KeyHandler */
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
		if (z == GLFW_PRESS)
		{
			renderer.push(&grass[1]);
		}
		else if (x == GLFW_PRESS)
		{
			renderer.remove(&grass[1]);
		}
	});

	//Add model and texture managers
	modelmanager.createModelType("creatures");
	texturemanager.createTextureType("creatures");

	texturemanager.paths()["creatures"].push_back("STexture");
	texturemanager.paths()["creatures"].push_back("pasta");
	modelmanager.paths()["creatures"].push_back("STexture");

	modelmanager.loadModels();
	texturemanager.loadTextures();

	/* Test Zone */

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-1.0f, 1.0f, 0.0f), //4
		glm::vec3(-1.0f, -1.0f, 0.0f), //3
		glm::vec3(1.0f, 1.0f, 0.0f), //1
		glm::vec3(1.0f, -1.0f, 0.0f) //2
	};

	std::vector<unsigned int> indices =
	{
		1, 2, 0, 1, 3, 2
	};

	std::vector<glm::vec2> uvs =
	{
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
	};

	loader.loadRaw(rawmodel, vertices, indices, uvs);


	//use nullptr for models and textures handling
	grass[0](modelmanager()["creatures"]["STexture"]);
	grass[0](texturemanager()["creatures"]["STexture"]);
	grass[0].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	renderer.push(&grass[0]);

	grass[1](&rawmodel);
	grass[1](texturemanager()["creatures"]["pasta"]);
	grass[1].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//blue.push(&grass[1]);
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
	//grass[0] << glm::vec3(0.0f, 0.1f, 0.0f);
	//grass[1] << glm::vec3(0.0f, 0.0f, 0.0f);
	renderer.update(cam);
	blue.update(cam);
}

void Playing::draw(Application * app)
{
	renderer.draw();
	blue.draw();
}
