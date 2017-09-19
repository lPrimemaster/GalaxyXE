#pragma once
#include <iostream>
#include <stack>
#include <memory>
#include <stdexcept>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../States/state.h"
#include "../States/playing.h"

using namespace std;

class Application
{
public:

	void initialize(glm::uvec2 resolution, const char* title);
	void cleanup();

	void pushState(State * state);
	void changeState(State * state);
	void popState();

	void handleEvents();
	void update();
	void draw();

	GLFWwindow * rWindow()
	{
		return window;
	};

	static Application * Instance()
	{
		return &app;
	}

	bool running();
	void quit();

protected:
	Application(glm::uvec2 resolution, const char* title);

private:
	static Application app;
	GLFWwindow* window;
	std::stack<State*> states;
	bool rApp;

};

