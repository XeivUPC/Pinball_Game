#pragma once
#include "MapSensor.h"
#include "CollisionSensor.h"

class LapSensor : public MapSensor {
public:
	LapSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int order, int variant);
	~LapSensor();

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
	int order = -1;

	Timer cooldownTimer;
	float cooldownTime = 5;
};

