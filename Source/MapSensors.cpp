#include "MapSensors.h"

MapSensor::MapSensor(ModuleGame* gameAt, b2Vec2 position, float angle) : MapObject(gameAt)
{
	this->position = position;
}

MapSensor::~MapSensor()
{

}

update_status MapSensor::Update()
{
	if (sensor.OnTriggerEnter()) {
		OnActivation();
	}
	return UPDATE_CONTINUE;
}

bool MapSensor::CleanUp()
{
	return true;
}

int MapSensor::GetTotalActivations()
{
	return timesActivated;
}

void MapSensor::ResetTotalActivations()
{
	timesActivated = 0;
}

void MapSensor::OnActivation()
{
	timesActivated++;
}
