
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>

namespace Debug
{
	void Log(std::string msg);
	void LogError(std::string msg);
}

#define DEBUG_ASSERT(c,s) c ? Debug::Log(s)
#define DEBUG_LOG(s) Debug::Log(s)
#define DEBUG_LOG_ERROR(s) Debug::LogError(s)

#endif //__DEBUG_H__
