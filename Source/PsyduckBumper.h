#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include "Timer.h"
class PsyduckBumper : public Bumper {
public:
	PsyduckBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip);
	~PsyduckBumper();

	update_status Update();
	bool CleanUp() override;

protected:
	void OnHit()override;
	b2Body* body = nullptr;

private:
	Texture* psyduck_texture = nullptr;
	Animator* psyduck_animator = nullptr;

	bool hidden = false;
	bool flip = false;

	Timer hidden_timer;
	float hidden_time = 2.f;
};
