#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include "Timer.h"
class OverworldPokemonBumper : public Bumper
{
public:
	OverworldPokemonBumper(ModuleGame* gameAt, b2Vec2 position, float radius, float restitution);
	~OverworldPokemonBumper();

	update_status Update();
	bool CleanUp() override;

protected:
	void OnHit()override;
	b2Body* body = nullptr;

private:
	Texture* texture;
	Animator* animator;
	Timer cooldown;
	float cooldownTime;
	int bumperAudioId;
};