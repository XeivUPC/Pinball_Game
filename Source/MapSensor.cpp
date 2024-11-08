#include "MapSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

MapSensor::MapSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle) : MapObject(gameAt)
{
	this->position = position;
	this->angle = angle;
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

void MapSensor::SwitchActivation()
{
	if (!active) {
		active = true;
	}
	else {
		active = false;
	}
}

bool MapSensor::IsActive()
{
	return active;
}

void MapSensor::OnActivation()
{
	timesActivated++;
}
