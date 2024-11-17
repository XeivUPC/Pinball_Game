#include "StaryuBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleAudio.h"

StaryuBumper::StaryuBumper(ModuleGame* gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip) : Bumper(gameAt, position, restitution)
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


	gameAt->App->texture->CreateTexture("Assets/map_staryuBumper.png", "map_staryuBumper");
	staryu_texture = gameAt->App->texture->GetTexture("map_staryuBumper");

	staryu_animator = new Animator(gameAt->App);

	AnimationData offAnim = AnimationData("Bumper_Off");
	offAnim.AddSprite(Sprite{ staryu_texture,{0, 0}, {22,18} });

	AnimationData onAnim = AnimationData("Bumper_On");
	onAnim.AddSprite(Sprite{ staryu_texture,{1, 0}, {22,18} });

	staryu_animator->AddAnimation(offAnim);
	staryu_animator->AddAnimation(onAnim);
	staryu_animator->SetSpeed(0.25f);

	staryu_animator->SelectAnimation("Bumper_Off", true);

	audioStaryuBumperId = gameAt->App->audio->LoadFx("Assets/SFX/Game_StaryuBumper.ogg");
}

StaryuBumper::~StaryuBumper()
{
}

update_status StaryuBumper::Update()
{
	Bumper::Update();

	if (recovering && recover_time <= recover_timer.ReadSec()) {
		recovering = false;
		body->GetFixtureList()[0].SetSensor(false);
		staryu_animator->SelectAnimation("Bumper_Off", true);
	}

	b2Vec2 renderOffset = { flip ? -11.f : -0.f,-0.f };
	staryu_animator->Update();
	staryu_animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE + renderOffset.x), (int)(body->GetPosition().y * SCREEN_SIZE + renderOffset.y), flip);

	return UPDATE_CONTINUE;
}

bool StaryuBumper::CleanUp()
{
	if (staryu_animator != nullptr) {
		delete staryu_animator;
		staryu_animator = nullptr;
	}

	gameAt->App->physics->world->DestroyBody(body);
	return true;
}

bool StaryuBumper::IsActive()
{
	return isActive;
}

void StaryuBumper::OnHit()
{
	if (recovering)
		return;
	Bumper::OnHit();
	recovering = true;
	gameAt->pointsCounter.Add(50000);
	body->GetFixtureList()[0].SetSensor(true);
	gameAt->App->audio->PlayFx(audioStaryuBumperId);

	recover_timer.Start();
	staryu_animator->SelectAnimation("Bumper_On", true);
	if (hitsRecieved > 3) {
		hitsRecieved = 3;
	}

	isActive = !isActive;
}
