#include "ConditionalSystem.h"

#include "IConditional.h"

#include <algorithm>

void ConditionalSystem::addConditional(IConditional* _conditional)
{
	allConditionals.push_back(_conditional);
}

bool ConditionalSystem::removeConditional(IConditional* _conditional)
{
	ConditionalSet::iterator foundConditional;
	foundConditional = std::find(allConditionals.begin(), allConditionals.end(), _conditional);
	if(foundConditional != allConditionals.end())
	{
		allConditionals.erase(foundConditional);

		foundConditional = std::find(activeConditionals.begin(), activeConditionals.end(), _conditional);
		activeConditionals.erase(foundConditional);

		return true;
	}
	return false;
}

const ConditionalSystem::ConditionalSet& ConditionalSystem::getActiveConditionals()
{
	return activeConditionals;
}

void ConditionalSystem::update(float _dt)
{
	ConditionalSet::iterator it;

	//update active conditionals and handle their deactivation
	for(it = activeConditionals.begin(); it != activeConditionals.end(); it++)
	{
		IConditional* conditional = *it;
		conditional->onUpdate(_dt);
		if(conditional->isConditionMet() == false)
		{
			conditional->onDeactivated();
			it = activeConditionals.erase(it);
		}
	}

	//check for conditionals to become active
	for(it = allConditionals.begin(); it != allConditionals.end(); it++)
	{
		IConditional* conditional = *it;
		if(conditional->isConditionMet())
		{
			if(singleActive)
			{
				activeConditionals.clear();
				activeConditionals.push_back(conditional);
				conditional->onActivated();
				break;
			}
			else
			{
				activeConditionals.push_back(conditional);
				conditional->onActivated();
			}
		}
	}
}

void ConditionalSystem::setSingleActive(bool _singleActive)
{
	singleActive = _singleActive;
}

bool ConditionalSystem::getSingleActive()
{
	return singleActive;
}