#include "application.h"


void Application::initialize(vmath::uvec2 resolution, const char* title)
{
	//GLFW3 INIT
	glfwInit();
	window = glfwCreateWindow(resolution[0], resolution[1], title, NULL, NULL);
	glfwMakeContextCurrent(window);

	//GLEW INIT
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		throw std::runtime_error("[Engine] Glew failed to initialize with error: " + std::string((char*)glewGetErrorString(err)));
	}
	else
	{
		std::cout << "[Engine] Glew initialized! Using version: " << glewGetString(GLEW_VERSION) << std::endl;
	}

	static GLfloat cColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, cColor);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	rApp = true;
}

void Application::cleanup()
{
	//CleanUp states
	while (!states.empty())
	{
		states.top()->cleanup();
		states.pop();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	rApp = false;

	//Do other stuff
}

void Application::changeState(State * state)
{
	if (!states.empty())
	{
		states.top()->cleanup();
		states.pop();
	}

	states.push(state);
	states.top()->initialize();
}

void Application::pushState(State * state)
{
	if (!states.empty())
	{
		states.top()->pause();
	}

	states.push(state);
	states.top()->initialize();
}

void Application::popState()
{
	if (!states.empty())
	{
		states.top()->cleanup();
		states.pop();
	}

	if (!states.empty())
	{
		states.top()->resume();
	}
}

void Application::handleEvents()
{
	states.top()->handleEvents(this);
	glfwPollEvents();
}

void Application::update()
{
	states.top()->update(this);
}

void Application::draw()
{
	states.top()->draw(this);

	//GLFW3 buffer swapping and event handling
	glfwSwapBuffers(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow * Application::rWindow()
{
	return window;
}

bool Application::running()
{
	return rApp;
}

void Application::quit()
{
	cout << "Application terminating..." << endl;
	rApp = false;
}
