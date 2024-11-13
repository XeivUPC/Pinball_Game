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
	bool HaveToActivateArrowGet();
	bool HaveToActivateArrowEvo();

protected:
	void OnAllActive() override;

	int direction = 0;

	bool activateNextGetArrow = false;
	bool activateNextEvoArrow = false;
};

