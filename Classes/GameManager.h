#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"

#include <list>
#include <map>

class Player;
class Line;

class GameManager : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	~GameManager();
	CREATE_FUNC(GameManager);

	virtual bool init();
	virtual void update(float _dt);

	//CCTargetedTouchDelegate
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);

protected:
	GameManager();

	std::map<unsigned int, Player*> players;
	std::list<Line*> activeLines;
};

#endif
