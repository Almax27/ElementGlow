/*
 * IEventSubscriber.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Almax
 *
 * Interface for classes that wish to receive events
 * Derrived classes must implement OnEvent() and manage their subscriptions appropriately
 */

#ifndef IEVENTSUBSCRIBER_H_
#define IEVENTSUBSCRIBER_H_

#include "Event.h"

class IEventSubscriber
{
public:
	/** This function is called for each event subscribed to, if and when they are published
	 * \param _event event this callback was called on, will be deleted by manager when functionr returns
	 */
	virtual void OnEvent(Event* _event) = 0;

	virtual ~IEventSubscriber();
protected:
	/** Subscribe to a given event type */
	void subscribe(EventType _eventType);
	/** Unsubscribe from a given event type */
	void unsubscribe(EventType _eventType);
	/** Unsubscribe from all events */
	void unsubscribeAll();
private:
};


#endif /* IEVENTSUBSCRIBER_H_ */
