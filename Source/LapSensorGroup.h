#pragma once
#include "MapSensorGroup.h"
#include "LapSensor.h"

class LapSensorGroup : public MapSensorGroup {
public:
	LapSensorGroup(ModuleGame* gameAt);
	~LapSensorGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();

protected:
	void OnAllActive() override;

	int direction = 0;
};

