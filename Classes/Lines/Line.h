#ifndef _LINE_H_
#define _LINE_H_

#include "cocos2d.h"
#include "Utility/Events/IEventSubscriber.h"

#include <list>
#include <map>

class Ball;
class Paddle;

class Line : public cocos2d::CCNode, public IEventSubscriber
{
public:
	virtual ~Line();

	static Line* create(const cocos2d::CCPoint& _startPos, const cocos2d::CCPoint& _endPos);

	virtual bool init(const cocos2d::CCPoint& _startPos, const cocos2d::CCPoint& _endPos);
	virtual void update(float _dt);

	//IEventSubscriber
	virtual void OnEvent(Event* _event);

	//helper methods
	void spawnBall(float _relPos, float _velocity);
	void triggerPaddle(unsigned int _playerIndex);

	CC_PROPERTY_PASS_BY_REF(cocos2d::CCPoint, startPos, StartPos);
	CC_PROPERTY_PASS_BY_REF(cocos2d::CCPoint, endPos, EndPos);

	float getLength() { return startPos.getDistance(endPos); }
	float getLengthSq() { return startPos.getDistanceSq(endPos); }

	//converts an absolute distance along the line to a GL point local to this object
	cocos2d::CCPoint getPointFromAbsDistance(float _absDistance);
	//converts an relative distance along the line to a GL point local to this object
	cocos2d::CCPoint getPointFromRelDistance(float _relDistance);

	const std::list<Ball*>& getActiveBalls() { return activeBalls; }

protected:
	Line();

	std::map<int, Paddle*> paddleMap;
	cocos2d::CCSprite* lineGraphic;
	void updateLineGraphic();

	std::list<Ball*> activeBalls;

private:
};

#endif //_LINE_H_