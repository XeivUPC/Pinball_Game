#include "PsyduckBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

PsyduckBumper::PsyduckBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip) : Bumper(gameAt, position, restitution)
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

	gameAt->App->texture->CreateTexture("Assets/map_psyduckBumper.png", "map_psyduckBumper");
	psyduck_texture = gameAt->App->texture->GetTexture("map_psyduckBumper");

	psyduck_animator = new Animator(gameAt->App);

	AnimationData psyduckIdle = AnimationData("Psyduck_Idle");
	psyduckIdle.AddSprite(Sprite{ psyduck_texture,{0, 0}, {15,24} });


	AnimationData psyduckHide = AnimationData("Psyduck_Hide");
	psyduckHide.AddSprite(Sprite{ psyduck_texture,{1, 0}, {15,24} });

	AnimationData psyduckAngry1 = AnimationData("Psyduck_Angry1");
	psyduckAngry1.AddSprite(Sprite{ psyduck_texture,{2, 0}, {15,24} });

	AnimationData psyduckAngry2 = AnimationData("Psyduck_Angry2");
	psyduckAngry2.AddSprite(Sprite{ psyduck_texture,{3, 0}, {15,24} });

	AnimationData psyduckAngry3 = AnimationData("Psyduck_Angry3");
	psyduckAngry3.AddSprite(Sprite{ psyduck_texture,{4, 0}, {15,24} });

	psyduck_animator->AddAnimation(psyduckIdle);
	psyduck_animator->AddAnimation(psyduckHide);
	psyduck_animator->AddAnimation(psyduckAngry1);
	psyduck_animator->AddAnimation(psyduckAngry2);
	psyduck_animator->AddAnimation(psyduckAngry3);
	psyduck_animator->SetSpeed(0.5f);

	psyduck_animator->SelectAnimation("Psyduck_Idle", true);
}

PsyduckBumper::~PsyduckBumper()
{
}

update_status PsyduckBumper::Update()
{
	Bumper::Update();

	if (hidden && psyduck_animator->HasAnimationFinished()) {
		psyduck_animator->SelectAnimation("Psyduck_Angry"+ std::to_string(hitsRecieved), true);
	}

	if (hidden && hidden_time <= hidden_timer.ReadSec()) {
		hidden = false;
		body->GetFixtureList()[0].SetSensor(false);
		psyduck_animator->SelectAnimation("Psyduck_Idle", true);
	}

	b2Vec2 renderOffset = { flip ? -15.f : 0.f,-14.f };
	psyduck_animator->Update();
	psyduck_animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE + renderOffset.x), (int)(body->GetPosition().y * SCREEN_SIZE + renderOffset.y), flip);

	return UPDATE_CONTINUE;
}

bool PsyduckBumper::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);
	return false;
}

void PsyduckBumper::OnHit()
{
	if (hidden)
		return;
	Bumper::OnHit();
	hidden = true;
	gameAt->pointsCounter.Add(5000);
	body->GetFixtureList()[0].SetSensor(true);

	hidden_timer.Start();
	psyduck_animator->SelectAnimation("Psyduck_Hide", false);

	if (hitsRecieved > 3) {
		hitsRecieved = 0;
		if (!flip)
			gameAt->NextHabitat();
		else
			gameAt->PreviousHabitat();
	}
}
