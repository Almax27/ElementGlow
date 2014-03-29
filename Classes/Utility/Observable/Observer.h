#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>
#include <list>

class Observable;

//TODO: needs to detach on destruction - cpp implementation required
class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void onNotification(std::string _notification, Observable* context) = 0;

private:
	friend class Observable;
	std::list<Observable*> observableList;
};

#endif //_OBSERVER_H_
