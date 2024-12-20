#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"

class BlackHoleEffector;

class MapCave : public MapObject {
private:
	b2Vec2 entryPosition = {0,0};
	float entryRadius = 0;

	Animator* animator =nullptr; 
	Texture* texture = nullptr;

	bool isOpen = false;
	bool isBallIn = false;

	b2Body* body;


	Timer freeBallTimer;
	float freeBallTime = 1.f;
	
	int audioVoidAbsorbId = -1;
	int audioVoidEnterId = -1;
public:
	MapCave(ModuleGame* gameAt, b2Vec2 position, b2Vec2 entryPosition, float entryRadius);
	~MapCave();

	update_status Update();
	bool CleanUp() override;

	void OpenCave();
	void CloseCave();

	void FreeBall();

	bool IsCaveOpen();

protected:
	void OnHit();

	CollisionSensor sensor;

	BlackHoleEffector* blackHoleEffector;
};

