/*
 * IEventSubscriber.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: Almax
 */


#include "IEventSubscriber.h"

#include "EventManager.h"

IEventSubscriber::~IEventSubscriber()
{
	unsubscribeAll();
}

void IEventSubscriber::subscribe(EventType _eventType)
{
	EventManager::Get().AddSubscriber(this, _eventType);
}

void IEventSubscriber::unsubscribe(EventType _eventType)
{
	EventManager::Get().RemoveSubscriber(this, _eventType);
}

void IEventSubscriber::unsubscribeAll()
{
	EventManager::Get().RemoveSubscriberAll(this);
}

