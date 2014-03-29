#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"

class HumanPlayer : public Player, public cocos2d::CCTargetedTouchDelegate
{
public:
	virtual ~HumanPlayer();

	static HumanPlayer* create(unsigned int _playerIndex, const cocos2d::CCRect& _touchArea);

	virtual bool init();
	virtual void update(float _dt);

	//CCTargetedTouchDelegate
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCRect, touchArea, TouchArea);

protected:
	HumanPlayer(unsigned int _playerIndex);

private:
};

#endif //_HUMAN_PLAYER_H_