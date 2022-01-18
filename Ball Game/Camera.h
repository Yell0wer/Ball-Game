#pragma once

class Camera
{
public:
	Camera(class Game* mGame);

	void Update(float delta);

	b2Vec2 GetPos() const { return mPos; }
	void SetPos(b2Vec2 pos) { mPos = pos; }

private:
	class Game* mGame;
	b2Vec2 mPos, mVel, mVelLim;
};

