#pragma once
#include "MapSensor.h"
#include "CollisionSensor.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"

class PokeballChangerSensor : public MapSensor {
public:
	PokeballChangerSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int order, int variant);
	~PokeballChangerSensor();

	update_status Update();
	bool CleanUp() override;
	void Activate() override;
	void Desactivate() override;

	int GetOrder() const;

protected:
	void OnTrigger() override;

	b2Body* body = nullptr;

private:
	int variant = -1;
	int order = 1;

	Texture* texture = nullptr;
	Animator* animator = nullptr;

};

