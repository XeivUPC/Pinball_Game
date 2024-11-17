#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include "Timer.h"
class StaryuBumper : public Bumper {
public:
	StaryuBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip);
	~StaryuBumper();

	update_status Update();
	bool CleanUp() override;

	bool IsActive();

protected:
	void OnHit()override;
	b2Body* body = nullptr;

private:
	Texture* staryu_texture = nullptr;
	Animator* staryu_animator = nullptr;

	bool recovering = false;
	bool flip = false;

	Timer recover_timer;
	float recover_time = 0.25f;


	bool isActive = true;
};
