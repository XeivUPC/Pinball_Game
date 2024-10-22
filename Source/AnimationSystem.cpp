#include "AnimationSystem.h"
#include "Application.h"
#include "ModuleRender.h"



Rectangle AnimationData::GetSpriteRect(int spriteIndex)
{
	Rectangle spriteRect = Rectangle();
	
	spriteRect.width = sprites[spriteIndex].size.x;
	spriteRect.height = sprites[spriteIndex].size.y;

	spriteRect.x = sprites[spriteIndex].index.x * spriteRect.width;
	spriteRect.y = sprites[spriteIndex].index.y * spriteRect.height;
	return spriteRect;
}

Texture2D* AnimationData::GetTexture(int spriteIndex)
{
	return sprites[spriteIndex].texture;
}

int AnimationData::GetCount(int spriteIndex)
{
	return sprites.size();
}

void AnimationData::AddSprite(Sprite sprite)
{
	sprite.extraData = -1;
	sprites.push_back(sprite);
}

void AnimationData::AddSprite(Sprite sprite, int extraData)
{
	sprite.extraData = extraData;
	sprites.push_back(sprite);
}

AnimationData::AnimationData(const char* n, std::vector<Sprite> s)
{
	name = n;
	sprites = s;
}

AnimationData::AnimationData(const char* n)
{
	name = n;
}
AnimationData::AnimationData()
{
}

AnimationData::~AnimationData()
{
	sprites.clear();
}


void Animator::Next()
{
	if (currentSprite < animations[currentAnimation].sprites.size() - 1)
		currentSprite++;
	else
	{
		if (loop)
		{
			currentSprite = 0;
		}
		else
		{
			currentSprite = animations[currentAnimation].sprites.size() - 1;
		}
	}
}

Animator::Animator(Application* App)
{
	this->App = App;
}

Animator::~Animator()
{
	animations.clear();
}

void Animator::AddAnimation(AnimationData anim)
{
	animations[anim.name] = anim;
}

void Animator::SelectAnimation(const char* animName, bool l)
{
	if (currentAnimation == animName)
		return;

	currentAnimation = animName;
	loop = l;
	currentSprite = 0;
}


void Animator::SetSpeed(float s)
{
	speed = s;
}

void Animator::Update()
{
	if (!isPlaying)
		return;

	if (timer.ReadSec() >= speed)
	{
		timer.Start();
		Next();
	}
}

void Animator::Animate(int x, int y, bool flip)
{	
	if (!canDraw)
		return;
	Rectangle rect = animations[currentAnimation].GetSpriteRect(currentSprite);

	App->renderer->Draw(*animations[currentAnimation].sprites[currentSprite].texture,x,y, &rect);
	
}

void Animator::SetIfPlaying(bool isPlaying)
{
	this->isPlaying = isPlaying;
}

bool Animator::IsPlaying()
{
	return isPlaying;
}

void Animator::SetIfCanDraw(bool canDraw)
{
	this->canDraw = canDraw;
}

bool Animator::CanDraw()
{
	return canDraw;
}

const char* Animator::GetCurrentAnimationName()
{
	return currentAnimation;
}

AnimationData Animator::GetCurrentAnimation()
{
	return animations[GetCurrentAnimationName()];
}

Sprite Animator::GetCurrentAnimationSprite()
{
	return GetCurrentAnimation().sprites[currentSprite];
}
