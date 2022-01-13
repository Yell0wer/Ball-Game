#pragma once

class ControllerComponent : public Component
{
public:
	ControllerComponent(class Actor* actor);

	void ProcessInput(const uint8_t* keyState) override;

	int GetLeft() const { return mLeft; }
	int GetRight() const { return mRight; }
	int GetJump() const { return mJump; }
	int GetShoot() const { return mShoot; }
	int GetCrouch() const { return mCrouch; }
	void SetLeft(int key) { mLeft = key; }
	void SetRight(int key) { mRight = key; }
	void SetJump(int key) { mJump = key; }
	void SetShoot(int key) { mShoot = key; }
	void SetCrouch(int key) { mCrouch = key; }

private:
	int mLeft, mRight, mJump, mShoot, mCrouch;
};

