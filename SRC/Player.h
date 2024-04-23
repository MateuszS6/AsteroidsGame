#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameUtil.h"

#include "GameObject.h"
#include "GameObjectType.h"
#include "IGameWorldListener.h"
#include "IPlayerListener.h"
#include "PowerUp.h"

class Player : public IGameWorldListener
{
public:
	Player() { mLives = 3; }
	virtual ~Player() {}

	void OnWorldUpdated(GameWorld* world) {}

	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {}

	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
	{
		if (object->GetType() == GameObjectType("Spaceship")) {
			mLives -= 1;
			FirePlayerKilled();
		}
		else if (object->GetType() == GameObjectType("PowerUp")) {
			shared_ptr<PowerUp> powerUp = dynamic_pointer_cast<PowerUp>(object);
			if (powerUp) {
				string powerUpName = powerUp->GetTypeName();
				FirePowerUpCollected(powerUpName);
			}
		}
	}

	void AddListener(shared_ptr<IPlayerListener> listener)
	{
		mListeners.push_back(listener);
	}

	void FirePlayerKilled()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit) {
			(*lit)->OnPlayerKilled();
		}
	}

	void FirePowerUpCollected(const string& powerUpName)
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit) {
			(*lit)->OnPowerUpCollected(powerUpName);
		}
	}

	int GetLivesLeft()
	{
		return mLives;
	}

	void AddLife()
	{
		mLives++;
	}

private:
	int mLives;

	typedef std::list< shared_ptr<IPlayerListener> > PlayerListenerList;

	PlayerListenerList mListeners;
};

#endif
