#pragma once

class PlayerControllerComponent : public ControllerComponent
{
public:
	PlayerControllerComponent(class Player* actor);

	void ProcessInput(const uint8_t* keyState) override;
	void Update(float delta) override;

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
	void ComputeMousePos(const uint8_t* keyState);
	ButtonState GetKeyState(SDL_Scancode key) const;
	ButtonState GetMouseButtonState(int button) const;

	SDL_Scancode mLeft, mRight, mJump, mShoot, mCrouch;
	float mMouseX, mMouseY;
	b2Vec2 mToMouse;

	uint8_t mCurrKeyboardState[SDL_NUM_SCANCODES], mPrevKeyboardState[SDL_NUM_SCANCODES];
	Uint32 mCurrMouse, mPrevMouse;
};

