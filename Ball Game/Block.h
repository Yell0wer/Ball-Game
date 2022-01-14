#pragma once

class Block : public Actor
{
public:
	Block(class Game* game, float w, float h);

	void UpdateActor(float delta) override;

private:
	float mWidth, mHeight;
};

