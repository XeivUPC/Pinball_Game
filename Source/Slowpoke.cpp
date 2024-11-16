#include "Slowpoke.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"
#include "Box2DFactory.h"
#include "Pokeball.h"
#include "ModulePhysics.h"

Slowpoke::Slowpoke(ModuleGame* gameAt, b2Vec2 position, float mouthRadius) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { position.x + 7.5f , position.y + 2.2f }, mouthRadius, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetSensor(true);
	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	gameAt->App->texture->CreateTexture("Assets/map_slowpoke.png", "map_slowpoke");
	map_slowpoke = gameAt->App->texture->GetTexture("map_slowpoke");

	map_slowpoke_animator = new Animator(gameAt->App);

	AnimationData mapSlowpokeIdleAnim = AnimationData("MapSlowpokeIdle");
	mapSlowpokeIdleAnim.AddSprite(Sprite{ map_slowpoke,{0, 0}, {32,32} });
	mapSlowpokeIdleAnim.AddSprite(Sprite{ map_slowpoke,{1, 0}, {32,32} });


	AnimationData mapSlowpokeEatAnim = AnimationData("MapSlowpokeEat");
	mapSlowpokeEatAnim.AddSprite(Sprite{ map_slowpoke,{1, 0}, {32,32} });
	mapSlowpokeEatAnim.AddSprite(Sprite{ map_slowpoke,{2, 0}, {32,32} });


	AnimationData mapSlowpokeDropAnim = AnimationData("MapSlowpokeDrop");
	mapSlowpokeDropAnim.AddSprite(Sprite{ map_slowpoke,{2, 0}, {32,32} });
	mapSlowpokeDropAnim.AddSprite(Sprite{ map_slowpoke,{1, 0},{32,32} });

	map_slowpoke_animator->AddAnimation(mapSlowpokeIdleAnim);
	map_slowpoke_animator->AddAnimation(mapSlowpokeEatAnim);
	map_slowpoke_animator->AddAnimation(mapSlowpokeDropAnim);
	map_slowpoke_animator->SetSpeed(1.f);
	map_slowpoke_animator->SelectAnimation("MapSlowpokeIdle", true);

	this->position = position;
}

Slowpoke::~Slowpoke()
{
}

update_status Slowpoke::Update()
{
	map_slowpoke_animator->SetSpeed(1.f);
	if (sensor.OnTriggerEnter()) {
		ballIn = true;
		map_slowpoke_animator->SetSpeed(0.2f);
		map_slowpoke_animator->SelectAnimation("MapSlowpokeEat", false);
		gameAt->pointsCounter.Add(100000);
		mouthTimer.Start();

	}

	if (ballIn) {
		map_slowpoke_animator->SetSpeed(0.1f);
		gameAt->GetPokeball()->SetPosition({ position.x + 5.5f , position.y + 2.2f });
		gameAt->GetPokeball()->SetVelocity({ 0,0 });
		if (mouthTimer.ReadSec() > mouthTime) {
			map_slowpoke_animator->SelectAnimation("MapSlowpokeDrop", false);
			if (map_slowpoke_animator->HasAnimationFinished()) {
				gameAt->GetPokeball()->SetVelocity({ 20,0 });
				ballIn = false;
				map_slowpoke_animator->SelectAnimation("MapSlowpokeIdle", true);
			}
		}
	}

	map_slowpoke_animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);
	
	map_slowpoke_animator->Update();

	return UPDATE_CONTINUE;
}

bool Slowpoke::CleanUp()
{
	if (map_slowpoke_animator != nullptr) {
		delete map_slowpoke_animator;
		map_slowpoke_animator = nullptr;
	}
	gameAt->App->physics->world->DestroyBody(body);

	LOG("Unloading Slowpoke");
	return true;
}
