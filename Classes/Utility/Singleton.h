/*
 * Singleton.h
 *
 *  Created on: 12 Oct 2013
 *      Author: Almax
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

template <class T>
class Singleton
{
public:
	static T& Get()
	{
		static T instance;
		return instance;
	};
	virtual ~Singleton(){}
protected:
	Singleton(){}
};

#endif /* SINGLETON_H_ */
