#include "BonusMultiplierSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

BonusMultiplierSensor::BonusMultiplierSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int order, int variant) : MapSensor(gameAt, position, width, height, angle)
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
		currentPosition = { body->GetPosition().x, body->GetPosition().y - height * 2};
	}
	else if (angle == 45) {
		currentPosition = { body->GetPosition().x - width / 4, body->GetPosition().y + height * 2 };
	}
	else if (angle == -15) {
		currentPosition = { body->GetPosition().x, body->GetPosition().y };
	}
	else if (angle == 15) {
		currentPosition = { body->GetPosition().x, body->GetPosition().y };
	}
	else if (angle == -28) {
		currentPosition = { body->GetPosition().x, body->GetPosition().y - height };
	}
	else if (angle == 28) {
		currentPosition = { body->GetPosition().x - width / 6, body->GetPosition().y + height * 1.5f};
	}

	// Set the new position and rotation
	body->SetTransform(currentPosition, angle_radians);

	currentPosition = body->GetPosition();

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);

	gameAt->App->texture->CreateTexture("Assets/bonus_multiplier_sensor.png", "bonus_multiplier_sensor");
	texture = gameAt->App->texture->GetTexture("bonus_multiplier_sensor");

	if (variant == 1) {
		gameAt->App->texture->CreateTexture("Assets/bonus_multiplier_blue_bumper.png", "bonus_multiplier_blue_bumper");
		bumperTexture = gameAt->App->texture->GetTexture("bonus_multiplier_blue_bumper");
	}

	pointsOnTrigger = 100;

	twinkleTimer.Start();
}

BonusMultiplierSensor::~BonusMultiplierSensor()
{
}

update_status BonusMultiplierSensor::Update()
{
	

	if (!dualTwinkling) {
		MapSensor::Update();

		if (!enabled)
			return UPDATE_CONTINUE;

		if (active) {
			glowing = true;
		}
		else {
			if (glowing) {
				twinkling = true;
			}
			else {
				twinkling = false;
			}
		}

		if (twinkling && !active) {
			if (twinkleTimer.ReadSec() >= twinkleTime && twinkleTimer.ReadSec() < twinkleTime*2) {
				glowing = !glowing;
			}
			else if(twinkleTimer.ReadSec() >= twinkleTime*2) {
				twinkleTimer.Start();
				glowing = !glowing;
			}
		}

		Rectangle rect = { 8.f * thisNum, 16.f * variant + 8 * glowing,8.f,8.f };

		if (variant == 0 && order == 0) {
			gameAt->App->renderer->Draw(*texture, 34 , 137 , &rect);
		}
		else if(variant == 0 && order == 1){
			gameAt->App->renderer->Draw(*texture, 119, 137, &rect);
		}
		else if (variant == 1 && order == 0) {
			gameAt->App->renderer->Draw(*texture, 34, 135, &rect);
		}
		else if (variant == 1 && order == 1) {
			gameAt->App->renderer->Draw(*texture, 119, 135, &rect);
		}

		Rectangle bumperRect = { 16.f * order,0.f,16.f,16.f };
		if (variant == 1 && !gameStart) {
			if (glowBumperTimer.ReadSec() < glowBumperTime) {
				if (order == 0) {
					gameAt->App->renderer->Draw(*bumperTexture, 35, 144, &bumperRect);
				}
				else if (order == 1) {
					gameAt->App->renderer->Draw(*bumperTexture, 111, 144, &bumperRect);
				}
			}
		}
	}
	else {
		if (!enabled)
			return UPDATE_CONTINUE;

		if (dualTwinklingTimer.ReadSec() >= dualTwinklingTime && dualTwinklingTimer.ReadSec() < dualTwinklingTime * 2) {
			glowing = false;
		} else if (dualTwinklingTimer.ReadSec() >= dualTwinklingTime * 2) {
			glowing = true;
			dualTwinklingTimer.Start();
		}

		if (dualTwinklingTotalTimer.ReadSec() >= dualTwinklingTotalTime) {
			dualTwinkling = false;
			justHit = false;
		}

		Rectangle rect = { 8.f * thisNum, 16.f * variant + 8 * glowing,8.f,8.f };

		if (variant == 0 && order == 0) {
			gameAt->App->renderer->Draw(*texture, 34, 137, &rect);
		}
		else if (variant == 0 && order == 1) {
			gameAt->App->renderer->Draw(*texture, 119, 137, &rect);
		}
		else if (variant == 1 && order == 0) {
			gameAt->App->renderer->Draw(*texture, 34, 135, &rect);
		}
		else if (variant == 1 && order == 1) {
			gameAt->App->renderer->Draw(*texture, 119, 135, &rect);
		}
	}

	return UPDATE_CONTINUE;
}

bool BonusMultiplierSensor::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	return true;
}

void BonusMultiplierSensor::Activate()
{
	MapSensor::Activate();
}

void BonusMultiplierSensor::Desactivate()
{
	MapSensor::Desactivate();
}

void BonusMultiplierSensor::SetGlowing()
{
	glowing = true;
}

void BonusMultiplierSensor::SetNotGlowing()
{
	glowing = false;
}

void BonusMultiplierSensor::SetDualTwinkling()
{
	dualTwinkling = true;
	dualTwinklingTimer.Start();
	dualTwinklingTotalTimer.Start();
}

bool BonusMultiplierSensor::IsDualTwinkling() const
{
	return dualTwinkling;
}

bool BonusMultiplierSensor::JustGotHit() const
{
	return justHit;
}

void BonusMultiplierSensor::SetNumber(int num)
{
	if (thisNum < 10) {
		thisNum = num;
	}
}

int BonusMultiplierSensor::GetNumber(int num) const
{
	return thisNum;
}

int BonusMultiplierSensor::GetOrder() const
{
	return order;
}

void BonusMultiplierSensor::OnTrigger()
{
	if (glowing && !dualTwinkling) {
		SetNotGlowing();
		Activate();
		MapSensor::OnTrigger();
		gameStart = false;
		justHit = true;
	}
	glowBumperTimer.Start();
}
