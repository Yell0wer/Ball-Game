#pragma once

class ContactListener : public b2ContactListener
{
public:
	ContactListener() {}

	void BeginContact(b2Contact* contact) {}

	void EndContact(b2Contact* contact) {}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);
		b2PointState state1[2], state2[2];
		b2GetPointStates(state1, state2, oldManifold, contact->GetManifold());

		if (state2[0] == b2_addState)
		{
			const b2Body* bodyA = contact->GetFixtureA()->GetBody();
			const b2Body* bodyB = contact->GetFixtureB()->GetBody();
			b2Vec2 point = worldManifold.points[0];
			b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point);
			b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);

			float approachVelocity = std::abs(b2Dot(vB - vA, worldManifold.normal)); // todo figure out and fix this thing

			uintptr_t userDataA = bodyA->GetUserData().pointer;
			uintptr_t userDataB = bodyB->GetUserData().pointer;
			if (userDataA) reinterpret_cast<class Player*>(userDataA)->OnCollision(approachVelocity * bodyB->GetMass(), userDataB);
			if (userDataB) reinterpret_cast<class Player*>(userDataB)->OnCollision(approachVelocity * bodyA->GetMass(), userDataA);
		}
	}

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}
};

class Game
{
public:
	Game();
	// game loop
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* a);
	void RemoveActor(class Actor* a);

	class Shader* GetShader() const { return mShader; }
	b2World* GetWorld() const { return mWorld; }
	class Player* GetPlayer() const { return mPlayer; }
	class Camera* GetCamera() const { return mCamera; }
	int GetWindowWidth() const { return mWindowWidth; }
	int GetWindowHeight() const { return mWindowHeight; }
	int GetLevelWidth() const { return mWindowWidth; }
	int GetLevelHeight() const { return mWindowHeight; }

	std::string mLevel[500]; // todo make level private

private:
	// helper functions
	bool LoadLevel(const std::string& file);
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	// game objects
	class Camera* mCamera;
	class Player* mPlayer;
	SDL_Window* mWindow;
	int mWindowWidth, mWindowHeight;
	int mLevelWidth, mLevelHeight;
	SDL_GLContext mContext;
	const Uint8* mKeyboardState;
	Uint32 mTickCount;
	class Shader* mShader;
	class VertexArray* mSquare;
	bool mIsRunning;
	std::vector<class Actor*> mActors;
	bool mActorsUpdating;
	std::vector<class Actor*> mPending;

	ContactListener* mContact; // temp

	// physics
	b2World* mWorld;
	int32 mVelIter = 8;
	int32 mPosIter = 3;
};