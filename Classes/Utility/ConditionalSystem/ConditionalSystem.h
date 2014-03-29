#ifndef _CONDITIONAL_SYSTEM_H_
#define _CONDITIONAL_SYSTEM_H_

#include <vector>

class IConditional;

class ConditionalSystem
{
public:

	typedef std::vector<IConditional*> ConditionalSet;

	/* add conditional to the inactive set, will be tested in next update() */
	void addConditional(IConditional* _conditional);
	/* remove conditional from system, returns false given conditional was not found */
	bool removeConditional(IConditional* _conditional);

	/* returns active conditionals */
	const ConditionalSet& getActiveConditionals();

	/* update and manage conditions */
	void update(float _dt);

	/* set if only one conditional can be active at any given time */
	void setSingleActive(bool _singleActive);
	/* get if only one conditional can be active at any given time */
	bool getSingleActive();
	

protected:
	bool singleActive;
	ConditionalSet activeConditionals;
	ConditionalSet allConditionals;

private:
};

#endif //_CONDITIONAL_SYSTEM_H_