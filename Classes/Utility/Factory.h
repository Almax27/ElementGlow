
#ifndef __FACTORY_H__
#define __FACTORY_H__

/*Factory class used to instance and pool objects via definitions
 * Each definition implementation should declare an extern global factory and instance it in their .cpp
 */

#include <map>
#include <vector>
#include "ObjectPool.h"
#include "Debug.h"
#include "Singleton.h"
#include "ToFromString.h"
#include "Utility/Events/IEventSubscriber.h"

//factory Event definition
#define EVENT_CLEANUP_ALL_FACTORIES "cleanupAllFactories"

//factory declaration
template<class Tag, class Object> class Factory;

template<class Tag, class Object>
class IFactoryConstructor
{
public:
	friend class Factory<Tag, Object>;
	IFactoryConstructor<Tag,Object>(Tag _tag)
    : tag(_tag) {}
    
	Tag GetTag() const { return tag; }
    
	virtual ~IFactoryConstructor() {}
protected:
	//called when a new object is to be created
	virtual Object* Create() = 0;
	//caled before an object is returned from Factory::Create()
	virtual void Init(Object* _obj) = 0;
    //called when the factory is requested to cleanup
    virtual void Cleanup() {};
private:
	Tag tag;
};

template<class Tag, class Object>
class Factory : IEventSubscriber
{
public:
	Factory();
	Factory(IFactoryConstructor<Tag, Object>* _defs[], int _count);
	~Factory();
    
    //IEventSubscriber
    virtual void OnEvent(Event* _event);
    
	//Create object
	virtual Object* Create(Tag _tag);
    
	//Factory will assume responsibility for deleting the definitions
	void RegisterConstructor(IFactoryConstructor<Tag, Object>* _def);
	void RegisterConstructorSet(IFactoryConstructor<Tag, Object>* _defs[], int _count);
    
	int getCreatedCount() { return createdCount; }
    
    virtual void cleanup();
    
protected:
	int createdCount;
	typedef std::map<Tag, IFactoryConstructor<Tag, Object>*> DefinitionMap;
	DefinitionMap definitions;
};

//------FACTORY IMPLEMENTATION------
template<class Tag, class Object>
Factory<Tag, Object>::Factory()
{
    subscribe(EVENT_CLEANUP_ALL_FACTORIES);
}

template<class Tag, class Object>
Factory<Tag, Object>::Factory(IFactoryConstructor<Tag, Object>* _defs[], int _count)
{
    subscribe(EVENT_CLEANUP_ALL_FACTORIES);
	RegisterConstructorSet(_defs, _count);
}

template<class Tag, class Object>
Factory<Tag, Object>::~Factory()
{
    unsubscribeAll();
	//cleanup definitions
	typename std::map<Tag, IFactoryConstructor<Tag, Object>*>::iterator iter;
	for(iter = definitions.begin(); iter != definitions.end(); iter++)
	{
		delete iter->second;
	}
    definitions.clear();
    cleanup();
}

template<class Tag, class Object>
void Factory<Tag, Object>::OnEvent(Event* _event)
{
    if(_event->isType(EVENT_CLEANUP_ALL_FACTORIES))
    {
        cleanup();
    }
}

template<class Tag, class Object>
Object* Factory<Tag, Object>::Create(Tag _tag)
{
	if(definitions.count(_tag) > 0)
	{
		IFactoryConstructor<Tag, Object>* def = definitions[_tag];
		Object* obj = def->Create();
			
		if(obj != 0)
        {
            createdCount++;
			def->Init(obj);
        }
        
		return obj;
	}
	else
	{
		DEBUG_LOG_ERROR("Factory failed to create object: invalid tag: " + ToString(_tag));
		return 0;
	}
}

template<class Tag, class Object>
void Factory<Tag, Object>::RegisterConstructor(IFactoryConstructor<Tag, Object>* _def)
{
	if(definitions.count(_def->GetTag()) == 0)
	{
		definitions[_def->GetTag()] = _def;
	}
	else
	{
		DEBUG_LOG_ERROR("Factory failed to add IFactoryConstructor: tag in use");
	}
}

template<class Tag, class Object>
void Factory<Tag, Object>::RegisterConstructorSet(IFactoryConstructor<Tag, Object>* _defs[], int _count)
{
	for(int i = 0; i < _count; i++)
	{
		RegisterConstructor(_defs[i]);
	}
}

template<class Tag, class Object>
void Factory<Tag, Object>::cleanup()
{
    typename std::map<Tag, IFactoryConstructor<Tag, Object>*>::iterator iter;
	for(iter = definitions.begin(); iter != definitions.end(); iter++)
	{
		iter->second->Cleanup();
	}
}
//----------------------------------

#endif //__IFACTORY_H__
