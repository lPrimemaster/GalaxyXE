#include "handler.h"
#include <iostream>

void Handler::Register(std::string outcome, std::function<void(void*)> lambda)
{
	auto emplaced = outcomes.emplace(std::move(outcome), std::move(lambda));
	identifier.push_back(emplaced.first);
}

void Handler::Trigger(const std::string & outcome, void* data)
{
	outcomes.at(outcome)(data);
}

void Handler::Trigger(std::size_t index, void* data) const
{
	identifier[index]->second(data);
}
