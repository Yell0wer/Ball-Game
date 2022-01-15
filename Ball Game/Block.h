#pragma once

class Block : public StaticActor
{
public:
	Block(class Game* game, float w, float h, const std::string& tex);

	void UpdateActor(float delta) override;

private:
	float mWidth, mHeight;
};

