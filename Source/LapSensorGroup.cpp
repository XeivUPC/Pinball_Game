#include "LapSensorGroup.h"
#include "LapSensor.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include "PokeBall.h"
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
	else if (!mapSensors.front()->IsActive() && !mapSensors.back()->IsActive()) {
		direction = 0;
	}
	if (gameAt->GetPokeball()->GetPosition().y > 155.f / SCREEN_SIZE) {
		DesactivateAll();
		direction = 0;
	}

	if (AllActive())
		OnAllActive();

	return UPDATE_CONTINUE;
}

bool LapSensorGroup::CleanUp()
{
	mapSensors.clear();
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

bool LapSensorGroup::HaveToActivateArrowGet()
{
	if (activateNextGetArrow) {
		activateNextGetArrow = false;
		return true;
	}
	else {
		return activateNextGetArrow;
	}
}

bool LapSensorGroup::HaveToActivateArrowEvo()
{
	if (activateNextEvoArrow) {
		activateNextEvoArrow = false;
		return true;
	}
	else {
		return activateNextEvoArrow;
	}
}

void LapSensorGroup::OnAllActive()
{
	if (direction == -1) {
		gameAt->pointsCounter.Add(4000);
		activateNextGetArrow = true;
		DesactivateAll();
	}
	else if (direction == 1) {
		gameAt->pointsCounter.Add(4000);
		activateNextEvoArrow = true;
		DesactivateAll();
	}
}
