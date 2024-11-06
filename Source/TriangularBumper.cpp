#include "TriangularBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include <random>

TriangularBumper::TriangularBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip, int variant) : Bumper(gameAt, position, restitution)
{
	gameAt->AddObject(this);

	this->variant = variant;
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
	bd.position.Set(position.x,position.y); // Set the body's initial position

	body = gameAt->App->physics->world->CreateBody(&bd);

	// Attach the fixture to the body
	b2Fixture* fixture = body->CreateFixture(&chainFixtureDef);

	sensor.SetBodyToTrack(fixture);

	sensor.AcceptOnlyTriggers(false);

	gameAt->App->texture->CreateTexture("Assets/triangular_bumper.png", "triangular_bumper");
	texture = gameAt->App->texture->GetTexture("triangular_bumper");

	animator = new Animator(gameAt->App);

	AnimationData triangularIdle = AnimationData("Triangular_Idle");
	triangularIdle.AddSprite(Sprite{ texture,{0, (float)variant}, {16,32} });

	AnimationData triangularHit = AnimationData("Triangular_Hit");
	triangularHit.AddSprite(Sprite{ texture,{1, (float)variant}, {16,32} });

	animator->AddAnimation(triangularIdle);
	animator->AddAnimation(triangularHit);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Triangular_Idle", true);
}

TriangularBumper::~TriangularBumper()
{
}

update_status TriangularBumper::Update()
{
	if (animator->HasAnimationFinished()) {
		if (gettingHit) {
			gettingHit = false;
		}
		animator->SelectAnimation("Triangular_Idle", true);
	}
	Bumper::Update();

	animator->Update();
	animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE - 1 - 13*flip), (int)(body->GetPosition().y * SCREEN_SIZE), flip);
	return UPDATE_CONTINUE;
}

bool TriangularBumper::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	return true;
}

void TriangularBumper::OnHit()
{
	Bumper::OnHit();
	animator->SelectAnimation("Triangular_Idle", true);
	animator->SelectAnimation("Triangular_Hit", false);

	gettingHit = true;
}