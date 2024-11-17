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
	
	if (sensor.OnTriggerEnter() && enabled) {

		OnTrigger();
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

void MapSensor::Activate() {
	active = true;
}
void MapSensor::Desactivate() {
	active = false;
}

void MapSensor::SwitchActiveStatus()
{
	if (active)
		Desactivate();
	else
		Activate();
}

bool MapSensor::IsActive()
{
	return active;
}

void MapSensor::Twinkle()
{
	twinkling = true;
	twinkleTimer.Start();
	twinklingTimer.Start();
}

bool MapSensor::IsTwinkling() const
{
	return twinkling;
}

bool MapSensor::HasFinishedTwinkling() const
{
	return finishedTwinkling;
}

void MapSensor::FinishTwinkle()
{
	finishedTwinkling = false;
}

void MapSensor::SetIfEnable(bool status)
{
	enabled = status;
}

void MapSensor::OnTrigger()
{
	if (active) {
		gameAt->pointsCounter.Add(pointsOnTrigger);
		timesActivated++;
	}
}
