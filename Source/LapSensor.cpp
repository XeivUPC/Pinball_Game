#include "LapSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

LapSensor::LapSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int order, int variant) : MapSensor(gameAt, position, width, height, angle)
{
	gameAt->AddObject(this);

	this->variant = variant;
	this->order = order;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateBox(gameAt->App->physics->world, { position.x + width / 2 , position.y + height / 2 }, width, height, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetSensor(true);
	body->GetFixtureList()[0].SetDensity(1);
	float angle_radians = angle * b2_pi / 180.0f;
	// Get current position
	b2Vec2 currentPosition = body->GetPosition();

	if (angle == -45) {
		currentPosition = { body->GetPosition().x + width/2, body->GetPosition().y - height/2};
	}
	else if (angle == 45) {
		currentPosition = { body->GetPosition().x - width / 2, body->GetPosition().y };
	}
	else if (angle == -15) {
		currentPosition = { body->GetPosition().x, body->GetPosition().y };
	}
	else if (angle == 15) {
		currentPosition = { body->GetPosition().x, body->GetPosition().y };
	}

	// Set the new position and rotation
	body->SetTransform(currentPosition, angle_radians);

	currentPosition = body->GetPosition();

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);


	pointsOnTrigger = 100;
}

LapSensor::~LapSensor()
{
}

update_status LapSensor::Update()
{
	
	MapSensor::Update();

	if (!enabled)
		return UPDATE_CONTINUE;

	if (cooldownTimer.ReadSec() >= cooldownTime) {
		Desactivate();
	}

	return UPDATE_CONTINUE;
}

bool LapSensor::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	return true;
}

void LapSensor::Activate()
{
	MapSensor::Activate();
}

void LapSensor::Desactivate()
{
	MapSensor::Desactivate();
}

int LapSensor::GetOrder() const
{
	return order;
}

void LapSensor::OnTrigger()
{
	MapSensor::OnTrigger();
	cooldownTimer.Start();
	Activate();
}
