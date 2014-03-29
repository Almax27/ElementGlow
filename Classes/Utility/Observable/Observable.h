#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#include <string>
#include <list>
#include <vector>

class Observer;

class Observable
{
public:
	Observable();
	virtual ~Observable();

	void attachObserver(Observer* _observer);
	void detachObserver(Observer* _obeserver);
	void clearObservers();

	void notifyObservers(std::string _notification);

private:
	friend class Observer;

	std::list<Observer*> observerList;

	struct ModifiedObserver
	{
		ModifiedObserver(Observer* _observer, bool _add) : observer(_observer), add(_add) {}
		Observer* observer;
		bool add;
	};
	std::vector<ModifiedObserver> modifyList;
	void processModifyList();
};

#endif //_OBSERVABLE_H_
