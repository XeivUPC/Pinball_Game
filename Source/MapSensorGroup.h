#pragma once
#include "MapObject.h"
#include "MapSensor.h"
#include <vector>

class MapSensorGroup : public MapObject {
private:
public:
	MapSensorGroup(ModuleGame* gameAt);
	~MapSensorGroup()=0;

	update_status Update();
	bool CleanUp() override;

	void AddSensor(MapSensor* sensor);
	void RemoveSensor(MapSensor* sensor);

	void ActivateAll();
	void DesactivateAll();
	void SwitchAllActiveStatus();

	bool AllActive();
	int GetActiveAmount();

	void SetIfEnable(bool status);

protected:
	virtual void OnAllActive() = 0;
	std::vector<MapSensor*> mapSensors;
};


//// vector<MapSensor>

//// AddSensor
//// RemoveSensor

//// ActivateAll
//// DesactivateAll

//// SwitchAllActiveStatus


//// AllActive

//// GetActiveAmount

//// OnAllActive virtual
