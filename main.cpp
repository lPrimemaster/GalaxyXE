#include <iostream>
#include <vector>
#include "common/object.h"
#include "handler/handler.h"

GLuint VAO[1];
GLuint VBO[1];
GLuint EBO[1];


void init(GLFWwindow** window)
{
	//GLFW3 INIT
	glfwInit();
	*window = glfwCreateWindow(1280, 720, "Framework", NULL, NULL);
	glfwMakeContextCurrent(*window);

	//GLEW INIT
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "[Engine] Glew failed to initialize with error: " << glewGetErrorString(err) << std::endl;
	}
	else
	{
		std::cout << "[Engine] Glew initialized! Using version: " << glewGetString(GLEW_VERSION) << std::endl;
	}
}

int main(int argc, char* argv)
{
	GLFWwindow* window;
	init(&window);

	SDEBUG("Debug is active.");

	Object* monkey = new Object(new Model("models/monkey"), new Shader*[2]{ new Shader(GL_VERTEX_SHADER, "media/triangles.vert"),
		new Shader(GL_FRAGMENT_SHADER, "media/triangles.frag") }, "model");

	Object* latus = new Object(new Model("models/latus"), new Shader*[2]{ new Shader(GL_VERTEX_SHADER, "media/triangles.vert"),
		new Shader(GL_FRAGMENT_SHADER, "media/triangles.frag") }, "model");

	Object* gun = new Object(new Model("models/gun"), new Shader*[2]{ new Shader(GL_VERTEX_SHADER, "media/triangles.vert"),
		new Shader(GL_FRAGMENT_SHADER, "media/triangles.frag") }, "model");

	Handler* events = new Handler();

	events->Register("R_X-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		monkey->modelTransform(1.0f, vmath::vec3((float)x, (float)y, 0), vmath::vec3(0, 0, 0));
	});

	events->Register("R_Y-Axis", [=](void* data) -> void {
		int x; memcpy(&x, (char*)data, sizeof(int));
		int y; memcpy(&y, (char*)data + sizeof(int), sizeof(int));
		monkey->modelTransform(1.0f, vmath::vec3((float)x, (float)y, 0), vmath::vec3(0, 0, 0));
	});


	static GLfloat cColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, cColor);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		static int x = 0, y = 0;
		static float scale = 1.0f;
		char* data = (char*)malloc(sizeof(int) * 2); //Data buffer for x and y coordinates

		memcpy(data, &x, sizeof(int));
		memcpy(data + sizeof(int), &y, sizeof(int));


		int up = glfwGetKey(window, GLFW_KEY_UP);
		int down = glfwGetKey(window, GLFW_KEY_DOWN);
		int left = glfwGetKey(window, GLFW_KEY_LEFT);
		int right = glfwGetKey(window, GLFW_KEY_RIGHT);

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

		monkey->update();
		monkey->render();

		gun->update();
		gun->render();

		latus->modelTransform(0.1f, vmath::vec3(0, 0, 0), vmath::vec3(0, 0, 0));
		latus->update();
		latus->render();

		//GLFW3 buffer swapping and event handling
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
