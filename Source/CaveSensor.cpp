#include "CaveSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleUserPreferences.h"

CaveSensor::CaveSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int order, int variant) : MapSensor(gameAt, position, width, height, angle)
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

	// Set the new position and rotation
	body->SetTransform(currentPosition, angle_radians);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);

	gameAt->App->texture->CreateTexture("Assets/cave_sensor.png", "cave_sensor");
	texture = gameAt->App->texture->GetTexture("cave_sensor");

	selectedLanguage = gameAt->App->userPreferences->GetLanguage();

	if (selectedLanguage == 0) {
		selectedLanguage = 1;
	}
	if (selectedLanguage >= 1) {
		selectedLanguage = 2;
	}

	animator = new Animator(gameAt->App);

	AnimationData caveSensorUnactive = AnimationData("Cave_Sensor_Unactive");
	caveSensorUnactive.AddSprite(Sprite{ texture,{(float)variant * 4 + order, 0}, {8,16} });

	AnimationData caveSensorActive = AnimationData("Cave_Sensor_Active");
	caveSensorActive.AddSprite(Sprite{ texture,{(float)variant * 4 + order, (float)selectedLanguage}, {8,16} });

	animator->AddAnimation(caveSensorUnactive);
	animator->AddAnimation(caveSensorActive);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Cave_Sensor_Unactive", true);

	cooldownTimer.Start();
}

CaveSensor::~CaveSensor()
{
}

update_status CaveSensor::Update()
{
	MapSensor::Update();

	if (active) {
		animator->SelectAnimation("Cave_Sensor_Active", true);
	}
	else {
		animator->SelectAnimation("Cave_Sensor_Unactive", true);
	}

	animator->Update();
	if (twinkling) {
		if (twinklingTimer.ReadSec() >= twinklingTime) {
			animator->SetIfCanDraw(!animator->CanDraw());
			twinklingTimer.Start();
		}
		if (twinkleTimer.ReadSec() >= twinkleTime) {
			animator->SetIfCanDraw(true);
			Desactivate();
			twinkling = false;
			finishedTwinkling = true;
		}
	}
	animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE) - 4, (int)(body->GetPosition().y * SCREEN_SIZE - 13), false);
	return UPDATE_CONTINUE;
}

bool CaveSensor::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	return true;
}

void CaveSensor::Activate()
{
	MapSensor::Activate();
}

void CaveSensor::Desactivate()
{
	MapSensor::Desactivate();
}

int CaveSensor::GetOrder() const
{
	return order;
}

void CaveSensor::OnTrigger()
{
	if (twinkling) {
		return;
	}
	if (active) {
		if (cooldownTimer.ReadSec() < cooldownTime) {
			return;
		}
	}

	SwitchActiveStatus();
	MapSensor::OnTrigger();

	if (active) {
		cooldownTimer.Start();
	}
}
