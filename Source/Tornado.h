#pragma once
#include "MapObject.h"
#include "AnimationSystem.h"
#include "MapSensor.h"
#include "Box2DFactory.h"


class BlackHoleEffector;

class Tornado : public MapObject {
private:

	Texture* texture = nullptr;
	Animator* animator = nullptr;


	float speed;
	b2Vec2 direction;
	float radius = 3;

	Timer lifeTimer;
	float lifeTime=5.f;


	b2Body* body = nullptr;
	BlackHoleEffector* blackHoleEffector = nullptr;
	CollisionSensor sensor;

public:
	Tornado(ModuleGame* gameAt, b2Vec2 position, b2Vec2 direction, float speed);
	~Tornado();

	update_status Update();
	bool CleanUp() override;


};

