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

	Model rawmodel;
	Loader loader;

	/* Entities Definition */
	Entity grass[2];

	/* Renderers */
	MasterRenderer renderer;
	MasterRenderer blue;

	/* Camera Class */
	Camera cam;

	/* Lights */
	Light ambiance[2];

};

