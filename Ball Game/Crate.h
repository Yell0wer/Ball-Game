#pragma once

class Crate : public DynamicActor
{
public:
	Crate(class Game* game);

	void UpdateActor(float delta) override;
};

