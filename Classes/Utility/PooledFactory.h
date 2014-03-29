//
//  PooledFactory.h
//  Dust
//
//  Created by Aaron Baumbach on 13/12/2013.
//
//

#ifndef __Dust__PooledFactory__
#define __Dust__PooledFactory__

/*Factory class used to instance and pool objects via definitions
 * Each definition implementation should declare an extern global PooledFactory and instance it in their .cpp
 */

#include "Factory.h"

//factory declaration
template<class Tag, class Object> class PooledFactory;

template<class Tag, class Object>
class IPooledFactoryConstructor : public IFactoryConstructor<Tag, Object>
{
public:
	friend class PooledFactory<Tag, Object>;
	IPooledFactoryConstructor<Tag,Object>(Tag _tag)
    : IFactoryConstructor<Tag, Object>(_tag) {}
    
	virtual ~IPooledFactoryConstructor() {}
protected:
	
	//called when an object is added to the pool
	virtual void Reset(Object* _obj) = 0;
private:
};

template<class Tag, class Object>
class PooledFactory : public Factory<Tag, Object>
{
public:
	PooledFactory();
	PooledFactory(IPooledFactoryConstructor<Tag, Object>* _defs[], int _count);
	~PooledFactory();
    
	//Create object
	virtual Object* Create(Tag _tag);
    
    //Pool object
	void Pool(Tag tag, Object* _obj);
    
	int getPoolCount() { return pool.GetCount(); }
    
    virtual void cleanup();
    
private:
	ObjectPool<Tag, Object> pool;
};

//------FACTORY IMPLEMENTATION------
template<class Tag, class Object>
PooledFactory<Tag, Object>::PooledFactory()
{
    
}

template<class Tag, class Object>
PooledFactory<Tag, Object>::PooledFactory(IPooledFactoryConstructor<Tag, Object>* _defs[], int _count)
: Factory<Tag, Object>((IFactoryConstructor<Tag, Object>**) _defs, _count)
{
    
}

template<class Tag, class Object>
PooledFactory<Tag, Object>::~PooledFactory()
{

}

template<class Tag, class Object>
Object* PooledFactory<Tag, Object>::Create(Tag _tag)
{
	if(Factory<Tag, Object>::definitions.count(_tag) > 0)
	{
		IPooledFactoryConstructor<Tag, Object>* def = (IPooledFactoryConstructor<Tag, Object>*) Factory<Tag, Object>::definitions[_tag];
		Object* obj = pool.Pop(_tag);
		if(obj == 0)
		{
			obj = def->Create();
			Factory<Tag, Object>::createdCount++;
		}
		if(obj != 0)
			def->Init(obj);
		return obj;
	}
	else
	{
		DEBUG_LOG_ERROR("Factory failed to create object: invalid tag: " + ToString(_tag));
		return 0;
	}
}

template<class Tag, class Object>
void PooledFactory<Tag, Object>::Pool(Tag _tag, Object* _obj)
{
	if(Factory<Tag, Object>::definitions.count(_tag) > 0)
	{
		pool.Push(_tag, _obj);
        IPooledFactoryConstructor<Tag, Object>* def = (IPooledFactoryConstructor<Tag, Object>*) Factory<Tag, Object>::definitions[_tag];
		def->Reset(_obj); //call reset after to ensure a reference is held
	}
	else
	{
		DEBUG_LOG_ERROR("Factory failed to pool object: invalid tag");
	}
}

template<class Tag, class Object>
void PooledFactory<Tag, Object>::cleanup()
{
    pool.ClearPool();
    Factory<Tag, Object>::cleanup();
}

#endif /* defined(__Dust__PooledFactory__) */
