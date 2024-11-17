#pragma once

#include "Timer.h"
#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"
#include "MapEnergyBattery.h"

class MapEnergyRotator : public MapObject
{
public:
	MapEnergyRotator(ModuleGame* gameAt, b2Vec2 position, MapEnergyBattery* battery, float width, float height, int variant);
	~MapEnergyRotator();

	update_status Update(); 
	bool CleanUp() override;
private:
	b2Body* body = nullptr;
	CollisionSensor sensor;

	Texture* texture = nullptr;
	Animator* animator = nullptr;

	MapEnergyBattery* battery;

	bool rotating=false;

	float velocity=0;
	float maxRotationSpeed=60;

	float speedReduction = 10;

	float pointsTime = 0.5f;
	Timer pointsTimer;

protected:
};

