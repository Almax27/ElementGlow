#include "GameManager.h"

#include "Players/HumanPlayer.h"

#include "Lines/Line.h"
#include "Utility/Rand.h"

#include <algorithm>

USING_NS_CC;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GameManager::init()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	//FIXME: test
	players[0] = HumanPlayer::create(0, CCRect(origin.x, origin.y, visibleSize.width, visibleSize.height));

	//FIXME: test
	float lineOffset = 80;
	float lineHalfWidth = 250;

	Line* testLine1 = Line::create(	ccp(center.x - lineHalfWidth, center.y - lineOffset), 
									ccp(center.x + lineHalfWidth, center.y - lineOffset));
	this->addChild(testLine1);
	activeLines.push_back(testLine1);

	Line* testLine2 = Line::create(	ccp(center.x - lineHalfWidth, center.y + 0), 
									ccp(center.x + lineHalfWidth, center.y + 0));
	this->addChild(testLine2);
	activeLines.push_back(testLine2);

	Line* testLine3 = Line::create(	ccp(center.x - lineHalfWidth, center.y + lineOffset), 
									ccp(center.x + lineHalfWidth, center.y + lineOffset));
	this->addChild(testLine3);
	activeLines.push_back(testLine3);

	return true;
}

void GameManager::update(float _dt)
{
	for(std::list<Line*>::iterator lineIt = activeLines.begin(); lineIt != activeLines.end(); lineIt++)
	{
		(*lineIt)->update(_dt);
	}
}

//CCTargetedTouchDelegate
bool GameManager::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
	return false;
}

void GameManager::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void GameManager::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void GameManager::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}