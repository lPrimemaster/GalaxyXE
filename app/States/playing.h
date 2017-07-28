#pragma once
#include "../state.h"
#include "../Application.h"
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

	Object* monkey;
	Object* latus;
	Object* gun;

	Handler* events;

};

