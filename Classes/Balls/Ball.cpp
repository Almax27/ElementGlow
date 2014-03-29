#include "Ball.h"

#include "Lines/Line.h"

#include "Resources.h"
#include <ctime>

USING_NS_CC;

Ball::Ball(Line* _parentLine)
	: parentLine(_parentLine)
{
}

Ball::~Ball()
{
}

Ball* Ball::create(Line* _parentLine)
{
	Ball* ball = new Ball(_parentLine);

	if(ball->init())
	{
		ball->autorelease();
		return ball;
	}

	CC_SAFE_DELETE(ball);
	return NULL;
}

bool Ball::init()
{
	CCSprite* sprite =  CCSprite::create(SpriteResource::ball);
	
	this->addChild(sprite);

	return true;
}

void Ball::update(float _dt)
{
	linePos += lineVelocity * _dt;
	if(linePos < 0)
	{
		linePos = 0;
		//TODO: kill?
		lineVelocity = -lineVelocity;
	}
	else if(linePos*linePos > parentLine->getLengthSq())
	{
		linePos = parentLine->getLength();
		//TODO: kill?
		lineVelocity = -lineVelocity;
	}

	this->setPosition(parentLine->getPointFromAbsDistance(linePos));
}

void Ball::reverseVelocity()
{
	lineVelocity = -lineVelocity;
}