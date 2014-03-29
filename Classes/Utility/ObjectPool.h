
#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <map>
#include <stack>

/* Object pool can be used to group objects together under a given tag
*/

template<class Tag, class Object>
class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();

	/*push new object onto the stack with the given tag
	* will create new stack if one doesn't exist already */
	void Push(Tag _tag, Object* _obj);

	/*pop from the stack with the given tag
	* returns 0 if there is no matching stack or it is empty */
	Object* Pop(Tag _tag);

	//deletes all pooled objects
	void DeletePool();

	//removed all objects from pool - does not delete memory allocations
	void ClearPool();

	int GetCount() {return count;}

protected:
	int count;
	typedef std::map< Tag, std::stack<Object*> > PoolMap;
	PoolMap poolMap;
private:
};

//----IMPLEMENTATION----

template<class Tag, class Object>
ObjectPool<Tag, Object>::ObjectPool()
{
}

template<class Tag, class Object>
ObjectPool<Tag, Object>::~ObjectPool()
{
}

template<class Tag, class Object>
void ObjectPool<Tag, Object>::Push(Tag _tag, Object* _obj)
{
	poolMap[_tag].push(_obj);
	count++;
}

template<class Tag, class Object>
Object* ObjectPool<Tag, Object>::Pop(Tag _tag)
{
	Object* obj = 0;
	std::stack<Object*>& pool = poolMap[_tag];
	if(pool.size() > 0)
	{
		obj = pool.top();
		pool.pop();
		count--;
	}
	return obj;
}

template<class Tag, class Object>
void ObjectPool<Tag, Object>::DeletePool()
{
	typename PoolMap::iterator mapIter;
	for(mapIter = poolMap.begin(); mapIter != poolMap.end(); mapIter++)
	{
		Object* obj = mapIter->second.top();
		while(obj)
		{
			delete obj;
			mapIter->second.pop(); //pop the one we deleted
			obj = mapIter->second.top(); //get next
		}
	}
	ClearPool();
}

template<class Tag, class Object>
void ObjectPool<Tag, Object>::ClearPool()
{
	poolMap.clear();
	count = 0;
}
//----------------------

#endif //__OBJECT_POOL_H__
