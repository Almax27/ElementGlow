#include "AIPlayer.h"

USING_NS_CC;

AIPlayer::AIPlayer(unsigned int _playerIndex)
	: Player(_playerIndex)
{

}

AIPlayer::~AIPlayer()
{
}

AIPlayer* AIPlayer::create(unsigned int _playerIndex)
{
	AIPlayer* aiPlayer = new AIPlayer(_playerIndex);

	if(aiPlayer->init())
	{
		aiPlayer->autorelease();
		return aiPlayer;
	}

	CC_SAFE_DELETE(aiPlayer);
	return NULL;
}

bool AIPlayer::init()
{
	return Player::init();
}

void AIPlayer::update(float _dt)
{
}