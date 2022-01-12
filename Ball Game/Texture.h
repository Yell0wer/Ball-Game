#pragma once
#include "stdafx.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& file);
	void Unload();

	void SetActive();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

private:
	unsigned int mID;
	int mWidth, mHeight;
};

