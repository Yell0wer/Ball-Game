#pragma once

class Character : public DynamicActor
{
public:
	Character(class Game* game);

	void UpdateActor(float delta) override;
	void Draw() override;

	void OnCollision(float impact, uintptr_t obj) override;

	AnimatedSpriteComponent* GetAnim() const { return mAnim; }

	std::string GetFacing() const { return (mFacing ? "-l" : "-r"); }
	void SetFacing(bool l) { mFacing = l; }

protected:
	void LoadAnim(const std::string& name, int fps, int frames);

	float mHealth;
	AnimatedSpriteComponent* mAnim;
	bool mFacing;
};

