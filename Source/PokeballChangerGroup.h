#pragma once
#include "MapSensorGroup.h"
#include "PokeballChangerSensor.h"

class PokeballChangerGroup : public MapSensorGroup {
public:
	PokeballChangerGroup(ModuleGame* gameAt);
	~PokeballChangerGroup();

	update_status Update();
	bool CleanUp() override;

	void AddSensor(PokeballChangerSensor* mapSensor);
	bool ChangePokeball();
	void Restart();

protected:
	std::vector<PokeballChangerSensor*> sensorGroup;

	bool hasToChange = false;
};

