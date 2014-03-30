#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

class Line;

class Ball : public cocos2d::CCNode
{
public:
	virtual ~Ball();

	static Ball* create(Line* _parentLine);

	virtual bool init();
	virtual void update(float _dt);

	CC_SYNTHESIZE(int, lastPlayerIndex, LastPlayerIndex);
	CC_SYNTHESIZE(float, linePos, LinePos);
	CC_SYNTHESIZE(float, lineVelocity, LineVelocity);

	void reverseVelocity();
	void scaleLineVelocity(float _scale); 
	void increaseLineVelocity(float _deltaVel); //increase in direction of travel

protected:
	Ball(Line* _parentLine);

	Line* parentLine;

private:
};
#endif //_BALL_H_
