#include "PowerUp.h"
#include "BoundingShape.h"
#include "Spaceship.h"

PowerUp::PowerUp(const std::string& name)
    : GameObject("PowerUp"), mPowerUpName(name)
{
    mPosition.x = rand() / 2;
    mPosition.y = rand() / 2;
    mPosition.z = 0.0;
}

PowerUp::~PowerUp()
{
}

bool PowerUp::CollisionTest(std::shared_ptr<GameObject> o)
{
    return false;
}

void PowerUp::OnCollision(const GameObjectList& objects)
{
    mWorld->FlagForRemoval(GetThisPtr());
}

std::string PowerUp::GetName() const
{
    return mPowerUpName;
}