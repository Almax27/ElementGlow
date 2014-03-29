#ifndef _CONDITIONAL_H_
#define _CONDITIONAL_H_

class IConditional
{
public:

	/* Derived classes must implement a condition to be tested for this instance to activate */
	virtual bool isConditionMet() = 0;

	/* Called when the instance is actived by isConditionMet() returning true. */
	void onActivated() {}
	/* Called when the instance is deactivated by isConditionMet() returning false. */
	void onDeactivated() {}

	/* Called each frame while active */
	void onUpdate(float dt) {}

protected:
private:
};

#endif //_CONDITIONAL_H_