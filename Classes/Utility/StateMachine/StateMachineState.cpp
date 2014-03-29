#include "StateMachineState.h"

StateMachineState::StateMachineState()
{
    state = STATE_INACTIVE;
}

StateMachineState::~StateMachineState()
{
    
}

void StateMachineState::Enter(bool _immediate)
{
    if(_immediate)
        SetState(STATE_ACTIVE);
    else
        SetState(STATE_ENTERING);
}

void StateMachineState::Exit(bool _immediate)
{
    if(_immediate)
        SetState(STATE_INACTIVE);
    else
        SetState(STATE_EXITING);
}

void StateMachineState::Update(float dt)
{
    switch (state)
    {
        case STATE_ACTIVE:
            OnUpdate(dt);
            break;
        case STATE_ENTERING:
            if(OnEntering(dt))
                SetState(STATE_ACTIVE);
            break;
        case STATE_EXITING:
            if(OnExiting(dt))
                SetState(STATE_INACTIVE);
            break;
        default:
            break;
    }
}

void StateMachineState::OnEnter()
{
    return;
}

bool StateMachineState::OnEntering(float dt)
{
    return true;
}

void StateMachineState::OnUpdate(float dt)
{
    return;
}

bool StateMachineState::OnExiting(float dt)
{
    return true;
}

void StateMachineState::OnExit()
{
    return;
}

void StateMachineState::SetState(StateMachineState::State _newState)
{
    if(state == _newState)
        return;
    
    switch(_newState)
    {
        case STATE_ENTERING:
            if(state != STATE_ACTIVE) //trigger only when coming from an exit state
                OnEnter();
            break;
        case STATE_ACTIVE:
            if(state != STATE_ENTERING) //trigger only when coming from an exit state
                OnEnter();
            break;
        case STATE_EXITING:
            break;
        case STATE_INACTIVE:
            OnExit(); //always trigger when becoming inactive
            break;
    }
    
    state = _newState;
}
