#include "PowerUp.h"
#include "BoundingShape.h"
#include "Spaceship.h"

PowerUp::PowerUp(const string& name)
    : GameObject("PowerUp"), mType(name)
{
    mPosition.x = rand() / 2;
    mPosition.y = rand() / 2;
    mPosition.z = 0.0;
}

PowerUp::~PowerUp()
{
}

bool PowerUp::CollisionTest(shared_ptr<GameObject> o)
{
    return false;
}

void PowerUp::OnCollision(const GameObjectList& objects)
{
    mWorld->FlagForRemoval(GetThisPtr());
}

string PowerUp::GetTypeName() const
{
    return mType;
}