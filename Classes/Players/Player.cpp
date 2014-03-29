#include "Player.h"

#include "Utility/Events/EventManager.h"

USING_NS_CC;

Player::Player(unsigned int _playerIndex)
	: playerIndex (_playerIndex)
{
}

Player::~Player()
{

}

void Player::triggerPlayerTouch()
{
	EventManager::Get().publishEvent(new Event("PlayerTouch", (void*)playerIndex));
}

bool Player::init()
{
	return true;
}

void Player::update(float _dt)
{
}
