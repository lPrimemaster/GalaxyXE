#pragma once
#include "state.h"
#include "../App/application.h"
#include "../Models/model.h"
#include "../Models/loader.h"
#include "../Entities/entity.h"
#include "../Renderer/masterrenderer.h"
#include "../camera.h"

class Playing : public State
{
public:
	void initialize();
	void cleanup();

	void pause();
	void resume();

	void handleEvents(Application * app);
	void update(Application * app);
	void draw(Application * app);

	static Playing * Instance()
	{
		return &playingState;
	}

protected:
	Playing();

private:
	static Playing playingState;

	/* Keyhandler Event */
	Handler keyHandler;

	/* Loader Class */
	Loader loader;

	/* Models Definition */
	Model model[1];

	/* Entities Definition */
	Entity grass[2];

	/* MasterRenderer Class */
	MasterRenderer renderer;

	/* Camera Class */
	Camera cam;

};

