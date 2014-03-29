/*
 * EventManager.cpp
 *
 *  Created on: 16 Nov 2013
 *      Author: Almax
 */

#include "EventManager.h"
#include "IEventSubscriber.h"

#include "Utility/Debug.h"

EventManager::EventManager()
	: isPublishing(false)
{
}

void EventManager::AddSubscriber(IEventSubscriber* _subscriber, EventType _eventType)
{
	if(!isPublishing)
	{
		//insert the subscriber under the given event type
		SubscriberList& subscriberList = subscriberMap[_eventType];
		subscriberList.insert(subscriberList.begin(),_subscriber);
	}
	else
	{
		subscriberModifyList.push_back(ModifySubscriber(_subscriber, _eventType, true));
	}
}

void EventManager::RemoveSubscriber(IEventSubscriber* _subscriber, EventType _eventType)
{
	if(!isPublishing)
	{
		//if event have been subscribed to before
		if(subscriberMap.count(_eventType) > 0)
		{
			//remove any occurances of the given subscriber
			subscriberMap[_eventType].remove(_subscriber);
		}
	}
	else
	{
		subscriberModifyList.push_back(ModifySubscriber(_subscriber, _eventType, false));
	}
}

void EventManager::RemoveSubscriberAll(IEventSubscriber* _subscriber)
{
	if(!isPublishing)
	{
		//for each event type (read pair)
		SubscriberMap::iterator mapIt;
		for(mapIt = subscriberMap.begin(); mapIt != subscriberMap.end(); mapIt++)
		{
			//remove any occurances of the given subscriber
			mapIt->second.remove(_subscriber);
		}
	}
	else
	{
		subscriberModifyList.push_back(ModifySubscriber(_subscriber, EventType(), false, true));
	}
}

void EventManager::publishEvent(Event* _event)
{
	pendingEventList.push_back(_event);
}

void EventManager::publishEventImmediately(Event* _event)
{
	EventManager::internalPublishEvent(_event);
}

void EventManager::processEvents()
{
	EventList::iterator it;
	for(it = pendingEventList.begin(); it != pendingEventList.end(); )
	{
		if(internalPublishEvent(*it))
		{
			it = pendingEventList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

bool EventManager::internalPublishEvent(Event* _event)
{
	if(subscriberMap.count(_event->getType()) != 0)
	{
		isPublishing = true;

		SubscriberList& subscriberList = subscriberMap[_event->getType()];
		SubscriberList::iterator it;
		for(it = subscriberList.begin(); it != subscriberList.end(); it++)
		{
			IEventSubscriber* subscriber = *it;
			subscriber->OnEvent(_event);
		}

		delete _event;

		isPublishing = false;

		//process modify list
		SubscriberModifyList::iterator modIt;
		for(modIt = subscriberModifyList.begin(); modIt != subscriberModifyList.end(); modIt++)
		{
			if(modIt->isSubscribing)
			{
				AddSubscriber(modIt->subscriber, modIt->eventType);
			}
			else //unsubscribing
			{
				if(modIt->isUnsubscribingAll)
					RemoveSubscriberAll(modIt->subscriber);
				else
					RemoveSubscriber(modIt->subscriber, modIt->eventType);
			}
		}

		subscriberModifyList.clear();

		return true;
	}
	else
	{
		DEBUG_LOG("No subscribers found for: " + _event->getType());
		return true; //successful publish as no subscribers were found
	}
}

