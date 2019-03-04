#pragma once
#include <functional>
#include <memory>
#include <vector>

template<class Sender, class Data>
class Event
{
public:
	Event(Sender & sender);
	~Event();
	void operator+=(std::function<void(Sender&, const Data&)> func);
	void operator-=(std::function<void(Sender&, const Data&)> func);
	void Invoke(const Data & data);
private:
	Sender *const sender;
	std::vector<std::function<void(Sender&, const Data&)> > callbacks;
};

#include <algorithm>

template<class Sender, class Data>
Event<Sender, Data>::Event(Sender & sender) : sender(&sender)
{
}

template<class Sender, class Data>
Event<Sender, Data>::~Event()
{
}

template<class Sender, class Data>
void Event<Sender, Data>::operator+=(std::function<void(Sender&, const Data&)> func)
{
	callbacks.push_back(func);
}

template<class Sender, class Data>
void Event<Sender, Data>::operator-=(std::function<void(Sender&, const Data&)> func)
{
	callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(), [&func](std::function<void(Sender&, const Data&)> f) {return f.target<void(*)(Sender&, const Data&)>() == func.target<void(*)(Sender&, const Data&)>(); }), callbacks.end());
}

template<class Sender, class Data>
void Event<Sender, Data>::Invoke(const Data & data)
{
	for (auto func : callbacks)
	{
		func(*sender, data);
	}
}

