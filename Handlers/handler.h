#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>

template<typename T>
class Handler
{
public:
	Handler() = default;

	void Register(std::string key, std::function<void(T)> type);
	void Trigger(std::string key, T type);


private:
	std::map<std::string, std::function<void(T)>> typemap;
};

template<typename T>
inline void Handler<T>::Register(std::string key, std::function<void(T)> type)
{
	typemap.emplace(key, type);
}

template<typename T>
inline void Handler<T>::Trigger(std::string key, T type)
{
	typemap[key](type);
}
