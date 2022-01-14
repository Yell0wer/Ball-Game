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
	ControllerComponent(class DynamicActor* actor);

	void ProcessInput(const uint8_t* keyState) override;
	void Update(float delta) override;

	bool IsGrounded();

	int GetLeft() const { return mLeft; }
	int GetRight() const { return mRight; }
	int GetJump() const { return mJump; }
	int GetShoot() const { return mShoot; }
	int GetCrouch() const { return mCrouch; }
	void SetLeft(SDL_Scancode key) { mLeft = key; }
	void SetRight(SDL_Scancode key) { mRight = key; }
	void SetJump(SDL_Scancode key) { mJump = key; }
	void SetShoot(SDL_Scancode key) { mShoot = key; }
	void SetCrouch(SDL_Scancode key) { mCrouch = key; }

private:
	ButtonState GetKeyState(SDL_Scancode key) const;

	class DynamicActor* mOwner;
	float mSpeedLim;
	SDL_Scancode mLeft, mRight, mJump, mShoot, mCrouch;
	uint8_t mCurrState[SDL_NUM_SCANCODES], mPrevState[SDL_NUM_SCANCODES];
};

