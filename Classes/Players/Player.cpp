#include "Player.h"

#include "Utility/Events/EventManager.h"

USING_NS_CC;

Player::Player(unsigned int _playerIndex)
	: playerIndex (_playerIndex), score(10)
{
}

Player::~Player()
{
	unsubscribeAll();
}

void Player::triggerPlayerTouch()
{
	EventManager::Get().publishEvent(new Event("PlayerTouch", (void*)playerIndex));
}

bool Player::init()
{
	subscribe("PlayerHit");
	subscribe("PlayerMissed");
	return true;
}

void Player::update(float _dt)
{
}

void Player::OnEvent(Event* _event)
{
	if(_event->isType("PlayerHit"))
	{
		if((int)_event->getData() == playerIndex)
		{
			score += 1;
		}
	}
	else if(_event->isType("PlayerMissed"))
	{
		if((int)_event->getData() == playerIndex)
		{
			score -= 1;
		}
	}
}
