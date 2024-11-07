#pragma once
#include "MapSensor.h"
#include "CollisionSensor.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"

class PokeballChangerSensor : public MapSensor {
public:
	PokeballChangerSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int variant);
	~PokeballChangerSensor();

	update_status Update();
	bool CleanUp() override;

protected:
	void OnActivation();

	b2Body* body = nullptr;

private:
	int variant = -1;

	Texture* texture = nullptr;
	Animator* animator = nullptr;
};

