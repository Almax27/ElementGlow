#ifndef _LINE_SPRITE_HELPER_H_
#define _LINE_SPRITE_HELPER_H_

#include "cocos2d.h"

static void PlaceLineSprite(cocos2d::CCSprite* _sprite, const cocos2d::CCPoint& _startPos, const cocos2d::CCPoint& _endPos)
{
	_sprite->setAnchorPoint(ccp(0.5f,0.5f));
	_sprite->setPosition((_endPos + _startPos) * 0.5f);

	float rotation = CC_RADIANS_TO_DEGREES((_endPos - _startPos).getAngle());
	_sprite->setRotation(-rotation);

	//TODO: Make this a 9slice?
	float xScale = (_endPos - _startPos).getLength() / _sprite->getContentSize().width;
	_sprite->setScaleX(xScale);
}

#endif