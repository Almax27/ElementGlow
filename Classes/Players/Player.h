#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Utility/Events/IEventSubscriber.h"

class Player : public cocos2d::CCObject, public IEventSubscriber
{
public:
	virtual ~Player();

	void triggerPlayerTouch();

	virtual bool init();
	virtual void update(float _dt);

	//IEventSubscriber
	virtual void OnEvent(Event* _event);

	CC_SYNTHESIZE_READONLY(int, playerIndex, PlayerIndex);
	CC_SYNTHESIZE(int, score, Score);

protected:
	Player(unsigned int _playerIndex);

private:
	
};

#endif //_PLAYER_H_