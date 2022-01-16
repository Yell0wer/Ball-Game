#pragma once

class ContactListener : public b2ContactListener // todo encapsulate this?
{
public:
	ContactListener() {}

	void BeginContact(b2Contact* contact) {}

	void EndContact(b2Contact* contact) {}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		const b2Body* bodyA = contact->GetFixtureA()->GetBody();
		const b2Body* bodyB = contact->GetFixtureB()->GetBody();
		b2Vec2 velA = bodyA->GetLinearVelocity(), velB = bodyB->GetLinearVelocity();

		uintptr_t actorA = bodyA->GetUserData().pointer;
		uintptr_t actorB = bodyB->GetUserData().pointer;
		if (actorA) reinterpret_cast<class Player*>(actorA)->OnCollision(velB.LengthSquared() * bodyB->GetMass() / 2.f, actorB);
		if (actorB) reinterpret_cast<class Player*>(actorB)->OnCollision(velA.LengthSquared() * bodyA->GetMass() / 2.f, actorA);
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