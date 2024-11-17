#include "DiglettBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleAudio.h"

DiglettBumper::DiglettBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip) : Bumper(gameAt, position, restitution)
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

	gameAt->App->texture->CreateTexture("Assets/map_diglettBumper.png", "map_diglettBumper");
	diglett_texture = gameAt->App->texture->GetTexture("map_diglettBumper");

	diglett_animator = new Animator(gameAt->App);

	AnimationData diglettIdle = AnimationData("Diglett_Idle");
	diglettIdle.AddSprite(Sprite{ diglett_texture,{0, 0}, {11,16} });
	diglettIdle.AddSprite(Sprite{ diglett_texture,{1, 0}, {11,16} });


	AnimationData diglettHide = AnimationData("Diglett_Hide");
	diglettHide.AddSprite(Sprite{ diglett_texture,{1, 0}, {11,16} });
	diglettHide.AddSprite(Sprite{ diglett_texture,{2, 0}, {11,16} });

	AnimationData diglettHidden = AnimationData("Diglett_Hidden");
	diglettHidden.AddSprite(Sprite{ diglett_texture,{2, 0}, {11,16} });

	diglett_animator->AddAnimation(diglettIdle);
	diglett_animator->AddAnimation(diglettHide);
	diglett_animator->AddAnimation(diglettHidden);
	diglett_animator->SetSpeed(0.15f);

	diglett_animator->SelectAnimation("Diglett_Idle", true);

	audioDiggletBumperId = gameAt->App->audio->LoadFx("Assets/SFX/Game_DiggletBumper.ogg");
}

DiglettBumper::~DiglettBumper()
{
}

update_status DiglettBumper::Update()
{
	Bumper::Update();

	if (hidden && diglett_animator->HasAnimationFinished()) {
		diglett_animator->SelectAnimation("Diglett_Hidden", true);	
	}

	if (remove_time < remove_timer.ReadSec()) {
		hitsRecieved--;
		remove_timer.Start();
		if (hitsRecieved < 0)
			hitsRecieved = 0;
	}

	if (hidden && hidden_time <= hidden_timer.ReadSec()) {
		hidden = false;
		body->GetFixtureList()[0].SetSensor(false);
		diglett_animator->SetSpeed(0.15f);
		diglett_animator->SelectAnimation("Diglett_Idle", true);
		if (hitsRecieved == 3)
			hitsRecieved = 0;
	}

	b2Vec2 renderOffset = { flip ? -11.f : 0.f,-8.f };
	diglett_animator->Update();
	diglett_animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE + renderOffset.x), (int)(body->GetPosition().y * SCREEN_SIZE + renderOffset.y), flip);

	return UPDATE_CONTINUE;
}

bool DiglettBumper::CleanUp()
{
	if (diglett_animator != nullptr) {
		delete diglett_animator;
		diglett_animator = nullptr;
	}

	gameAt->App->physics->world->DestroyBody(body);
	return true;
}

void DiglettBumper::OnHit()
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
	diglett_animator->SelectAnimation("Diglett_Hide", false);
	diglett_animator->SetSpeed(0.07f);
	gameAt->App->audio->PlayFx(audioDiggletBumperId);
	if (hitsRecieved == 3) {
		if (!flip)
			gameAt->PreviousHabitat();
		else
			gameAt->NextHabitat();
	}
}
