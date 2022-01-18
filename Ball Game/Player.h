#pragma once

class Player : public Character
{
public:
	Player(class Game* game);

	void UpdateActor(float delta) override;

private:

};