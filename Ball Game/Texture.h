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

	std::pair<int, int> GetDim() const { return mDim; }

private:
	unsigned int mID;
	std::pair<int, int> mDim;
};

