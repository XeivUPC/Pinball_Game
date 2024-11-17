#pragma once

#include <vector>
#include <unordered_map>
#include <string>

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
	std::string name = "";
	std::vector <Sprite> sprites;
protected:
	Texture2D* GetTexture(int spriteIndex);
public:
	Rectangle GetSpriteRect(int spriteIndex);
	int GetCount();
	void AddSprite(Sprite sprite);
	void AddSprite(Sprite sprite, int extraData);
	AnimationData(std::string n, std::vector<Sprite> s);
	AnimationData(std::string n);
	AnimationData();
	~AnimationData();

};

class Animator
{
private:
	void Next();
	void Previous();

	std::unordered_map<std::string, AnimationData> animations;

	std::string currentAnimation = "";
	int currentSprite = 0;

	bool loop = false;
	float speed = 1;
	int animationDirection = 1;

	bool isPlaying=true;
	bool canDraw=true;

	bool animationFinished = false;

	Timer timer;

	Application* App;

public:
	Animator(Application* App);
	~Animator();
	void AddAnimation(AnimationData anim);
	void SelectAnimation(std::string animName, bool l);
	bool HasAnimationFinished();
	void SetSpeed(float s);
	float GetSpeed();
	void Update();
	void LerpUpdate(float factor);
	void SetDirection(int direction);
	void Animate(int x, int y, bool flip);
	void Animate(int x, int y, Rectangle rect, bool flip);

	void SetIfPlaying(bool isPlaying);
	bool IsPlaying();

	void SetIfCanDraw(bool canDraw);
	bool CanDraw();

	std::string GetCurrentAnimationName();
	AnimationData GetCurrentAnimation();
	Sprite GetCurrentAnimationSprite();
	int GetCurrentAnimationSpriteIndex();
};