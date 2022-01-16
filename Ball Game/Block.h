#pragma once

class Block : public StaticActor
{
public:
	Block(class Game* game, float w, float h, b2Vec2 end, const std::string& model, const std::string& texType);

	void UpdateActor(float delta) override;

	void Draw() override;

private:
	bool IsBlock(char c) { return c == '^' || c == 'v' || c == '>' || c == '<' || c == '*' || c == '#'; }
	float mWidth, mHeight;
	std::vector<class SpriteComponent*> mSprites;
};

