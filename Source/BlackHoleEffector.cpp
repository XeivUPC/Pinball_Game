#include "BlackHoleEffector.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2DFactory.h"

BlackHoleEffector::BlackHoleEffector(ModuleGame* gameAt, b2Vec2 position, float radius) : Effector (gameAt, position)
{
	gameAt->AddObject(this);

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { position.x, position.y }, radius, fixtureData);
	body->SetType(b2_staticBody);

	body->GetFixtureList()[0].SetSensor(true);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);
}

BlackHoleEffector::~BlackHoleEffector()
{
}

update_status BlackHoleEffector::Update()
{
	Effector::Update();

	if (enabled) {
		for (const auto& bodyPointer : bodiesInside) {
			b2Vec2 bodyPos = bodyPointer->GetWorldCenter();

			b2Vec2 direction = position - bodyPos;

			direction.Normalize();

			float distance = direction.Length();
			float strength = 50.0f / (distance * distance);

			b2Vec2 finalDirection = { direction.x * strength, direction.y * strength };
			bodyPointer->ApplyLinearImpulseToCenter(finalDirection, true);
		}
	}

	return UPDATE_CONTINUE;
}

bool BlackHoleEffector::CleanUp()
{
	Effector::CleanUp();
	return true;
}