#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include "Timer.h"

class CircularBumper : public Bumper {
public:
	CircularBumper(ModuleGame* gameAt, b2Vec2 position, float radius, float restitution, int variant);
	~CircularBumper();

	update_status Update();
	bool CleanUp() override;

protected:
	void OnHit();
	b2Body* body = nullptr;

private:
	int variant = -1;

	Texture* texture = nullptr;
	Animator* animator = nullptr;

	Timer shake_timer;
	float shake_time = 1.5f;
	float shake_time_min = 1.f;
	float shake_time_max = 1.5f;

	void SetShakeTime();

	bool gettingHit = false;

	int bumperAudioId = -1;
};

