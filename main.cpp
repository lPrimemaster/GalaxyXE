#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <vector>
#include <thread>
#include "App/application.h"

/* --------------------------------- */
/* STATIC STATE SINGLETON DEFINITION */
/* --------------------------------- */
Application Application::app(glm::uvec2(1280, 720), "GalaxyXE - Pluto");
Playing Playing::playingState;


/* ---- */
/* MAIN */
/* ---- */
int main(int argc, char** argv)
{
	Application* app = Application::Instance();

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
