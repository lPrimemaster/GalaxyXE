#include "playing.h"
#include "../Entities/entity.h"
#include "../Utils/math.h"

Playing::Playing() : renderer("base", "base"), wireframes("base", "brightgreen"), cam(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f), light(45.0f, 16.0f / 9.0f, 0.1f, 100.0f),
ambiance(glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), physics(&mtx)
{
}

void Playing::initialize(Application * app)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glLineWidth(5.0f);
	glCullFace(GL_BACK);
	glfwSetInputMode(app->rWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	cam.setEye(glm::vec3(0.0f, 0.0f, 0.0f));
	
	/* KeyHandler */ //TODO - Make key getters static...
	keyHandler.Register("R_Mouse", [=](int) -> void {
		int CTRL = glfwGetKey(app->rWindow(), GLFW_KEY_LEFT_ALT);
		if (CTRL != GLFW_PRESS)
		{
			static GLFWwindow* sWindow = app->rWindow();
			static glm::dvec2 nd;

			static const float MX_SENSITIVITY = 0.0025f;
			static const float MY_SENSITIVITY = 0.0025f;

			glfwGetCursorPos(sWindow, &nd.x, &nd.y);

			double deltaX = glm::dvec2(nd).x - (double)(1280 / 2);
			double deltaY = glm::dvec2(nd).y - (double)(720 / 2);

			cam.setYaw((float)deltaX * MX_SENSITIVITY);
			cam.setPitch((float)deltaY * MY_SENSITIVITY);
			cam.fpsRH();

			glfwSetCursorPos(sWindow, (double)(1280 / 2), (double)(720 / 2));
		}
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
		int CTRL = glfwGetKey(app->rWindow(), GLFW_KEY_LEFT_ALT);

		if (CTRL != GLFW_PRESS)
		{
			glm::vec3 direction = cam.heading();
			glm::vec3 oeye = cam.getEye();

			direction.y = 0.0f;
			glm::vec3 ydir = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 newDir = math::cross(ydir, direction);
			neye = oeye + direction * dx * MX_SENSITIVITY + newDir * dy * MY_SENSITIVITY + ydir * dz * MZ_SENSITIVITY;
			cam.setEye(neye);
		}
		else
		{
			glm::vec3 direction = light.heading();
			glm::vec3 oeye = light.getEye();

			direction.y = 0.0f;
			glm::vec3 ydir = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 newDir = math::cross(ydir, direction);
			neye = oeye + direction * dx * MX_SENSITIVITY + newDir * dy * MY_SENSITIVITY + ydir * dz * MZ_SENSITIVITY;
			light.setEye(neye);
		}
	});
	keyHandler.Register("MLight", [=](int) -> void {
		int w = glfwGetKey(app->rWindow(), GLFW_KEY_UP);
		int a = glfwGetKey(app->rWindow(), GLFW_KEY_LEFT);
		int s = glfwGetKey(app->rWindow(), GLFW_KEY_DOWN);
		int d = glfwGetKey(app->rWindow(), GLFW_KEY_RIGHT);
		int down = glfwGetKey(app->rWindow(), GLFW_KEY_END);
		int up = glfwGetKey(app->rWindow(), GLFW_KEY_HOME);
		
		static glm::vec3 pos = glm::vec3(0.0f, 7.0f, 0.0f);

		if (w == GLFW_PRESS)
		{
			pos.x += 0.1f;
		}
		if (s == GLFW_PRESS)
		{
			pos.x -= 0.1f;
		}
		if (a == GLFW_PRESS)
		{
			pos.z += 0.1f;
		}
		if (d == GLFW_PRESS)
		{
			pos.z -= 0.1f;
		}
		if (up == GLFW_PRESS)
		{
			pos.y += 0.1f;
		}
		if (down == GLFW_PRESS)
		{
			pos.y -= 0.1f;
		}
		ambiance.setDirection(pos);
	});
	keyHandler.Register("Cos", [=](int) -> void {

		static float spot = 0.0f;
		int P = glfwGetKey(app->rWindow(), GLFW_KEY_P);
		int CRT = glfwGetKey(app->rWindow(), GLFW_KEY_LEFT_CONTROL);
		if  (P == GLFW_PRESS)
		{
			if (CRT != GLFW_PRESS)
				spot += 0.01f;
			else
				spot -= 0.01f;

			//ambiance.setCosCutoff(spot);
			printf("Spot: %f\n", spot);
		}
	});

	//Add model and texture managers
	modelmanager.createModelType("creatures");
	texturemanager.createTextureType("creatures");

	modelmanager.paths()["creatures"].push_back("plane");
	modelmanager.paths()["creatures"].push_back("dragon");
	modelmanager.paths()["creatures"].push_back("stall");

	texturemanager.paths()["creatures"].push_back("boi");
	texturemanager.paths()["creatures"].push_back("stallTexture");

	modelmanager.loadModels();
	texturemanager.loadTextures();

	gui.associateTexture(texturemanager()["creatures"]["boi"]->getTexture());
	gui.setPosition(glm::vec2(100.0f, 100.0f));

	renderer.push(&ambiance);
	wireframes.push(&ambiance); // Feature pointer needs to be checked for crashing

	grass[0](modelmanager()["creatures"]["plane"]);
	//grass[0](texturemanager()["creatures"]["stallTexture"]);
	grass[0].setPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	//renderer.push(&grass[0]);

	//use nullptr for models and textures handling
	grass[1](modelmanager()["creatures"]["stall"]);
	grass[1](texturemanager()["creatures"]["stallTexture"]);
	//grass[1].setPosition(glm::vec3(0.0f, -0.25f, 0.0f));
	renderer.push(&grass[1]);
	physics.createPhysObj(&grass[1]);

	boundingBox = new Model();
	boundingBox->attachParam(GXE_MODEL_WIREFRAME, GXE_ON);
	boundingBox->attachParam(GXE_MODEL_RENDER_TYPE, GL_TRIANGLE_STRIP);
	loader.loadRaw(*boundingBox, grass[1].getBody().getColisionTree().getBoundingVertices());
	grass[2](boundingBox);
	grass[2].attach(&grass[1]);
	wireframes.push(&grass[2]);

	physics.startThread();
}

void Playing::cleanup()
{
	physics.stopThread();
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
	keyHandler.Trigger("MLight", NULL);
	keyHandler.Trigger("Cos", NULL);

	if (glfwWindowShouldClose(app->rWindow()))
	{
		app->quit();
	}
}

void Playing::update(Application * app)
{
	grass[0] << 10.0f;
	grass[1] << 1.0f;
	gui << 0.1f;
	renderer.update(cam);
	wireframes.update(cam);
	//gui.update();
}

void Playing::draw(Application * app)
{
	mtx.lock();
	renderer.draw();
	wireframes.draw();
	//gui.draw();
	mtx.unlock();
}
