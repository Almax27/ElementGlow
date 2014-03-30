#include "GameManager.h"

#include "Players/HumanPlayer.h"

#include "Lines/Line.h"
#include "Utility/Rand.h"
#include "Utility/ToFromString.h"

#include <algorithm>

USING_NS_CC;

GameManager::GameManager()
{
	bestTime = 0;
	currentTime = 0;
}

GameManager::~GameManager()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	for(int i = 0; i < players.size(); i++)
	{
		CC_SAFE_RELEASE(players[i]);
	}
	players.clear();
}

bool GameManager::init()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	//FIXME: test
	players[0] = HumanPlayer::create(0, CCRect(origin.x, origin.y, visibleSize.width, visibleSize.height));
	players[0]->retain();

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

	int ballSpeed = 200;
	for(std::list<Line*>::iterator lineIt = activeLines.begin(); lineIt != activeLines.end(); lineIt++)
	{
		(*lineIt)->reset();
		(*lineIt)->spawnBall(0.5f, ballSpeed);
		ballSpeed += 100;
	}

	//FIXME: test
	scoreText = CCLabelTTF::create("", "arial", 24);
	this->addChild(scoreText);
	scoreText->setAnchorPoint(ccp(0.5f, 1.0f));
	scoreText->setPosition(ccp(center.x, visibleSize.height));
	timeText = CCLabelTTF::create("", "arial", 24);
	this->addChild(timeText);
	timeText->setAnchorPoint(ccp(0.5f, 1.0f));
	timeText->setPosition(ccp(center.x, visibleSize.height - 30));
		
	return true;
}

void GameManager::update(float _dt)
{
	currentTime += _dt;

	for(std::list<Line*>::iterator lineIt = activeLines.begin(); lineIt != activeLines.end(); lineIt++)
	{
		(*lineIt)->update(_dt);
	}

	int targetScore = 50;

	//FIXME: end game test
	if(players[0]->getScore() <= 0 || players[0]->getScore() >= targetScore)
	{
		//on Win
		if(players[0]->getScore() >= targetScore)
		{
			if(bestTime == 0 || currentTime < bestTime)
			bestTime = currentTime;
		}

		//reset
		players[0]->setScore(10);
		currentTime = 0;

		int ballSpeed = 200;
		for(std::list<Line*>::iterator lineIt = activeLines.begin(); lineIt != activeLines.end(); lineIt++)
		{
			(*lineIt)->reset();
			(*lineIt)->spawnBall(0.5f, ballSpeed);
			ballSpeed += 100;
		}
	}

	std::string scoreString =	"Score: " + ToString(players[0]->getScore()) + "/" + ToString(targetScore);
	scoreText->setString(scoreString.c_str());

	std::string timeString =	"Time: " + ToString((int)currentTime) +
								" -- Best Time: " + (bestTime == 0 ? "n/a" : ToString(bestTime));
	timeText->setString(timeString.c_str());
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
