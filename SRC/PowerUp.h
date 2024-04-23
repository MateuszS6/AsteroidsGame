#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "GameObject.h"

class PowerUp : public GameObject
{
public:
	PowerUp(const std::string& name);
	~PowerUp(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	string GetTypeName() const;

private:
	string mType;
};

#endif
