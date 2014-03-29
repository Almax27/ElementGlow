#ifndef ToFromString_h
#define ToFromString_h

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

template <typename T>
std::string ToString (const T &t)
{
	std::ostringstream os;
	os << t;
	return os.str();
}

template <typename T>
std::string ToStringWithPrecision(const T& t, int precision)
{
	std::ostringstream os;
	os  << std::fixed << std::setprecision(precision) << t;
	return os.str();
}

template <typename T>
T FromString (const std::string &str)
{
	std::istringstream is(str);
	T t;
	is >> t;
	return t;
}


#endif
