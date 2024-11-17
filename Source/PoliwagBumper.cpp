#include "PoliwagBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "BonusFinalBall.h"

PoliwagBumper::PoliwagBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip) : Bumper(gameAt, position, restitution)
{

	gameAt->AddObject(this);
	this->flip = flip;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	b2ChainShape chainShape;
	chainShape.CreateLoop(&vertices[0], vertices.size());

	b2FixtureDef chainFixtureDef;
	chainFixtureDef.shape = &chainShape;
	chainFixtureDef.density = 1.0f;
	chainFixtureDef.restitution = 0.8f;
	chainFixtureDef.friction = 1.f;
	chainFixtureDef.userData = fixtureData;

	b2BodyDef bd;
	bd.type = b2_staticBody; // Set the body type to static
	bd.position.Set(position.x, position.y); // Set the body's initial position

	body = gameAt->App->physics->world->CreateBody(&bd);
	b2Fixture* fixture = body->CreateFixture(&chainFixtureDef);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);


	gameAt->App->texture->CreateTexture("Assets/map_poliwagBumper.png", "map_poliwagBumper");
	poliwag_texture = gameAt->App->texture->GetTexture("map_poliwagBumper");

	poliwag_animator = new Animator(gameAt->App);

	AnimationData poliwagIdle = AnimationData("Poliwag_Idle");
	poliwagIdle.AddSprite(Sprite{ poliwag_texture,{0, 0}, {8,16} });

	AnimationData poliwagHidden = AnimationData("Poliwag_Hidden");
	poliwagHidden.AddSprite(Sprite{ poliwag_texture,{1, 0}, {8,16} });

	poliwag_animator->AddAnimation(poliwagIdle);
	poliwag_animator->AddAnimation(poliwagHidden);
	poliwag_animator->SetSpeed(0.15f);

	poliwag_animator->SelectAnimation("Poliwag_Idle", true);
}

PoliwagBumper::~PoliwagBumper()
{
}

update_status PoliwagBumper::Update()
{
	Bumper::Update();

	if (hidden && hidden_time <= hidden_timer.ReadSec()) {
		hidden = false;
		body->GetFixtureList()[0].SetSensor(false);
		poliwag_animator->SelectAnimation("Poliwag_Idle", true);
		if (hitsRecieved == 3)
			hitsRecieved = 0;
	}

	if (remove_time < remove_timer.ReadSec()) {
		hitsRecieved--;
		remove_timer.Start();
		if (hitsRecieved < 0)
			hitsRecieved = 0;
	}

	b2Vec2 renderOffset = { flip ? -8.f  : -0.f,-8.f };
	poliwag_animator->Update();
	poliwag_animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE + renderOffset.x), (int)(body->GetPosition().y * SCREEN_SIZE + renderOffset.y), flip);

	return UPDATE_CONTINUE;
}

bool PoliwagBumper::CleanUp()
{
	if (poliwag_animator != nullptr) {
		delete poliwag_animator;
		poliwag_animator = nullptr;
	}
	gameAt->App->physics->world->DestroyBody(body);
	return true;
}

void PoliwagBumper::OnHit()
{
	if (hidden)
		return;

	if (hitsRecieved == 3)
		hitsRecieved = 0;

	Bumper::OnHit();
	remove_timer.Start();
	hidden = true;
	gameAt->pointsCounter.Add(5000);
	body->GetFixtureList()[0].SetSensor(true);

	hidden_timer.Start();
	poliwag_animator->SelectAnimation("Poliwag_Hidden", true);
	if (hitsRecieved == 3) {
		gameAt->finalBallUI->AddInBonus(5);

		if (!flip)
			gameAt->PreviousHabitat();
		else
			gameAt->NextHabitat();
	}
}
