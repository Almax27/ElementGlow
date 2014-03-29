#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

#include "Utility/Events/IEventSubscriber.h"

class Event;
class GameManager;

class GameScene : public cocos2d::CCLayer, public IEventSubscriber
{
public:
	GameScene();
	virtual ~GameScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    virtual void update(float dt);
    virtual void onEnter();
    virtual void onExit();

	//IEventSubscriber implemention
	virtual void OnEvent(Event* _event);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

	//touch events
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){};
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){};
	//virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

protected:
	GameManager* gameManager;
};

#endif //_GAME_SCENE_H_