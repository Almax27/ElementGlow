#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"

class Line;

class Paddle : public cocos2d::CCNode
{
public:
	virtual ~Paddle();

	static Paddle* create(Line* _line, float _startPos, float _endPos);

	//CCNode
	virtual bool init();

	void triggerPaddle();

	//start and end dictate the paddles bounds and direction on it's parent line
	CC_SYNTHESIZE(float, startPos, StartPos);
	CC_SYNTHESIZE(float, endPos, EndPos);

protected:
	Paddle(Line* _line, float _startPos, float _endPos);

	Line* parentLine;
private:
};

#endif