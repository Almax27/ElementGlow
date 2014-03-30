#include "Ball.h"

#include "Lines/Line.h"

#include "Resources.h"
#include <ctime>

USING_NS_CC;

Ball::Ball(Line* _parentLine)
	: parentLine(_parentLine), lastPlayerIndex(-1)
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
	this->setPosition(parentLine->getPointFromAbsDistance(linePos));
}

void Ball::reverseVelocity()
{
	lineVelocity = -lineVelocity;
}

void Ball::scaleLineVelocity(float _scale)
{
	lineVelocity *= _scale;
}

void Ball::increaseLineVelocity(float _deltaVel)
{
	int direction = (lineVelocity > 0) - (lineVelocity < 0);
	lineVelocity += _deltaVel * direction;
}