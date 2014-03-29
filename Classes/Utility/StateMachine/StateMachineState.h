#ifndef __StateMachineStateState__
#define __StateMachineStateState__

class StateMachineState
{
public:

	StateMachineState();
	virtual ~StateMachineState();

	enum State
	{
		STATE_INACTIVE,
		STATE_ENTERING,
		STATE_ACTIVE,
		STATE_EXITING
	};

	/** called when the state should enter */
	void Enter(bool _immediate);

	/** called when the state should exit */
	void Exit(bool _immediate);

	/** called every frame while the state is active */
	void Update(float dt);

	/** state accessor */
	State GetState() { return state; }

protected:

	/** called on Enter() */
	virtual void OnEnter();

	/** called every frame after Enter(true) until returning true */
	virtual bool OnEntering(float dt);

	/** called every frame after OnEntering() returns true*/
	virtual void OnUpdate(float dt);

	/** called on Exit(false) or when OnExiting() returns true */
	virtual void OnExit();

	/** called every frame after Exit(true) until returning true */
	virtual bool OnExiting(float dt);

private:

	State state;

	void SetState(State _newState);

};

#endif
