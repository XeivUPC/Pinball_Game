#include "PokeballChangerGroup.h"

PokeballChangerGroup::PokeballChangerGroup(ModuleGame* gameAt) : MapSensorGroup(gameAt)
{
	this->gameAt = gameAt;
}

PokeballChangerGroup::~PokeballChangerGroup()
{

}

update_status PokeballChangerGroup::Update()
{
	bool allActive = true;
	hasToChange = false;

	for (PokeballChangerSensor* sensor : sensorGroup) {
		if (sensor->IsActive()) {
			allActive = false;
		}
	}

	if (allActive) {
		hasToChange = true;
	}

	return UPDATE_CONTINUE;
}

bool PokeballChangerGroup::CleanUp()
{
	for (PokeballChangerSensor* sensor : sensorGroup) {
		delete sensor;
	}
	return true;
}

void PokeballChangerGroup::AddSensor(PokeballChangerSensor* mapSensor)
{
	sensorGroup.emplace_back(mapSensor);
}

bool PokeballChangerGroup::ChangePokeball()
{
	return hasToChange;
}

void PokeballChangerGroup::Restart()
{
	for (PokeballChangerSensor* sensor : sensorGroup) {
		sensor->ResetTotalActivations();
	}
}
