#include "GameScene.h"

#include "Utility/Events/EventManager.h"
#include "GameManager.h"

#include "Resources.h"

USING_NS_CC;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	unscheduleAllSelectors();
}

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameScene::init()
{
	//////////////////////////////
    // super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	scheduleUpdateWithPriority(1); //late update

	gameManager = GameManager::create();
	this->addChild(gameManager);

	return true;
}

void GameScene::update(float dt)
{    
	CCLayer::update(dt);
	
	gameManager->update(dt);

	EventManager::Get().processEvents();
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
}

void GameScene::onExit()
{
    CCLayer::onExit();
}

void GameScene::OnEvent(Event* _event)
{
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    return false; //never eat the input
}
