#include <iostream>
#include <vector>
//#include "common/object.h"
#include "Handlers/handler.h"
#include "App/application.h"
#include "States/playing.h"


int main(int argc, char* argv)
{
	Application* app = new Application();

	app->initialize(vmath::uvec2(1280, 720), "GalaxyXE - Pluto");
	app->pushState(Playing::Instance());

	while (app->running())
	{
		app->handleEvents();
		app->update();
		app->draw();
	}

	app->cleanup();

	return 0;
}
