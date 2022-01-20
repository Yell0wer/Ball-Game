#include "stdafx.h"

Game::Game() {}

bool Game::Initialize()
{
	// initialize sdl
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log("Failed initializing SDL: %s\n", SDL_GetError());
		return 0;
	}
	// use core opengl profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// color buffer with 8 bits per channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	// create sdl window
	mWindowWidth = 1920;
	mWindowHeight = 1080;
	mWindow = SDL_CreateWindow("Carl's Fantastic Ball Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	if (!mWindow)
	{
		SDL_Log("Failed creating window: %s\n", SDL_GetError());
		return 0;
	}
	// opengl context
	mContext = SDL_GL_CreateContext(mWindow);
	// initialize glew
	glewExperimental = GL_TRUE; // prevents unnecessary errors on some platforms
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed initializing GLEW");
		return 0;
	}
	glGetError(); // clear insignificant error codes

	// load shaders
	if (!LoadShaders()) return 0;
	// allow program to run
	mIsRunning = 1;
	
	float v[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};
	unsigned int i[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSquare = new VertexArray(v, 4, i, 6);

	b2Vec2 gravity(0.f, -30.f);
	mWorld = new b2World(gravity);

	mContact = new ContactListener();
	mWorld->SetContactListener(mContact); // temp

	Actor* bg = new Actor(this);
	bg->LoadTex("Assets/bg/redline.png");
	bg->SetPos(b2Vec2(12.f, -4.5f));
	Actor* bg1 = new Actor(this);
	bg1->LoadTex("Assets/bg/redline.png");
	bg1->SetPos(b2Vec2(37.f, -4.5f));

	mPlayer = new Player(this);
	LoadLevel("Levels/demo.txt");

	mCamera = new Camera(this);

	return 1;
}

void Game::RunLoop()
{
	// game loop
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	while (!mActors.empty()) delete mActors.back();
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	// poll for events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	// update keyboard state
	mKeyboardState = SDL_GetKeyboardState(NULL);

	mActorsUpdating = 0;
	for (auto a : mActors) a->ProcessInput(mKeyboardState);
	mActorsUpdating = false;
}

void Game::UpdateGame()
{
	// limit framerate (15 fps)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
	// get delta 
	float delta = (SDL_GetTicks() - mTickCount) / 1000.f;
	// clamp delta  value
	delta = std::min(delta, 0.05f);
	// update tick count
	mTickCount = SDL_GetTicks();
	// update actors
	mActorsUpdating = 1;
	for (auto a : mActors)
	{
		a->Update(delta);
		if (a->GetState() == EDead) mDead.push_back(a);
	}
	if (mPlayer->GetState() == EDead) mIsRunning = 0;
	mActorsUpdating = 0;
	for (auto a : mPending) AddActor(a);
	mPending.clear();
	for (auto a : mDead) delete a;
	mDead.clear();
	mWorld->Step(delta, mVelIter, mPosIter);
	mCamera->Update(delta);
}

void Game::GenerateOutput()
{
	// set clear color to black
	glClearColor(0.f, 0.f, 0.f, 1.f);
	// clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// activate vertex array
	mShader->SetActive();
	mSquare->SetActive();
	// alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// draw
	for (auto a : mActors) a->Draw();
	// swap buffers
	SDL_GL_SwapWindow(mWindow);
}

void Game::AddActor(class Actor* a)
{
	if (mActorsUpdating) mPending.push_back(a);
	else
	{
		auto i = mActors.begin();
		for (; i != mActors.end(); i++)
			if (a->GetOrder() > (*i)->GetOrder()) break;
		mActors.insert(i, a);
	}
}

void Game::RemoveActor(class Actor* a)
{ // binary search?
	auto i = std::find(mPending.begin(), mPending.end(), a);
	if (i != mPending.end())
	{
		std::iter_swap(i, mPending.end() - 1);
		mPending.pop_back();
	}

	i = std::find(mActors.begin(), mActors.end(), a);
	if (i != mActors.end())
	{
		std::iter_swap(i, mActors.end() - 1);
		mActors.pop_back();
	}
}

bool Game::LoadShaders()
{
	mShader = new Shader();
	if (!mShader->Load("Basic.vert", "Basic.frag")) return 0;
	mShader->SetActive();
	mShader->SetMatrixUniform("uViewTransform", Matrix4::CreateScale(64.f) * Matrix4::CreateSimpleViewProj(static_cast<float>(mWindowWidth), static_cast<float>(mWindowHeight)));
	return 1;
}

bool Game::LoadLevel(const std::string& file)
{
	std::ifstream str(file);
	str >> mLevelWidth >> mLevelHeight;
	str.ignore();
	for (int i = 0; i < mLevelHeight; i++)
	{
		std::getline(str, mLevel[i]);
	}
	std::string block = "";
	for (int i = 0; i < mLevelHeight; i++)
		for (int j = 0; j <= mLevelWidth; j++)
		{
			b2Vec2 pos = b2Vec2(static_cast<float>(j), static_cast<float>(-i));
			if (mLevel[i][j] == 'v' ||
				mLevel[i][j] == '>' ||
				mLevel[i][j] == '^' ||
				mLevel[i][j] == '<' ||
				mLevel[i][j] == '*' ||
				mLevel[i][j] == '#'
				) block += mLevel[i][j];
			else if (block != "")
			{
				Block* b = new Block(this, static_cast<float>(block.size()), 1.f, pos, block + '\n', "demo-walls"); // todo change to border
				b->SetPos(b2Vec2(static_cast<float>((j + j - block.size()) / 2.f) - 0.5f, static_cast<float>(-i)));
				block = "";
			}
			switch (mLevel[i][j])
			{
			case '@':
			{
				Block* b = new Block(this, 1.f, 1.f, pos, "", "blank");
				b->SetPos(pos);
				break;
			}
			case 'P':
			{
				mPlayer->SetPos(pos);
				break;
			}
			case 'C':
			{
				Crate* c = new Crate(this);
				c->SetPos(pos);
				break;
			}
			case 'E':
			{
				Enemy* e = new Enemy(this);
				e->SetPos(pos);
				break;
			}
			}
		}
	return 1;
}