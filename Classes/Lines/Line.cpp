#include "Line.h"
#include "Balls/Ball.h"
#include "Paddles/Paddle.h"

#include "Utility/LineSpriteHelper.h"
#include "Utility/Rand.h"
#include "Utility/Events/EventManager.h"
#include "Resources.h"

#include "SimpleAudioEngine.h"

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
	if(CCNode::init() == false)
	{
		return false;
	}

	//create line graphic
	lineGraphic = CCSprite::create(SpriteResource::line);
	this->addChild(lineGraphic);

	this->setStartPos(_startPos);
	this->setEndPos(_endPos);
	updateLineGraphic();

	paddleMap[0] = Paddle::create(this, 0, 100);
	this->addChild(paddleMap[0]);
	paddleMap[1] = Paddle::create(this, this->getLineLength(),  this->getLineLength() - 100);
	this->addChild(paddleMap[1]);

	unsubscribeAll();
	subscribe("PlayerTouch");

	spawnBall(0.5f, 500 * randf(0.5f, 1.0f));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(AudioResource::hit);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(AudioResource::miss);

	return true;
}

void Line::update(float _dt)
{
	for(std::list<Ball*>::iterator it = activeBalls.begin(); it != activeBalls.end(); it++)
	{
		Ball* ball = *it;

		ball->update(_dt);		

		if(ball->getLinePos() <= 0 && ball->getLineVelocity() < 0)
		{
			onPlayerMissedBall(ball, 0);
		}
		else if(ball->getLinePos() >= this->getLineLength() && ball->getLineVelocity() > 0)
		{
			onPlayerMissedBall(ball, 1);
		}
	}
}

void Line::OnEvent(Event* _event)
{
	if(_event->isType("PlayerTouch"))
	{
		unsigned int playerIndex = (int) _event->getData();
		triggerPaddle(playerIndex);
	}
}

void Line::onPlayerHitBall(Ball* _ball, int _playerIndex)
{
	if(_ball->getLastPlayerIndex() != _playerIndex)
	{
		_ball->setLastPlayerIndex(_playerIndex);
		_ball->reverseVelocity();
		_ball->increaseLineVelocity(40);
		EventManager::Get().publishEvent(new Event("PlayerHit", (void*)_playerIndex));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(AudioResource::hit);
	}
}

void Line::onPlayerMissedBall(Ball* _ball, int _playerIndex)
{
	_ball->reverseVelocity();

	if(_ball->getLastPlayerIndex() != _playerIndex)
	{
		_ball->setLastPlayerIndex(_playerIndex);
		_ball->increaseLineVelocity(-10);
		EventManager::Get().publishEvent(new Event("PlayerMissed", (void*)_playerIndex));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(AudioResource::miss);
	}
}

void Line::spawnBall(float _relPos, float _velocity)
{
	Ball* newBall = Ball::create(this);
	newBall->setLinePos(this->getLineLength() * _relPos);
	newBall->setLineVelocity(_velocity);

	this->addChild(newBall);
	activeBalls.push_back(newBall);
}

void Line::triggerPaddle(int _playerIndex)
{
	if(paddleMap.count(_playerIndex))
	{
		paddleMap[_playerIndex]->triggerPaddle(_playerIndex);
	}
	else
	{
		CCLOG("No paddle exists for player %i", _playerIndex);
	}
}

void Line::reset()
{
	for(std::list<Ball*>::iterator it = activeBalls.begin(); it != activeBalls.end(); it++)
	{
		this->removeChild((*it), true);
	}
	activeBalls.clear();
}

const CCPoint& Line::getStartPos()
{
	return startPos;
}

void Line::setStartPos(const CCPoint& _position)
{
	startPos = _position;
	lineLength = startPos.getDistance(endPos);
	updateLineGraphic();
}

const CCPoint& Line::getEndPos()
{
	return endPos;
}

void Line::setEndPos(const CCPoint& _position)
{
	endPos = _position;
	lineLength = startPos.getDistance(endPos);
	updateLineGraphic();
}

CCPoint Line::getPointFromAbsDistance(float _absDistance)
{
	return startPos + ((endPos - startPos).normalize() * clampf(_absDistance,0,lineLength));
}

CCPoint Line::getPointFromRelDistance(float _relDistance)
{
	return startPos.lerp(endPos, clampf(_relDistance,0,1));
}

void Line::updateLineGraphic()
{
	if(lineGraphic != NULL)
	{
		PlaceLineSprite(lineGraphic, startPos, endPos);
	}
}
