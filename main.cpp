#include <iostream>
#include <vector>
#include "object.h"

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

#if 0
void verticesDrawNormal()
{
	glCreateVertexArrays(1, VAO);
	glBindVertexArray(VAO[0]);

	GLfloat vertices[] = {
		-0.90f, -0.90f, 0.0f,
		0.85f, -0.90f, 0.0f,
		-0.90f,  0.85f, 0.0f };

	glCreateBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
}

void verticesDrawElement()
{
	GLushort vertIndex[] = { 0, 2, 3, 0, 1, 3 };

	glCreateBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertIndex), vertIndex, GL_STATIC_DRAW);

	glCreateVertexArrays(1, VAO);
	glBindVertexArray(VAO[0]);

	Vector3f a = { -0.90f, -0.90f, 0.0f };
	Vector3f b = { 0.90f, -0.90f, 0.0f };
	Vector3f c = { -0.90f,  0.90f, 0.0f };
	Vector3f d = { 0.90f,  0.90f, 0.0f };

	vector<Vector3f> vertice = {
		a,
		b,
		c,
		d };

	vector<GLfloat> vertices = {
		-0.90f, -0.90f, 0.0f,
		0.90f, -0.90f, 0.0f,
		-0.90f,  0.90f, 0.0f,
		0.90f,  0.90f, 0.0f };

	GLfloat verti[] = {
		-0.90f, -0.90f, 0.0f,
		0.90f, -0.90f, 0.0f,
		-0.90f,  0.90f, 0.0f,
		0.90f,  0.90f, 0.0f };

	glCreateBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertice.size() * sizeof(Vector3f), &vertice.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
}

void drawNormal()
{
	static const GLfloat cColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, cColor);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawElement()
{
	static const GLfloat cColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, cColor);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}
#endif // 0

int main(int argc, char* argv)
{
	GLFWwindow* window;
	init(&window);

	Object* simao = new Object(new Model("models/monkey"), new Shader*[2]{ new Shader(GL_VERTEX_SHADER, "media/triangles.vert"),
		new Shader(GL_FRAGMENT_SHADER, "media/triangles.frag") }, "model");

	simao->bind(ENGINE_OBJ_PROGRAM_BIND);

	while (!glfwWindowShouldClose(window))
	{
		static int x = 0, y = 0;
		static float scale = 1.0f;

#if DEBUG
		int up = glfwGetKey(window, GLFW_KEY_UP);
		int down = glfwGetKey(window, GLFW_KEY_DOWN);
		int left = glfwGetKey(window, GLFW_KEY_LEFT);
		int right = glfwGetKey(window, GLFW_KEY_RIGHT);
		int crtl = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);

		if (up == GLFW_PRESS && crtl == GLFW_PRESS)
			scale += 0.01f;
		if (down == GLFW_PRESS && crtl == GLFW_PRESS)
			scale -= 0.01f;
		if (scale <= 0.0f)
			scale = 0.0f;

		if (left == GLFW_PRESS)
			y += 10;

		if (right == GLFW_PRESS)
			y -= 10;

		if (up == GLFW_PRESS)
			x += 10;

		if (down == GLFW_PRESS)
			x -= 10;

#endif // DEBUG


		simao->modelTransform(scale, vmath::vec3((float)x, (float)y, 0), vmath::vec3(0, 0, 0));
		simao->update();
		simao->render();

		//GLFW3 buffer swapping and event handling
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
