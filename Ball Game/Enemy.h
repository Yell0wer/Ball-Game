#pragma once

class Enemy : public Character
{
public:
	Enemy(class Game* game);

	void UpdateActor(float delta) override;

private:

};

