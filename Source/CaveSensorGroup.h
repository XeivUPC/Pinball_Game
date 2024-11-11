#pragma once
#include "MapSensorGroup.h"
#include "CaveSensor.h"

class CaveSensorGroup : public MapSensorGroup {
public:
	CaveSensorGroup(ModuleGame* gameAt);
	~CaveSensorGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();

protected:
	void OnAllActive() override;
};

