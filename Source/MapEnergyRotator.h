#pragma once

#include "Timer.h"
#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"

class MapEnergyRotator : public MapObject
{
public:
	MapEnergyRotator(ModuleGame* gameAt, b2Vec2 position, float width, float height, int variant);
	~MapEnergyRotator();

	update_status Update();
	bool CleanUp() override;
private:
	b2Body* body;
	CollisionSensor sensor;

	Texture* texture = nullptr;
	Animator* animator = nullptr;

	bool rotating=false;

	float velocity=0;
	float maxRotationSpeed=60;

	float speedReduction = 10;
protected:
};

