#pragma once

class Enemy : public Character
{
public:
	Enemy(class Game* game);

	void UpdateActor(float delta) override;

	void SetPost(const b2Vec2& post) { mPost = post; }

private:
	b2Vec2 mPost;
};

