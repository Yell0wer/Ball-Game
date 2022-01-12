#include "Texture.h"
#define w first
#define h second

Texture::Texture() :
	mID(0),
	mDim({ 0, 0 })
{}

Texture::~Texture() {}

bool Texture::Load(const std::string& file)
{
	int channels = 0;
	unsigned char* img = SOIL_load_image(file.c_str(), &mDim.w, &mDim.h, &channels, SOIL_LOAD_AUTO);
	
	if (!img)
	{
		SDL_Log("SOIL failed to load image %s: %s", file.c_str(), SOIL_last_result());
		return 0;
	}

	int format = GL_RGB;
	if (channels == 4) format = GL_RGBA;

	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mDim.w, mDim.h, 0, format, GL_UNSIGNED_BYTE, img);

	SOIL_free_image_data(img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return 1;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mID);
}