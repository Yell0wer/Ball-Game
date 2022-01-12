#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int order) : 
	Component(owner),
	mTexture(nullptr),
	mDrawOrder(order),
	mTexDim({0, 0})
{}

SpriteComponent::~SpriteComponent() {}

void SpriteComponent::Draw(Shader* shader)
{
	if (!mTexture) return;
	Matrix4 s = Matrix4::CreateScale(static_cast<float>(mTexDim.first), static_cast<float>(mTexDim.second), 1.f);
	Matrix4 w = s * mOwner->GetWorldTransform();

	shader->SetMatrixUniform("uWorldTransform", w);
	mTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexDim = texture->GetDim();
}