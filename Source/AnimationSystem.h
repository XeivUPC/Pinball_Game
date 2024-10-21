#pragma once

#include <vector>
#include <unordered_map>

#include "raylib.h"
#include "Timer.h"

class Application;

struct Sprite
{
	Texture2D* texture;
	Vector2 index;
	Vector2 size;

	int extraData;
};

class AnimationData
{
	friend class Animator;
private:
	const char* name = "";
	std::vector <Sprite> sprites;
protected:
	Rectangle GetSpriteRect(int spriteIndex);
	Texture2D* GetTexture(int spriteIndex);
	int GetCount(int spriteIndex);
public:
	void AddSprite(Sprite sprite);
	void AddSprite(Sprite sprite, int extraData);
	AnimationData(const char* n, std::vector<Sprite> s);
	AnimationData();
	~AnimationData();

};

class Animator
{
private:
	void Next();

	std::unordered_map<const char*, AnimationData> animations;

	const char* currentAnimation = "";
	int currentSprite = 0;

	bool loop = false;
	float speed = 1;

	bool isPlaying=true;
	bool canDraw=true;

	Timer timer;

	Application* App;

public:
	Animator(Application* App);
	~Animator();
	Animator(std::vector<AnimationData> anims, float s);
	void AddAnimation(AnimationData anim);
	void SelectAnimation(const char* animName, bool l);
	void SetSpeed(float s);
	void Update();
	void Animate(int x, int y, bool flip);

	void SetIfPlaying(bool isPlaying);
	bool IsPlaying();

	void SetIfCanDraw(bool canDraw);
	bool CanDraw();

	const char* GetCurrentAnimationName();
	AnimationData GetCurrentAnimation();
	Sprite GetCurrentAnimationSprite();
};