#include "GameWorld.h"
#include "Bullet.h"
#include "BoundingSphere.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. Bullets live for 2s and are regular bullets, by default. */
Bullet::Bullet()
	: GameObject("Bullet"), mTimeToLive(2000), mIsPowerUpBullet(false)
{
}

/** Construct a new bullet with given position, velocity, acceleration, angle, rotation and lifespan. */
Bullet::Bullet(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl, bool ipub)
	: GameObject("Bullet", p, v, a, h, r), mTimeToLive(ttl), mIsPowerUpBullet(ipub)
{
}

/** Copy constructor. */
Bullet::Bullet(const Bullet& b)
	: GameObject(b),
	  mTimeToLive(b.mTimeToLive),
	mIsPowerUpBullet(b.mIsPowerUpBullet)
{
}

/** Destructor. */
Bullet::~Bullet(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update bullet, removing it from game world if necessary. */
void Bullet::Update(int t)
{
	// Update position/velocity
	GameObject::Update(t);
	// Reduce time to live
	mTimeToLive = mTimeToLive - t;
	// Ensure time to live isn't negative
	if (mTimeToLive < 0) { mTimeToLive = 0; }
	// If time to live is zero then remove bullet from world
	if (mTimeToLive == 0) {
		if (mWorld) mWorld->FlagForRemoval(GetThisPtr());
	}

}

bool Bullet::CollisionTest(shared_ptr<GameObject> o)
{
	// Check if the bullet is a power-up bullet
	if (mIsPowerUpBullet) {
		// Power-up bullets only collide with power-ups
		if (o->GetType() == GameObjectType("PowerUp"))
			return mBoundingShape->CollisionTest(o->GetBoundingShape());
		else return false;
	}
	// Normal bullets only collide with asteroids
	if (o->GetType() != GameObjectType("Asteroid")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Bullet::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}
