#pragma once
#include <functional>
#include <vector>
#include <map>

class Handler
{
public:
	Handler() = default;

	void Register(std::string outcome, std::function<void(void*)> lambda);
	void Trigger(const std::string & outcome, void* data);
	void Trigger(std::size_t index, void* data) const;

private:
	using Outcomes = std::map<std::string, std::function<void(void*)>>;
	std::vector<Outcomes::iterator> identifier;
	Outcomes outcomes;
};

