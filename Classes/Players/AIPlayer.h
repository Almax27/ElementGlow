#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include "Player.h"

class AIPlayer : public Player
{
public:
	virtual ~AIPlayer();

	static AIPlayer* create(unsigned int _playerIndex);

	virtual bool init();
	virtual void update(float _dt);

protected:
	AIPlayer(unsigned int _playerIndex);

private:
};

#endif //_AI_PLAYER_H_