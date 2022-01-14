#pragma once

class Player : public DynamicActor
{
public:
	Player(class Game* game);

	void UpdateActor(float delta) override;

private:

};

