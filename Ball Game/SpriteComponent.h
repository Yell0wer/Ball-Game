#pragma once

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, float offset = 0);
	~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);

	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

protected:
	class Texture* mTexture;
	float mOffset;
	int mTexWidth, mTexHeight;
};

