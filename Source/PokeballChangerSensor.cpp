#include "PokeballChangerSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

PokeballChangerSensor::PokeballChangerSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int order, int variant) : MapSensor(gameAt, position, width, height, angle)
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

	gameAt->App->texture->CreateTexture("Assets/pokeball_changer_sensor.png", "pokeball_changer_sensor");
	texture = gameAt->App->texture->GetTexture("pokeball_changer_sensor");

	animator = new Animator(gameAt->App);

	AnimationData pokeballSensorUnactive = AnimationData("Pokeball_Sensor_Unactive");
	pokeballSensorUnactive.AddSprite(Sprite{ texture,{0, (float)variant}, {8,16} });

	AnimationData pokeballSensorActive = AnimationData("Pokeball_Sensor_Active");
	pokeballSensorActive.AddSprite(Sprite{ texture,{1, (float)variant}, {8,16} });

	animator->AddAnimation(pokeballSensorUnactive);
	animator->AddAnimation(pokeballSensorActive);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Pokeball_Sensor_Unactive", true);

	cooldownTimer.Start();
}

PokeballChangerSensor::~PokeballChangerSensor()
{
}

update_status PokeballChangerSensor::Update()
{
	MapSensor::Update();

	if (active) {
		animator->SelectAnimation("Pokeball_Sensor_Active", true);
	}
	else {
		animator->SelectAnimation("Pokeball_Sensor_Unactive", true);
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

	animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE) - 4, (int)(body->GetPosition().y * SCREEN_SIZE - 10), false);
	return UPDATE_CONTINUE;
}

bool PokeballChangerSensor::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	return true;
}

void PokeballChangerSensor::Activate()
{
	MapSensor::Activate();
}

void PokeballChangerSensor::Desactivate()
{
	MapSensor::Desactivate();
}

int PokeballChangerSensor::GetOrder() const
{
	return order;
}

void PokeballChangerSensor::OnTrigger()
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
