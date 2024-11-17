#include "CaveSensorGroup.h"
#include "CaveSensor.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include "CentralScreen.h"
#include <algorithm>

CaveSensorGroup::CaveSensorGroup(ModuleGame* gameAt) : MapSensorGroup(gameAt)
{
	this->gameAt = gameAt;
}

CaveSensorGroup::~CaveSensorGroup()
{

}

update_status CaveSensorGroup::Update()
{
	if (IsKeyPressed(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		bool startValue = mapSensors.front()->IsActive();

		for (size_t i = 0; i < mapSensors.size()-1; i++)
		{
			if (mapSensors[i + 1]->IsActive())
				mapSensors[i]->Activate();
			else
				mapSensors[i]->Desactivate();
		}
		if (startValue)
			mapSensors.back()->Activate();
		else
			mapSensors.back()->Desactivate();
	}

	if (IsKeyPressed(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		bool lastValue = mapSensors.back()->IsActive();

		for (size_t i = mapSensors.size() - 1; i > 0; i--)
		{
			if (mapSensors[i - 1]->IsActive())
				mapSensors[i]->Activate();
			else
				mapSensors[i]->Desactivate();
		}
		if (lastValue)
			mapSensors.front()->Activate();
		else
			mapSensors.front()->Desactivate();
	}

	bool areTwinkling = true;
	for (const auto& sensorPointer : mapSensors)
	{
		if (!sensorPointer->IsTwinkling()) {
			areTwinkling = false;
		}
	}
	if (AllActive() && !areTwinkling)
		OnAllActive();

	for (const auto& sensorPointer : mapSensors)
	{
		if (sensorPointer->HasFinishedTwinkling()) {
			DesactivateAll();
			sensorPointer->FinishTwinkle();
		}
	}

	return UPDATE_CONTINUE;
}

bool CaveSensorGroup::CleanUp()
{

	return true;
}

void CaveSensorGroup::Sort()
{
	std::sort(mapSensors.begin(), mapSensors.end(), []( MapSensor* a, MapSensor* b) {

		CaveSensor* caveA = static_cast<CaveSensor*>(a);
		CaveSensor* caveB = static_cast<CaveSensor*>(b);

		return caveA->GetOrder() < caveB->GetOrder();
	});

}

void CaveSensorGroup::OnAllActive()
{
	gameAt->pointsCounter.Add(4000);

	if(gameAt->screen->CanProgramBeOverwritten()) {
		gameAt->screen->SwitchProgram(new BonusStartProgram());
		gameAt->OpenCave();
	}

	for (const auto& sensorPointer : mapSensors)
	{
		sensorPointer->Twinkle();
	}
}
