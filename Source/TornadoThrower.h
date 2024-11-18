#pragma once
#include "MapObject.h"
#include "AnimationSystem.h"
#include "MapSensor.h"
#include "Box2DFactory.h"

class TornadoThrower : public MapObject {
private:
	Timer throwTimer;
	float throwSpeed = 5.f;
public:
	TornadoThrower(ModuleGame* gameAt, b2Vec2 position);
	~TornadoThrower();

	update_status Update();
	bool CleanUp() override;

protected:
	b2Body* body = nullptr;
	b2Vec2 position = { 0,0 };

	float radius = 0;

	Texture* texture = nullptr;
	Animator* animator = nullptr;

	Timer destroyTimer;
	int destroyTime = 30;

	CollisionSensor sensor;
};

