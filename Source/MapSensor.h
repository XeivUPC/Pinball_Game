#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"

class MapSensor : public MapObject {
private:
public:
	MapSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle);
	~MapSensor() = 0;

	update_status Update();
	bool CleanUp() override;

	int GetTotalActivations();
	void ResetTotalActivations();


	virtual void Activate() = 0;
	virtual void Desactivate() = 0;
	void SwitchActiveStatus();
	bool IsActive();

	void Twinkle();
	bool IsTwinkling() const;
	bool HasFinishedTwinkling() const;
	void FinishTwinkle();

protected:
	virtual void OnTrigger() = 0;
	int timesActivated = 0;
	bool active = false;

	bool twinkling = false;
	bool finishedTwinkling = false;

	Timer twinklingTimer;
	float twinklingTime = 0.15f;
	Timer twinkleTimer;
	int twinkleTime = 2;

	b2Vec2 position = { 0,0 };
	float angle;

	CollisionSensor sensor;
};

//// OnTrigger

//// Activate virtual

//// Desctivate virtual

//// SwitchActiveStatus

//// IsActive

//// GetTotalActivations
//// ResetTotalActivations
