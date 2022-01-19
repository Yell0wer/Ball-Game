#include "stdafx.h"

Block::Block(class Game* game, float w, float h, b2Vec2 end, const std::string& model, const std::string& texType) :
	StaticActor(game),
	mWidth(w), // todo change to border
	mHeight(h)
{
	// TODO FIX THIS MESS
	SetBox(w, h, 1.f); // this shit really stinks don't touch

	if (!model.size())
	{
		class Texture* t = new Texture();
		t->Load("Assets/" + texType + ".png");
		class SpriteComponent* s = new SpriteComponent(this);
		s->SetTexture(t);
		mSprites.push_back(s);
	}
	else 
		for (uint i = 0; i < model.size(); i++)
		{
			class Texture* t = new Texture();
			int r = static_cast<int>(-end.y);
			int c = static_cast<int>(end.x - model.size() + 1 + i);
			if (model[i] == '^') t->Load("Assets/" + texType + "/2.png");
			else if(model[i] == 'v') t->Load("Assets/" + texType + "/8.png");
			else if (model[i] == '>') t->Load("Assets/" + texType + "/4.png");
			else if (model[i] == '<') t->Load("Assets/" + texType + "/6.png");
			else if (model[i] == '*')
			{
				if (r > 0)
				{
					if (IsBlock(mGame->mLevel[r][c + 1]) && IsBlock(mGame->mLevel[r - 1][c])) t->Load("Assets/" + texType + "/1.png");
					if (c > 0)
						if (IsBlock(mGame->mLevel[r][c - 1]) && IsBlock(mGame->mLevel[r - 1][c])) t->Load("Assets/" + texType + "/3.png");
				}
				if(c > 0)
					if (IsBlock(mGame->mLevel[r][c - 1]) && IsBlock(mGame->mLevel[r + 1][c])) t->Load("Assets/" + texType + "/9.png");
				if (IsBlock(mGame->mLevel[r][c + 1]) && IsBlock(mGame->mLevel[r + 1][c])) t->Load("Assets/" + texType + "/7.png");
			}
			else if (model[i] == '#')
			{
				if (r > 0)
				{
					if (IsBlock(mGame->mLevel[r][c + 1]) && IsBlock(mGame->mLevel[r - 1][c])) t->Load("Assets/" + texType + "/1e.png");
					if (c > 0)
						if (IsBlock(mGame->mLevel[r][c - 1]) && IsBlock(mGame->mLevel[r - 1][c])) t->Load("Assets/" + texType + "/3e.png");
				}
				if (c > 0)
					if (IsBlock(mGame->mLevel[r][c - 1]) && IsBlock(mGame->mLevel[r + 1][c])) t->Load("Assets/" + texType + "/9e.png");
				if (IsBlock(mGame->mLevel[r][c + 1]) && IsBlock(mGame->mLevel[r + 1][c])) t->Load("Assets/" + texType + "/7e.png");
			}
			class SpriteComponent* s = new SpriteComponent(this, static_cast<float>(i) - (w - 1) / 2.f);
			s->SetTexture(t);
			mSprites.push_back(s);
		}

}

void Block::UpdateActor(float delta)
{
	UpdateTrans();
}

void Block::Draw()
{
	for (auto s : mSprites) s->Draw(mGame->GetShader());
}