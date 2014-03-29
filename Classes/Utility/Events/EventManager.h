/*
 * EventManager.h
 *
 *  Created on: 16 Nov 2013
 *      Author: Almax
 *
 * The EventManager singleton handles passing published events to subscribers
 * It's update method should be run in the main thread once per frame, ideal
 *
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "Utility/Singleton.h"
#include "Event.h"

#include <map>
#include <list>

class IEventSubscriber;

class EventManager : public Singleton<EventManager>
{
public:
	EventManager();

	/** Add subscriber to event list - will receive events of given type */
	void AddSubscriber(IEventSubscriber* _subscriber, EventType _eventType);

	/** Remove subscriber from event list - will no longer receive events of given type */
	void RemoveSubscriber(IEventSubscriber* _subscriber, EventType _eventType);

	/** Remove subscriber from all event lists - will no longer receive events of any type */
	void RemoveSubscriberAll(IEventSubscriber* _subscriber);

	/** Publish event asynchronously on the next the EventManager::processEvents() call
	 * EventManager will delete event when publishing is complete
	 */
	void publishEvent(Event* _event);

	/** Publish event synchronously
	 * EventManager will delete event when publishing is complete
	 */
	void publishEventImmediately(Event* _event);

	/** Publish all pending events
	 * Recommend calling this once per frame at an appropriate time
	 */
	void processEvents();

protected:
	struct ModifySubscriber
	{
		ModifySubscriber(IEventSubscriber* _subscriber, EventType _eventType, bool _isSubscribing, bool _isUnsubscribingAll = false)
		: subscriber(_subscriber),
		  eventType(_eventType),
		  isSubscribing(_isSubscribing),
		  isUnsubscribingAll(_isUnsubscribingAll)
		{
		}
		IEventSubscriber* subscriber;
		EventType eventType;
		bool isSubscribing;
		bool isUnsubscribingAll;
	};

	typedef std::list<IEventSubscriber*> SubscriberList;
	typedef std::list<ModifySubscriber> SubscriberModifyList;
	typedef std::map<EventType, SubscriberList> SubscriberMap;
	typedef std::list<Event*> EventList;

	bool isPublishing;
	SubscriberMap subscriberMap;
	EventList pendingEventList;
	SubscriberModifyList subscriberModifyList;

	/** Publish event and delete when finished
	 * \return true if successful
	 */
	bool internalPublishEvent(Event* _event);
private:
};

#endif /* EVENTMANAGER_H_ */
