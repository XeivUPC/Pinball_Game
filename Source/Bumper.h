#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"

class Bumper : public MapObject {
private:
public:
	Bumper(ModuleGame* gameAt, b2Vec2 position, float restitution);
	~Bumper() = 0;

	update_status Update();
	bool CleanUp() override;
	
	int GetTotalHits();
	void ResetTotalHits();

protected:
	virtual void OnHit() = 0;
	int hitsRecieved=0;
	float restitution = 0;
	b2Vec2 position = {0,0};
	CollisionSensor sensor;
};

