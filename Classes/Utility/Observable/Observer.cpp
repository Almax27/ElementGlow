#include "Observer.h"
#include "Observable.h"

Observer::Observer()
{
}

Observer::~Observer()
{
	for(std::list<Observable*>::iterator it = observableList.begin(); it != observableList.end(); it++)
	{
		(*it)->detachObserver(this);
	}
	observableList.clear();
}