#pragma once
#include "pbody.h"
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include "../Entities/entity.h"
#include "collisiontree.h"

class PEngine
{
public:
	PEngine(std::mutex* mtx);
	~PEngine();
	void createPhysObj(Entity* ent);

	bool startThread();
	bool stopThread();

private:
	std::map<Entity*, PBody*> bodies;
	float time = 0;
	bool threadStop = false;
	bool tRunning = false;

private:
	bool resolveLinearMotion(PBody* body);
	bool resolveAngularMotion(PBody* body);
	bool calculateColisions(PBody* first, PBody* second);
	bool calculateInertiaTensor(PBody* body);

	void step();
	void assignValueToRenderEngine(std::pair<Entity* const, PBody*> b);

private:
	std::thread pThread;
	std::mutex* mtx;
};

