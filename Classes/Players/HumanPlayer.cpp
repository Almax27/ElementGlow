#include "HumanPlayer.h"

USING_NS_CC;

HumanPlayer::HumanPlayer(unsigned int _playerIndex)
	: Player(_playerIndex)
{
}

HumanPlayer::~HumanPlayer()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

HumanPlayer* HumanPlayer::create(unsigned int _playerIndex, const cocos2d::CCRect& _touchArea)
{
	HumanPlayer* humanPlayer = new HumanPlayer(_playerIndex);

	if(humanPlayer->init())
	{
		humanPlayer->autorelease();
		humanPlayer->setTouchArea(_touchArea);
		return humanPlayer;
	}

	CC_SAFE_DELETE(humanPlayer);
	return NULL;
}

bool HumanPlayer::init()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return Player::init();
}

void HumanPlayer::update(float _dt)
{

}

bool HumanPlayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(touchArea.containsPoint(pTouch->getLocation()))
	{
		triggerPlayerTouch();
		return true;
	}
	return false;
}