#pragma once
#include "MapSensorGroup.h"
#include "PokeballChangerSensor.h"

class PokeballChangerGroup : public MapSensorGroup {
public:
	PokeballChangerGroup(ModuleGame* gameAt);
	~PokeballChangerGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();

protected:
	void OnAllActive() override;

	bool hasToChange = false;

	int audioPokeballSensorId = -1;
};

