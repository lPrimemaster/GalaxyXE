#include "pengine.h"
#include <chrono>


PEngine::PEngine(std::mutex* mtx)
{
	this->mtx = mtx;
}


PEngine::~PEngine()
{
}

void PEngine::createPhysObj(Entity * ent) //Change this
{
	PBody* emp = new PBody(ent);
	//emp->velocity = glm::vec3(2.0f, 0.0f, 0.0f);
	//emp->acceleration = glm::vec3(-0.5f, 0.0f, 0.0f);
	emp->angularVelocity = glm::vec3(1.0f, 1.7f, -2.0f);
	bodies.emplace(ent, emp);
}

void PEngine::step()
{
	while (!threadStop)
	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		static std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
		static int runs = 0;
		static double timeStep = 1.0/500.0;
		time += timeStep;
		for (auto b : bodies)
		{
			//Center of mass relative position
			resolveLinearMotion(b.second);
			//Center of mass relative rotation
			resolveAngularMotion(b.second);

			mtx->lock();
			assignValueToRenderEngine(b);
			mtx->unlock();
		}
		runs++;
		std::chrono::duration<double> ctime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
		std::chrono::duration<double> wait = std::chrono::duration<double, std::ratio<1, 1000000>>(std::chrono::duration<double, std::ratio<1, 1000000>>(10000) - ctime);
		std::this_thread::sleep_for(wait);
		if ((std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0)).count() > 1)
		{
			timeStep = 1.0 / runs;
			runs = 0;
			t0 = std::chrono::high_resolution_clock::now();
		}
	}
}

bool PEngine::startThread()
{
	pThread = std::thread(&PEngine::step, this);
	tRunning = true;
	return true;
}

bool PEngine::stopThread()
{
	if (tRunning)
	{
		threadStop = true;
		pThread.join();
		return true;
	}
	return false;
}

void PEngine::assignValueToRenderEngine(std::pair<Entity* const, PBody*> b)
{
	b.first->setPosition(b.second->position);
	b.first->setRotation(b.second->rotation);
}

bool PEngine::resolveLinearMotion(PBody * body)
{
	body->position = body->velocity * time + body->acceleration * time * time;
	return true;
}

bool PEngine::resolveAngularMotion(PBody * body)
{
	body->rotation = body->angularVelocity * time + body->angularAcceleration * time * time;
	return true;
}



bool PEngine::calculateColisions(PBody* first, PBody* second)
{
	return false;
}

bool PEngine::calculateInertiaTensor(PBody * body)
{
	return true;
}
