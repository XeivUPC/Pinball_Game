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

AnimationData::AnimationData(std::string n, std::vector<Sprite> s)
{
	name = n;
	sprites = s;
}

AnimationData::AnimationData(std::string n)
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
	if (currentSprite < (int)animations[currentAnimation].sprites.size() - 1)
		currentSprite++;
	else
	{
		if (loop)
		{
			currentSprite = 0;
		}
		else
		{
			animationFinished = true;
			currentSprite = animations[currentAnimation].sprites.size() - 1;
		}
	}
}

void Animator::Previous()
{
	if (currentSprite > 0)
		currentSprite--;
	else
	{
		if (loop)
		{
			currentSprite = animations[currentAnimation].sprites.size() - 1;
		}
		else
		{
			animationFinished = true;
			currentSprite = 0;
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

void Animator::SelectAnimation(std::string animName, bool l)
{
	if (currentAnimation == animName)
		return;
	animationFinished = false;
	currentAnimation = animName;
	loop = l;
	currentSprite = 0;
	timer.Start();
}

bool Animator::HasAnimationFinished()
{
	if (loop)
		return false;
	else {
		return animationFinished;
	}
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
		if (animationDirection==1) {
			Next();	
		}
		else {
			Previous();
		}
	}

}

void Animator::LerpUpdate(float factor)
{
	if (!isPlaying)
		return;

	factor *= animationDirection;


	int spriteCount = animations[currentAnimation].sprites.size();


	int	frame = (int)round(factor * (spriteCount-1));

	if (loop) {
		if(spriteCount!=0)
			frame %= spriteCount;
		else {
			frame = 0;
		}
	}
	else {
		if (animationDirection == 1) {
			if (frame >= spriteCount)
				frame = spriteCount-1;
		}
		else {
			if (frame < 0)
				frame = 0;
		}
	}

	currentSprite = frame;

}

void Animator::SetDirection(int direction)
{
	this->animationDirection = direction;
}

void Animator::Animate(int x, int y, bool flip)
{	
	if (!canDraw)
		return;
	Rectangle rect = animations[currentAnimation].GetSpriteRect(currentSprite);

	if(flip)
		rect.width *= -1;

	App->renderer->Draw(*animations[currentAnimation].sprites[currentSprite].texture,x,y, &rect, WHITE, flip);
	
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

std::string Animator::GetCurrentAnimationName()
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
