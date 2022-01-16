#pragma once

struct Animation
{
	int FPS;
	float CurrFrame;
	std::vector<class Texture*> Frames;
};

class AnimatedSpriteComponent : public SpriteComponent
{
public:
	AnimatedSpriteComponent(class Actor* owner);
	~AnimatedSpriteComponent();

	void Update(float delta) override;
	void Draw(Shader* shader) override;

	void AddAnimation(const std::string& name, Animation* anim) { mAnimations[name] = anim; }

	void PlayAnimation(const std::string& name, bool override, int order) { if (mCurrAnim == "" || (override && order > mOverrideOrder)) { mCurrAnim = name; mOverrideOrder = order; } }

private:
	std::string mCurrAnim;
	int mOverrideOrder;
	std::unordered_map<std::string, Animation*> mAnimations;
};

