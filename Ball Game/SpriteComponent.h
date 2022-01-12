#pragma once
#include "stdafx.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int order = 100);
	~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	std::pair<int, int> GetTexDim() const { return mTexDim; }

private:
	class Texture* mTexture;
	int mDrawOrder;
	std::pair<int, int> mTexDim;
};

