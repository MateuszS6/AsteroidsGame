#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include "GameSession.h"
#include "IKeyboardListener.h"
#include "GameUtil.h"
#include "IGameWorldListener.h"
#include "IKeyboardListener.h"
#include "IPlayerListener.h"
#include "IScoreListener.h" 
#include "ScoreKeeper.h"
#include "Player.h"
#include "IPlayerListener.h"
#include "ScoreKeeper.h"
#include "Asteroid.h"
#include <vector>

class GameObject;
class Spaceship;
class GUILabel;

class Asteroids : public GameSession, public IKeyboardListener, public IGameWorldListener, public IScoreListener, public IPlayerListener
{
public:
	Asteroids(int argc, char *argv[]);
	virtual ~Asteroids(void);

	virtual void Start(void);
	virtual void Stop(void);

	// Declaration of IKeyboardListener interface ////////////////////////////////

	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

	// Declaration of IScoreListener interface //////////////////////////////////

	void OnScoreChanged(int score);

	// Declaration of the IPlayerLister interface //////////////////////////////

	void OnPlayerKilled();
	void OnPowerUpCollected(const string& powerUpType);

	// Declaration of IGameWorldListener interface //////////////////////////////

	void OnWorldUpdated(GameWorld* world) {}
	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {}
	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object);

	// Override the default implementation of ITimerListener ////////////////////

	void OnTimer(int value);

private:
	shared_ptr<Spaceship> mSpaceship;
	shared_ptr<GUILabel> mScoreLabel;
	shared_ptr<GUILabel> mLivesLabel;
	shared_ptr<GUILabel> mGameOverLabel;
	shared_ptr<GUILabel> mTitleLabel;
	shared_ptr<GUILabel> mStartLabel;
	shared_ptr<GUILabel> mSelectLabel;
	shared_ptr<GUILabel> mPowerUpLabel;
	shared_ptr<GUILabel> mControlsLabel;

	vector<shared_ptr<Asteroid>> mAsteroidList;

	uint mLevel;
	uint mAsteroidCount;
	bool mGameStarted;
	string mSpaceshipSpriteName;
	bool mIsBulletCooldownActive;
	bool mIsTimeSlowed;

	shared_ptr<GameObject> CreateSpaceship();
	void SetSpaceshipSprite(const string& name);
	void CreateAsteroids(const uint num_asteroids);
	void CreatePowerUp();
	void ToggleSlowMotion(bool activate);
	void TogglePhasing(bool activate);
	void ToggleBulletCooldown(bool activate);
	void CreateGUI();
	void CreateStartScreen();
	void UpdateLivesLabel();
	void UpdatePowerUpLabel(const string& text, const GLVector3f& colour);
	shared_ptr<GameObject> CreateExplosion();
	
	const static uint SHOW_GAME_OVER = 0;
	const static uint START_NEXT_LEVEL = 1;
	const static uint CREATE_NEW_PLAYER = 2;
	const static uint SPAWN_NEXT_POWERUP = 3;
	const static uint END_SLOW_MOTION = 4;
	const static uint END_PHASING = 5;
	const static uint END_BULLET_COOLDOWN = 6;

	ScoreKeeper mScoreKeeper;
	Player mPlayer;
};

#endif