#ifndef __IPLAYERLISTENER_H__
#define __IPLAYERLISTENER_H__

class IPlayerListener
{
public:
	virtual void OnPlayerKilled() = 0;
	virtual void OnPowerUpCollected(const string& powerUpType) = 0;
};

#endif
