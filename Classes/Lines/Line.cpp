#include "Line.h"
#include "Balls/Ball.h"
#include "Paddles/Paddle.h"

#include "Utility/Rand.h"
#include "Resources.h"


USING_NS_CC;

Line::Line()
{
	lineGraphic = NULL;
}

Line::~Line()
{
	unsubscribeAll();
}

Line* Line::create(const cocos2d::CCPoint& _startPos, const cocos2d::CCPoint& _endPos)
{
	Line* line = new Line();

	if(line->init(_startPos, _endPos))
	{
		line->autorelease();
		return line;
	}

	CC_SAFE_DELETE(line);
	return NULL;
}

bool Line::init(const cocos2d::CCPoint& _startPos, const cocos2d::CCPoint& _endPos)
{
	//create line graphic
	lineGraphic = CCSprite::create(SpriteResource::line);
	this->addChild(lineGraphic);

	startPos = _startPos;
	endPos = _endPos;
	updateLineGraphic();

	paddleMap[0] = Paddle::create(this, 0, 50);
	this->addChild(paddleMap[0]);
	paddleMap[1] = Paddle::create(this, this->getLength(),  this->getLength() - 50);
	this->addChild(paddleMap[1]);

	unsubscribeAll();
	subscribe("PlayerTouch");

	spawnBall(0.5f, 500 * randf(0.5f, 1.0f));

	return CCNode::init();
}

void Line::update(float _dt)
{
	for(std::list<Ball*>::iterator it = activeBalls.begin(); it != activeBalls.end(); it++)
	{
		(*it)->update(_dt);		
	}
}

void Line::OnEvent(Event* _event)
{
	if(_event->isType("PlayerTouch"))
	{
		unsigned int playerIndex = (unsigned int) _event->getData();
		triggerPaddle(playerIndex);
	}
}

void Line::spawnBall(float _relPos, float _velocity)
{
	Ball* newBall = Ball::create(this);
	newBall->setLinePos(this->getLength() * _relPos);
	newBall->setLineVelocity(_velocity);

	this->addChild(newBall);
	activeBalls.push_back(newBall);
}

void Line::triggerPaddle(unsigned int _playerIndex)
{
	if(paddleMap.count(_playerIndex))
	{
		paddleMap[_playerIndex]->triggerPaddle();
	}
	else
	{
		CCLOG("No paddle exists for player %i", _playerIndex);
	}
}

const CCPoint& Line::getStartPos()
{
	return startPos;
}

void Line::setStartPos(const CCPoint& _position)
{
	startPos = _position;
	updateLineGraphic();
}

const CCPoint& Line::getEndPos()
{
	return endPos;
}

void Line::setEndPos(const CCPoint& _position)
{
	endPos = _position;
	updateLineGraphic();
}

CCPoint Line::getPointFromAbsDistance(float _absDistance)
{
	return startPos + ((endPos - startPos).normalize() * _absDistance);
}

CCPoint Line::getPointFromRelDistance(float _relDistance)
{
	return startPos.lerp(endPos, _relDistance);
}

void Line::updateLineGraphic()
{
	if(lineGraphic != NULL)
	{
		lineGraphic->setAnchorPoint(ccp(0.5f,0.5f));
		lineGraphic->setPosition((endPos + startPos) * 0.5f);

		float rotation = CC_RADIANS_TO_DEGREES((endPos - startPos).getAngle());
		lineGraphic->setRotation(-rotation);

		//TODO: Make this a 9slice?
		float xScale = (endPos - startPos).getLength() / lineGraphic->getContentSize().width;
		lineGraphic->setScaleX(xScale);
	}
}