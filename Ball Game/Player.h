#pragma once

class Player : public Actor
{
public:
	Player(class Game* game);

	void UpdateActor(float delta) override;

private:

};

