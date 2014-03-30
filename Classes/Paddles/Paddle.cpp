#include "Paddle.h"
#include "Lines/Line.h"
#include "Balls/Ball.h"

#include "Utility/LineSpriteHelper.h"
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

	CCPoint startPoint = parentLine->getPointFromAbsDistance(startPos);
	CCPoint endPoint = parentLine->getPointFromAbsDistance(endPos);
	
	//FIXME: placeholder paddle body graphic
	paddleBody = CCSprite::create(SpriteResource::line);
	this->addChild(paddleBody);
	paddleBody->setColor(ccc3(0,0,255));
	paddleBody->setOpacity(0);
	PlaceLineSprite(paddleBody, startPoint, endPoint);

	//FIXME: placeholder start and end graphics
	CCSprite* startSprite = CCSprite::create(SpriteResource::line);
	this->addChild(startSprite);
	startSprite->setPosition(startPoint);
	startSprite->setColor(ccc3(255,0,0));

	CCSprite* endSprite = CCSprite::create(SpriteResource::line);
	this->addChild(endSprite);
	endSprite->setPosition(endPoint);
	endSprite->setColor(ccc3(0,0,255));

	return true;
}

int Paddle::triggerPaddle(int _playerIndex)
{
	int ballHitCount = 0;
	const std::list<Ball*>& activeBalls = parentLine->getActiveBalls();
	for(std::list<Ball*>::const_iterator it = activeBalls.begin(); it != activeBalls.end(); it++)
	{
		Ball* ball = (*it);

		bool ballHit = false;
		float ballPos = (*it)->getLinePos();
		float ballVel = (*it)->getLineVelocity();
		//if our direction is positive
		if(startPos < endPos)
		{
			//if the ball velocity is negative and within bounds
			ballHit |= ballVel < 0 && ballPos >= startPos && ballPos <= endPos;
		}
		else //if our direction is negative
		{
			//if the ball velocity is positive and within bounds
			ballHit |= ballVel > 0 && ballPos <= startPos && ballPos >= endPos;
		}
		if(ballHit)
		{
			ballHitCount++;
			parentLine->onPlayerHitBall(ball, _playerIndex);
		}
	}

	if(ballHitCount > 0)
	{
		paddleBody->runAction(CCFadeOut::create(0.5f));
	}

	return ballHitCount;
}
