#include "stdafx.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	const b2Body* bodyA = contact->GetFixtureA()->GetBody(), * bodyB = contact->GetFixtureB()->GetBody();
	b2Vec2 velA = bodyA->GetLinearVelocity(), velB = bodyB->GetLinearVelocity();

	uintptr_t actorA = bodyA->GetUserData().pointer, actorB = bodyB->GetUserData().pointer;
	if (actorA) reinterpret_cast<class Character*>(actorA)->OnCollision(velB.LengthSquared() * bodyB->GetMass(), actorB);
	if (actorB) reinterpret_cast<class Character*>(actorB)->OnCollision(velA.LengthSquared() * bodyA->GetMass(), actorA);
}