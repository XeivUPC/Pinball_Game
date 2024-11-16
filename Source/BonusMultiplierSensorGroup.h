#pragma once
#include "MapSensorGroup.h"
#include "BonusMultiplierSensor.h"

class BonusMultiplierSensorGroup : public MapSensorGroup {
public:
	BonusMultiplierSensorGroup(ModuleGame* gameAt);
	~BonusMultiplierSensorGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();

protected:
	void OnAllActive() override;
private:
	int totalNum = 0;
};

