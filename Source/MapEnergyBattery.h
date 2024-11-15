#pragma once

#include "Timer.h"
#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"

class MapEnergyBattery : public MapObject
{
public:
	MapEnergyBattery(ModuleGame* gameAt, b2Vec2 position, int variant);
	~MapEnergyBattery();

	update_status Update();
	bool CleanUp() override;

	void AddEnergy(float amount);
	void SetEnergy(float amount);
	void Reset();

private:
	
	Texture* texture = nullptr;
	Animator* animator = nullptr;

	float totalCapacity = 16.f;
	float currentEnergy = 0.f;
protected:
};
