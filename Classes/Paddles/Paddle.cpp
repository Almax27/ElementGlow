#include "Paddle.h"
#include "Lines/Line.h"
#include "Balls/Ball.h"
#include "Resources.h"

USING_NS_CC;

Paddle::Paddle(Line* _line, float _startPos, float _endPos)
	: parentLine(_line),
	startPos(_startPos),
	endPos(_endPos)
{
}

Paddle::~Paddle()
{
}

Paddle* Paddle::create(Line* _line, float _startPos, float _endPos)
{
	Paddle* paddle = new Paddle(_line, _startPos, _endPos);

	if(paddle->init())
	{
		paddle->autorelease();
		return paddle;
	}

	CC_SAFE_DELETE(paddle);
	return NULL;
}

bool Paddle::init()
{
	if(CCNode::init() == false)
	{
		return false;
	}
	
	//FIXME: placeholder start and end graphics
	CCSprite* startSprite = CCSprite::create(SpriteResource::line);
	this->addChild(startSprite);
	startSprite->setPosition(parentLine->getPointFromAbsDistance(startPos));
	startSprite->setColor(ccc3(255,0,0));

	CCSprite* endSprite = CCSprite::create(SpriteResource::line);
	this->addChild(endSprite);
	endSprite->setPosition(parentLine->getPointFromAbsDistance(endPos));
	endSprite->setColor(ccc3(0,0,255));

	return true;
}

void Paddle::triggerPaddle()
{
	const std::list<Ball*>& activeBalls = parentLine->getActiveBalls();
	for(std::list<Ball*>::const_iterator it = activeBalls.cbegin(); it != activeBalls.cend(); it++)
	{
		float ballPos = (*it)->getLinePos();
		float ballVel = (*it)->getLineVelocity();
		//if our direction is positive
		if(startPos < endPos)
		{
			//if the ball velocity is negative and within bounds
			if(ballVel < 0 && ballPos >= startPos && ballPos <= endPos)
			{
				(*it)->reverseVelocity();
			}
		}
		else //if our direction is negative
		{
			//if the ball velocity is positive and within bounds
			if(ballVel < 0 && ballPos <= startPos && ballPos >= endPos)
			{
				(*it)->reverseVelocity();
			}
		}
	}
}