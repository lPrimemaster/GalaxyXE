#pragma once
#include "state.h"
#include "../App/application.h"
#include "../Models/model.h"
#include "../Models/loader.h"
#include "../Entities/entity.h"
#include "../Renderer/masterrenderer.h"
#include "../camera.h"
#include "../Utils/math.h"
#include "../Common/modelmanager.h"
#include "../Common/texturemanager.h"
#include "../Lights/Plight.h"
#include "../Lights/shadowbox.h"
#include "../Physics/pengine.h"

class Playing : public State
{
public:
	void initialize(Application * app);
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
	Handler<int> keyHandler;

	/* Models Definition */
	ModelManager modelmanager;

	/* Textures Definition */
	TextureManager texturemanager;

	/* Entities Definition */
	Entity grass[3];

	/* Renderers */
	MasterRenderer renderer;
	MasterRenderer wireframes;

	/* Camera Class */
	Camera cam;
	Camera light;

	/* Lights */
	DLight ambiance;

	/* Physics */
	PEngine physics;
	std::mutex mtx;

	/* Test */
	Loader loader;

	Model* boundingBox;

	Gui gui;

};

