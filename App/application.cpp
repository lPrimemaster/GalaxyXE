#include "application.h"

void Application::initialize(glm::uvec2 resolution, const char* title)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Context
	window = glfwCreateWindow(resolution[0], resolution[1], title, NULL, NULL);
	m_resolution = resolution;
	glfwMakeContextCurrent(window);

	//GLEW INIT
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "[Engine] Glew failed to initialize with error: " << (char*)glewGetErrorString(err) << std::endl;
	}
	else
	{
		std::cout << "[Engine] Glew initialized! Using version: " << glewGetString(GLEW_VERSION) << std::endl;
	}

	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

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
	states.top()->initialize(Application::Instance());
}

void Application::pushState(State * state)
{
	if (!states.empty())
	{
		states.top()->pause();
	}

	states.push(state);
	states.top()->initialize(Application::Instance());
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
	states.top()->handleEvents(Application::Instance());
	glfwPollEvents();
}

void Application::update()
{
	states.top()->update(Application::Instance());
}

void Application::draw()
{
	states.top()->draw(Application::Instance());

	//GLFW3 buffer swapping and event handling

	glfwSwapBuffers(window);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

Application::Application(glm::uvec2 resolution, const char* title)
{
	initialize(resolution, title);
}

glm::uvec2 Application::rWindowSize()
{
	return m_resolution;
}
