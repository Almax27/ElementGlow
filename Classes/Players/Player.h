#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"

class Player : public cocos2d::CCObject
{
public:
	virtual ~Player();

	void triggerPlayerTouch();

	virtual bool init();
	virtual void update(float _dt);

	CC_SYNTHESIZE_READONLY(unsigned int, playerIndex, PlayerIndex);

protected:
	Player(unsigned int _playerIndex);

private:
	
};

#endif //_PLAYER_H_