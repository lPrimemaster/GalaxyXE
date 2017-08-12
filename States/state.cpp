#include "state.h"
#include "../App/application.h"


State::State() { }

void State::changeState(Application * app, State * state)
{
	app->changeState(state);
}