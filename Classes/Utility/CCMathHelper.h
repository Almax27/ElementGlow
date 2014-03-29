#ifndef _CC_MATH_HELPER_H_
#define _CC_MATH_HELPER_H_

#include "cocos2d.h"

namespace cocos2d
{
	/* returns the given rect scaled about it's center */
	CCRect scaleRect(const CCRect& _rect, float _scale)
	{
		CCRect r = _rect;
		r.size = r.size * _scale; //scale rect
		r.origin = r.origin + (_rect.size - r.size) * 0.5f; //correct rect origin
		return r;
	}
}
#endif