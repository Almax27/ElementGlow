#include "Observable.h"
#include "Observer.h"

Observable::Observable()
{
}

Observable::~Observable()
{
}

void Observable::attachObserver(Observer* _observer)
{
	modifyList.push_back(ModifiedObserver(_observer, true));
	_observer->observableList.push_back(this);
}

void Observable::detachObserver(Observer* _observer)
{
	modifyList.push_back(ModifiedObserver(_observer, false));
	_observer->observableList.remove(this);
}

void Observable::clearObservers()
{
	for(std::list<Observer*>::iterator it = observerList.begin(); it != observerList.end(); it++)
	{
		modifyList.push_back(ModifiedObserver(*it, false));
		(*it)->observableList.remove(this);
	}
}

void Observable::notifyObservers(std::string _notification)
{
	processModifyList();

	for(std::list<Observer*>::iterator it = observerList.begin(); it != observerList.end(); it++)
	{
		if(*it != NULL)
		{
			(*it)->onNotification(_notification, this);
		}
	}
}

void Observable::processModifyList()
{
	for(int i = 0; i < modifyList.size(); i++)
	{
		if(modifyList[i].add)
		{
			observerList.push_back(modifyList[i].observer);
		}
		else
		{
			observerList.remove(modifyList[i].observer);
		}
	}
}