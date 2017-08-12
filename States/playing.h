#pragma once
#include "state.h"
#include "../App/application.h"
#include "../Models/model.h"
#include "../Models/loader.h"

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
	Handler events;
	Model ab;
	Loader loader;
};

