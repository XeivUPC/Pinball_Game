#include "LapSensorGroup.h"
#include "LapSensor.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include <algorithm>

LapSensorGroup::LapSensorGroup(ModuleGame* gameAt) : MapSensorGroup(gameAt)
{
	this->gameAt = gameAt;
}

LapSensorGroup::~LapSensorGroup()
{

}

update_status LapSensorGroup::Update()
{
	if (mapSensors.back()->IsActive() && !mapSensors.front()->IsActive()) {
		direction = -1;
	}
	else if (mapSensors.front()->IsActive() && !mapSensors.back()->IsActive()) {
		direction = 1;
	}
	else if(!mapSensors.front()->IsActive() && !mapSensors.back()->IsActive()) {
		direction = 0;
	}

	OnAllActive();

	return UPDATE_CONTINUE;
}

bool LapSensorGroup::CleanUp()
{

	return true;
}

void LapSensorGroup::Sort()
{
	std::sort(mapSensors.begin(), mapSensors.end(), [](MapSensor* a, MapSensor* b) {

		LapSensor* sensorA = static_cast<LapSensor*>(a);
		LapSensor* sensorB = static_cast<LapSensor*>(b);

		return sensorA->GetOrder() < sensorB->GetOrder();
		});

}

void LapSensorGroup::OnAllActive()
{
	gameAt->pointsCounter.Add(25000);
	if (direction == -1) {
		// Get +1
	}
	else if (direction == 1) {
		// Evo +1
	}
}
