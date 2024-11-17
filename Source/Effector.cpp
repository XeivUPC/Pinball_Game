#include "Effector.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2DFactory.h"

Effector::Effector(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	this->position = position;
}

Effector::Effector(ModuleGame* gameAt, b2Vec2 position, float width, float height) : MapObject(gameAt)
{
	this->position = position;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateBox(gameAt->App->physics->world, { position.x + width / 2 , position.y + height / 2 }, width, height, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetSensor(true);
	body->GetFixtureList()[0].SetDensity(1);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);
}

Effector::Effector(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices) : MapObject(gameAt)
{
	this->position = position;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	b2ChainShape chainShape;
	chainShape.CreateLoop(&vertices[0], vertices.size());

	b2FixtureDef chainFixtureDef;
	chainFixtureDef.shape = &chainShape;
	chainFixtureDef.density = 1.0f;
	chainFixtureDef.friction = 1.f;
	chainFixtureDef.userData = fixtureData;

	b2BodyDef bd;
	bd.type = b2_staticBody; // Set the body type to static
	bd.position.Set(position.x, position.y); // Set the body's initial position

	body = gameAt->App->physics->world->CreateBody(&bd);

	// Attach the fixture to the body
	b2Fixture* fixture = body->CreateFixture(&chainFixtureDef);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);
}

Effector::~Effector()
{
}

update_status Effector::Update()
{
	b2Body* bodyTrigger = sensor.OnTriggerEnterGet();
	if (bodyTrigger != nullptr && enabled) {
		OnEnter(bodyTrigger);
	}
	bodyTrigger = nullptr;
	bodyTrigger = sensor.OnTriggerExitGet();
	if (bodyTrigger != nullptr && enabled) {
		OnExit(bodyTrigger);
	}
	return UPDATE_CONTINUE;
}

bool Effector::CleanUp()
{
	bodiesInside.clear();
	gameAt->App->physics->world->DestroyBody(body);
	return true;
}

void Effector::SetIfEnable(bool status)
{
	enabled = status;
}

void Effector::OnEnter(b2Body* enterBody)
{
	bodiesInside.push_back(enterBody);
}

void Effector::OnExit(b2Body* exitBody)
{
	int index = 0;

	for (const auto& bodyPointer : bodiesInside) {
		if (bodiesInside.at(index) == exitBody) {
			bodiesInside.erase(bodiesInside.begin() + index);
			break;
		}
		index++;
	}
}