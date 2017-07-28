#include "state.h"
#include "application.h"


State::State() { }

void State::changeState(Application * app, State * state)
{
	app->changeState(state);
}