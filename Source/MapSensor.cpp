#include "MapSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

MapSensor::MapSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle) : MapObject(gameAt)
{
	this->position = position;
	this->angle = angle;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateBox(gameAt->App->physics->world, { position.x , position.y }, width, height, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetSensor(true);
	body->GetFixtureList()[0].SetDensity(1);
	float angle_radians = angle * b2_pi / 180.0f;
	// Get current position
	b2Vec2 currentPosition = body->GetPosition();

	// Set the new position and rotation
	body->SetTransform(currentPosition, angle_radians);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);
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
