#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"

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

	Texture* texture;
	Animator* animator;
	
};

