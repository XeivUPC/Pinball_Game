#include "MapSensorGroup.h"

MapSensorGroup::MapSensorGroup(ModuleGame* gameAt) : MapObject(gameAt)
{
	gameAt->AddObject(this);
}

MapSensorGroup::~MapSensorGroup()
{

}

update_status MapSensorGroup::Update()
{
	return UPDATE_CONTINUE;
}

bool MapSensorGroup::CleanUp()
{
	mapSensors.clear();
	return true;
}

void MapSensorGroup::AddSensor(MapSensor* sensor)
{
	mapSensors.emplace_back(sensor);
}

void MapSensorGroup::RemoveSensor(MapSensor* sensor)
{
	bool found = false;
	int index = 0;
	for (const auto& sensorPointer : mapSensors)
	{
		if (sensorPointer == sensor) {
			found = true;
			break;
		}
		index++;
	}
	if(found)
		mapSensors.erase(mapSensors.begin() + index);
}

void MapSensorGroup::ActivateAll()
{
	for (const auto& sensorPointer : mapSensors)
	{
		sensorPointer->Activate();
	}
}

void MapSensorGroup::DesactivateAll()
{
	for (const auto& sensorPointer : mapSensors)
	{
		sensorPointer->Desactivate();
	}
}

void MapSensorGroup::SwitchAllActiveStatus()
{
	for (const auto& sensorPointer : mapSensors)
	{
		sensorPointer->SwitchActiveStatus();
	}
}

bool MapSensorGroup::AllActive()
{
	bool allActive = true;
	for (const auto& sensorPointer : mapSensors)
	{
		if (!sensorPointer->IsActive()) {
			allActive = false;
			break;
		}
	}
	return allActive;
}

int MapSensorGroup::GetActiveAmount()
{
	int count = 0;
	for (const auto& sensorPointer : mapSensors)
	{
		if (!sensorPointer->IsActive()) {
			count++;
		}
	}
	return count;
}
