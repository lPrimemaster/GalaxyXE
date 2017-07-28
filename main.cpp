#include <iostream>
#include <vector>
#include "common/object.h"
#include "handler/handler.h"
#include "app/application.h"
#include "app/States/playing.h"


int main(int argc, char* argv)
{
	Application* app = new Application();

	app->initialize(vmath::ivec2(1280, 720), "GalaxyXE - Pluto");
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
