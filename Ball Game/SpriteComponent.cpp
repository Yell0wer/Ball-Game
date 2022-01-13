#include "stdafx.h"

SpriteComponent::SpriteComponent(Actor* owner, int order) : 
	Component(owner),
	mTexture(nullptr),
	mDrawOrder(order),
	mTexWidth(0),
	mTexHeight(0)
{
}

SpriteComponent::~SpriteComponent() {}

void SpriteComponent::Draw(Shader* shader)
{
	if (!mTexture) return;
	Matrix4 w = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.f) * mOwner->GetWorldTransform();

	shader->SetMatrixUniform("uWorldTransform", w);
	mTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = mTexture->GetWidth();
	mTexHeight = mTexture->GetHeight();
}