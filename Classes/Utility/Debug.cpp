#include "Debug.h"

#include "cocos2d.h"

namespace Debug
{
	void Log(std::string msg)
	{
		CCLOG(msg.c_str());
	}

	void LogError(std::string msg)
	{
		CCLOGERROR(msg.c_str());
	}
}
