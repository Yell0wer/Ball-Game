#include "stdafx.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	const b2Body* bodyA = contact->GetFixtureA()->GetBody();
	const b2Body* bodyB = contact->GetFixtureB()->GetBody();
	b2Vec2 velA = bodyA->GetLinearVelocity(), velB = bodyB->GetLinearVelocity();

	uintptr_t actorA = bodyA->GetUserData().pointer;
	uintptr_t actorB = bodyB->GetUserData().pointer;
	if (actorA) reinterpret_cast<class Player*>(actorA)->OnCollision(velB.LengthSquared() * bodyB->GetMass() / 2.f, actorB);
	if (actorB) reinterpret_cast<class Player*>(actorB)->OnCollision(velA.LengthSquared() * bodyA->GetMass() / 2.f, actorA);
}