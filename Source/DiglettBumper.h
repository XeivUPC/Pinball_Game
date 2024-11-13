#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include "Timer.h"
class DiglettBumper : public Bumper {
public:
	DiglettBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip);
	~DiglettBumper();

	update_status Update();
	bool CleanUp() override;

protected:
	void OnHit() override;
	b2Body* body = nullptr;

private:
	Texture* diglett_texture = nullptr;
	Animator* diglett_animator = nullptr;

	bool hidden = false;
	bool flip = false;

	Timer hidden_timer;
	float hidden_time = 1.f;
};

