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

	void PlayAnimation(const std::string& name, bool override) { if (mCurrAnim == "" || override) mCurrAnim = name; }

private:
	std::string mCurrAnim;
	std::unordered_map<std::string, Animation*> mAnimations;
};

