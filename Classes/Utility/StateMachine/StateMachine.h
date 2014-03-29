#ifndef __StateMachine__
#define __StateMachine__

#include "StateMachineState.h"
#include "Types.h"
#include <map>
#include <queue>
#include "Utility/ToFromString.h"

template <typename StateKey>
class StateMachine
{
public:
	/** StateMachine ctor */
	StateMachine();

	/** StateMachine dtor */
	virtual ~StateMachine();

	void Update(float _dt);

	//**************************************
	// State Management Methods

	/** add given state to the StateMachine under the given key,
		key-state relationship is 1-1 and keys must be unique */
	void AddState(StateKey _key, StateMachineState* _state);

	/** remove a state from the StateMachine with given key
		if delete is true the state instance will be deleted */
	void RemoveState(StateKey _key, bool _delete);

	/** remove all states from the StateMachine
		if _delete is true all state instance will also be deleted */
	void RemoveAllStates(bool _delete);

	/** Test to see if StateMachine contains a state with the given key */
	bool ContainsState(StateKey _key) const;

	/** Get state with given key, returns NULL if the key does not exist */
	StateMachineState* GetState(StateKey _key) const;

	//**************************************
	// State Control Methods

	/** Prompt state change, exiting the active and entering the given.
		If queue is true the function will be queued and re-called as soon as possible
		Returns false if a state change is already in progress, or there was an error
		Returns true if a valid state change was made or queued */
	bool ChangeState(StateKey _key, bool _immediate, bool _queue = false);

	/** exits the currently active state if there is one
		return false if in transition */
	bool ExitActiveState(bool _immediate);

	/** Get the currently active state, returns NULL if no state is active */
	const StateKey* GetActiveState() const { return activeState == stateMap.end() ? NULL : &activeState->first; }

	/** Get isTransitioning, returns true if a change of state is in progress */
	bool GetIsTransitioning() const { return isTransitioning; }

	/** Clears any state changes currently queued */
	void ClearStateQueue() { while(pendingStateChanges.size() > 0) pendingStateChanges.pop(); }

private:
	typedef std::map<StateKey, StateMachineState*> StateMap;
	StateMap stateMap;

	struct PendingStateChange
	{
		PendingStateChange(StateKey _key, bool _immediate) : key(_key), immediate(_immediate) {}
		StateKey key;
		bool immediate;
	};
	typedef std::queue<PendingStateChange> StateQueue;
	StateQueue pendingStateChanges;

	bool isTransitioning;

	typename StateMap::iterator activeState;
	typename StateMap::iterator nextState;
};

template <typename StateKey>
StateMachine<StateKey>::StateMachine()
{
	activeState = stateMap.end();
	nextState = stateMap.end();

	isTransitioning = false;
}

template <typename StateKey>
StateMachine<StateKey>::~StateMachine()
{
	RemoveAllStates(true);
	ClearStateQueue();
}

template <typename StateKey>
void StateMachine<StateKey>::Update(float _dt)
{
	StateMachineState* active = activeState == stateMap.end() ? NULL : activeState->second;

	if(isTransitioning)
	{
		StateMachineState* next = nextState->second;

		if(nextState == stateMap.end())
		{
			Eegeo_TTY("Invalid next state, aborting state change...\n");
			isTransitioning = false;
			return;
		}

		//if we have an active state, try and leave it
		if(active)
		{
			if(active->GetState() == StateMachineState::STATE_ACTIVE)
				active->Exit(false);
			else if(active->GetState() == StateMachineState::STATE_INACTIVE)
				activeState = stateMap.end();

			active->Update(_dt);
		}
		//else try and enter the next state
		else if(next->GetState() == StateMachineState::STATE_INACTIVE)
		{
			next->Enter(false);
		}
		//else when the new state is active, cache it as the active state and end transition
		else if(next->GetState() == StateMachineState::STATE_ACTIVE)
		{
			activeState = nextState;
			nextState = stateMap.end();
			isTransitioning = false;
		}

		next->Update(_dt);
	}
	else
	{
		//update active if valid
		if(active)
		{
			active->Update(_dt);

			//clean up inactive active state
			if(active->GetState() == StateMachineState::STATE_INACTIVE)
				activeState = stateMap.end();
		}



		//process queued transitions
		if(pendingStateChanges.size() > 0)
		{
			PendingStateChange& pendingChange = pendingStateChanges.front();
			if(ContainsState(pendingChange.key))
			{
				ChangeState(pendingChange.key, pendingChange.immediate);
			}
			else
				Eegeo_TTY("Failed to process pending state: no longer exists\n");

			pendingStateChanges.pop();
		}
	}
}

template <typename StateKey>
void StateMachine<StateKey>::AddState(StateKey _key, StateMachineState* _state)
{
	if(_state == NULL)
		Eegeo_TTY("Failed to add state: NULL state given\n");
	else if(ContainsState(_key))
		Eegeo_TTY("Failed to add state: key already exists\n");
	else
		stateMap[_key] = _state;
}

template <typename StateKey>
void StateMachine<StateKey>::RemoveState(StateKey _key, bool _delete)
{
	typename StateMap::iterator it = stateMap.find(_key);
	if(it == stateMap.end())
		Eegeo_TTY("Failed to remove state: key not found\n");
	else if(it == activeState)
		Eegeo_TTY("Failed to remove state: currently active\n");
	else if(isTransitioning && it == nextState)
		Eegeo_TTY("Failed to remove state: being transitioned to\n");
	else
	{
		if(_delete)
			delete it->second;
		stateMap.erase(it);
	}
}

template<typename StateKey>
void StateMachine<StateKey>::RemoveAllStates(bool _delete)
{
	typename StateMap::iterator it = stateMap.begin();
	while(it != stateMap.end())
	{
		if(_delete)
			delete it->second;
		stateMap.erase(it++);
	}
}

template <typename StateKey>
bool StateMachine<StateKey>::ContainsState(StateKey _key) const
{
	return stateMap.count(_key) > 0;
}

template <typename StateKey>
StateMachineState* StateMachine<StateKey>::GetState(StateKey _key) const
{
	if(ContainsState(_key))
	{
		return stateMap[_key];
	}
	else
		return NULL;
}

template <typename StateKey>
bool StateMachine<StateKey>::ChangeState(StateKey _key, bool _immediate, bool _queue)
{
	typename StateMap::iterator it = stateMap.find(_key);

	if(it == stateMap.end())
		Eegeo_TTY("Failed to change state: invalid key\n");
	else if(it == activeState)
		Eegeo_TTY("Failed to change state: state already active\n");
	else if(isTransitioning && it == nextState)
		Eegeo_TTY("Failed to change state: already transitioning to given state\n");
	else if(isTransitioning)
	{
		if(_queue)
		{
			pendingStateChanges.push(PendingStateChange(_key, _immediate));
			return true;
		}
		else
			return false;
	}
	else
	{
		if(_immediate)
		{
			if(activeState != stateMap.end()) //make sure we have an active state
				activeState->second->Exit(true);
			it->second->Enter(true);
		}
		else
		{
			isTransitioning = true;
			nextState = it;
		}
		return true;
	}
	return false;
}

template <typename StateKey>
bool StateMachine<StateKey>::ExitActiveState(bool _immediate)
{
	if(activeState != stateMap.end())
	{
		if(isTransitioning)
		{
			Eegeo_TTY("Failed to exit active state (%s): transitioning\n", ToString(activeState->first).c_str());
			return false;
		}

		activeState->second->Exit(_immediate);
	}

	return true;
}

#endif
