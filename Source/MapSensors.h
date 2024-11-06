#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"

class MapSensor : public MapObject {
private:
public:
	MapSensor(ModuleGame* gameAt, b2Vec2 position);
	~MapSensor() = 0;

	update_status Update();
	bool CleanUp() override;

	int GetTotalActivations();
	void ResetTotalActivations();

protected:
	virtual void OnActivation() = 0;
	int timesActivated = 0;
	b2Vec2 position = { 0,0 };
	CollisionSensor sensor;
};

