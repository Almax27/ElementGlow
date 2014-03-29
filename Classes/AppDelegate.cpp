#include "AppDelegate.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

typedef struct tagResource
{
    cocos2d::CCSize size;
    std::string directory;
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(640, 360),   "small" };
static Resource largeResource =  { cocos2d::CCSizeMake(1280, 720),  "large"   };
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1280, 720);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{

}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

	//setup multiresolution support
	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedHeight);
	
	CCSize frameSize = pEGLView->getFrameSize();

	std::vector<std::string> searchPath;

	searchPath.push_back(largeResource.directory);
    pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
	/*
    if (frameSize.height > smallResource.size.height)
    { 
        searchPath.push_back(largeResource.directory);
        pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
    }
    else
    { 
        searchPath.push_back(smallResource.directory);
        pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
    }*/

	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	pDirector->setProjection(kCCDirectorProjection2D);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
