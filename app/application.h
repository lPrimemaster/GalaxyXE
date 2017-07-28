#pragma once
#include <iostream>
#include <stack>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vmath.h>

#include "state.h"

using namespace std;

class Application
{
public:

	void initialize(vmath::ivec2 resolution, const char* title);
	void cleanup();

	void pushState(State * state);
	void changeState(State * state);
	void popState();

	void handleEvents();
	void update();
	void draw();

	GLFWwindow* rWindow();

	bool running();
	void quit();

private:
	GLFWwindow* window;
	std::stack<State*> states;
	bool rApp;

};

