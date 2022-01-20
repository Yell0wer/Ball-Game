#pragma once

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class ControllerComponent : public Component
{
public:
	ControllerComponent(class Character* actor);

protected:
	void Move(bool l, b2Body* body);
	void Jump(float delta, b2Body* body);
	void Shoot(b2Vec2 dir);

	b2Vec2 mAcceleration;
	float mCooldown, mShootTimer, mJumpTimer;
	bool mIsGrounded, mWasGrounded, mJumpGrounded;
	int mNumJumps;
	class Character* mOwner;
	float mSpeedLim, mShootPower;
};

class RayCastCallback : public b2RayCastCallback
{
public:
	RayCastCallback() : m_fixture(nullptr) {}

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		return fraction;
	}

	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float m_fraction;
};