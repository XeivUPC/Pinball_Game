#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"

class Effector : public MapObject {
private:
public:
	Effector(ModuleGame* gameAt, b2Vec2 position);
	Effector(ModuleGame* gameAt, b2Vec2 position, float width, float height);
	Effector(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices);
	~Effector();

	update_status Update();
	bool CleanUp() override;

	void SetIfEnable(bool status);

protected:
	void OnEnter(b2Body* enterBody);
	void OnExit(b2Body* exitBody);

	std::vector<b2Body*> bodiesInside;

	b2Body* body = nullptr;
	b2Vec2 position = { 0,0 };

	bool enabled = false;

	CollisionSensor sensor;
};

