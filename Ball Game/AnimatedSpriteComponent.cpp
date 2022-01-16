#include "stdafx.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(class Actor* owner) :
	SpriteComponent(owner),
	mCurrAnim("")
{}

AnimatedSpriteComponent::~AnimatedSpriteComponent() {}

void AnimatedSpriteComponent::Update(float delta)
{
	Animation* curr = mAnimations[mCurrAnim];
	if (!curr) return;
	curr->CurrFrame += delta * curr->FPS;
	if (curr->CurrFrame >= curr->Frames.size())
	{
		curr->CurrFrame = 0.f;
		mCurrAnim = "";
	}
}

void AnimatedSpriteComponent::Draw(class Shader* shader)
{
	Texture* currFrame = mAnimations[mCurrAnim]->Frames[static_cast<int>(mAnimations[mCurrAnim]->CurrFrame)];
	mTexWidth = currFrame->GetWidth();
	mTexHeight = currFrame->GetHeight();
	Matrix4 w = Matrix4::CreateTranslation(Vector3(mOffset, 0.f, 0.f)) * Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.f) * mOwner->GetWorldTransform();

	shader->SetMatrixUniform("uWorldTransform", w);
	currFrame->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}