#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include "Timer.h"

class TriangularBumper : public Bumper {
public:
	TriangularBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool filp, int variant);
	~TriangularBumper();

	update_status Update();
	bool CleanUp() override;

protected:
	void OnHit();
	b2Body* body = nullptr;
	b2Body* bumperBody = nullptr;

private:
	int variant = -1;
	bool flip = false;

	Texture* texture = nullptr;
	Animator* animator = nullptr;

	bool gettingHit = false;
};

