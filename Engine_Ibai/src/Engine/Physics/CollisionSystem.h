#ifndef COLLISION_H_
#define COLLISION_H_
// ---------------------------------------------------------------------------
#include "../Math/Collisions.h"
#include "../Math/ContactCollisions.h"
#include "RigidBody.h"

// Collision restitution for velocity resolution
#define DFLT_RESTITUTION 0.908f;

/* @README
The functions below are provided for you. They are "wrapper functions" around collision tests.
These serve as the link between the collision library (the tests) and the physics/collision system. 
In fact, they are the ones that actually call the functions in ContactCollisions.h.
	
Note that they all have the same signature. This is so that we can refer to them 
via function pointers (see typedef below). This allows us to store these functions 
as function pointers in the collision system following the method discussed in class.
(see mCollisionTests member variables of CollisionSystem below).
	
Finally	the functions guarantee that contact viewer is always body1. This is the 
convention we followed in class. 
*/
bool CollideCircles(RigidBody* body1, RigidBody* body2, Contact * c);
bool CollideAABBs(RigidBody* body1, RigidBody* body2, Contact * c);
bool CollideOBBs(RigidBody* body1, RigidBody* body2, Contact * c);
bool CollideAABBToCircle(RigidBody* body1, RigidBody* body2, Contact * c);
bool CollideOBBToCircle(RigidBody* body1, RigidBody* body2, Contact * c);
// typedef for function pointer CollisionFn
typedef bool(*CollisionFn)(RigidBody*, RigidBody*, Contact *);

/*!



*/
struct CollisionSystem
{
	// ------------------------------------------------------------------------
	// Member Variables
	std::list<RigidBody*> mStaticBodies;
	std::list<RigidBody*> mDynamicBodies;

	// Collision iterations
	u32 mCollisionIterations;
	u32 mCollisionsThisFrame; // collisions this frame

	// Collision Tests -They are added to the collision system at initialize. 
	// (see CollisionSystem::Init) for more details.
	CollisionFn mCollisionTests[CSHAPE_INDEX_MAX];

	// ------------------------------------------------------------------------
	// Member Functions

	// System Functions
	void Init();
	void Update();
	void Shutdown();

	// Rigid Body Management
	void AddRigidBody(RigidBody* obj, bool is_dynamic);
	void RemoveRigidBody(RigidBody *obj);
	void ClearBodies();

	// findeing the collision tests
	CollisionFn GetCollisionFn(RigidBody * b1, RigidBody * b2);

	// Collides and resolve all rigidbodies 
	void CollideAllBodies();

	// Exposed solver
	void ResolveContactPenetration(RigidBody * obj1, RigidBody * obj2, Contact * contact);
	void ResolveContactVelocity(RigidBody * obj1, RigidBody * obj2, Contact * contact);
};

extern CollisionSystem gCollisionSystem;

// ---------------------------------------------------------------------------
#endif