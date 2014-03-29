/*
 * Event.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Almax
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <string>

typedef std::string EventType;
#define EventCompare(a,b) a == b

class Event
{
public:
	Event(EventType _type, void* _data = NULL)
	: type(_type),
	data(_data)
	{
	}
	virtual ~Event() {}

	const EventType& getType() const { return type; }
	bool isType(EventType _type) const { return EventCompare(type, _type); }

	void* getData() const { return data; }

protected:
private:
	EventType type;
	void* data;
};

#endif /* EVENT_H_ */
