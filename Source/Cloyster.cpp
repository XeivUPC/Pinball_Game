#include "Cloyster.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"
#include "ModuleAudio.h"
#include "Box2DFactory.h"
#include "Pokeball.h"
#include "CentralScreen.h"
#include "ModulePhysics.h"
#include "MapCave.h"
#include "GameUI.h"

Cloyster::Cloyster(ModuleGame* gameAt, b2Vec2 position, float mouthRadius) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { position.x+1  , position.y + 3.5f }, mouthRadius, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetSensor(true);
	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	gameAt->App->texture->CreateTexture("Assets/map_cloyster.png", "map_cloyster");
	map_cloyster = gameAt->App->texture->GetTexture("map_cloyster");

	map_cloyster_animator = new Animator(gameAt->App);

	AnimationData mapCloysterIdleAnim = AnimationData("MapCloysterIdle");
	mapCloysterIdleAnim.AddSprite(Sprite{ map_cloyster,{0, 0}, {24,32} });
	mapCloysterIdleAnim.AddSprite(Sprite{ map_cloyster,{1, 0}, {24,32} });
	

	AnimationData mapCloysterEatAnim = AnimationData("MapCloysterEat");
	mapCloysterEatAnim.AddSprite(Sprite{ map_cloyster,{1, 0}, {24,32} });
	mapCloysterEatAnim.AddSprite(Sprite{ map_cloyster,{2, 0}, {24,32} });


	AnimationData mapCloysterDropAnim = AnimationData("MapCloysterDrop");
	mapCloysterDropAnim.AddSprite(Sprite{ map_cloyster,{2, 0}, {24,32} });
	mapCloysterDropAnim.AddSprite(Sprite{ map_cloyster,{1, 0},{24,32} });

	map_cloyster_animator->AddAnimation(mapCloysterIdleAnim);
	map_cloyster_animator->AddAnimation(mapCloysterEatAnim);
	map_cloyster_animator->AddAnimation(mapCloysterDropAnim);
	map_cloyster_animator->SetSpeed(1.f);
	map_cloyster_animator->SelectAnimation("MapCloysterIdle", true);

	this->position = position;

	audioBellsproutAbsorbId = gameAt->App->audio->LoadFx("Assets/SFX/Game_BellsproutAbsorb.ogg");
	audioBellsproutHawkTuahId = gameAt->App->audio->LoadFx("Assets/SFX/Game_BellsproutHawkTuah.ogg");
}

Cloyster::~Cloyster()
{
}

update_status Cloyster::Update()
{
	map_cloyster_animator->SetSpeed(1.f);
	if (sensor.OnTriggerEnter()) {
		ballIn = true;
		map_cloyster_animator->SetSpeed(0.2f);
		map_cloyster_animator->SelectAnimation("MapCloysterEat", false);
		gameAt->pointsCounter.Add(100000);
		mouthTimer.Start();
		gameAt->App->audio->PlayFx(audioBellsproutAbsorbId);
		if (gameAt->CanCapture() && gameAt->screen->CanProgramBeOverwritten()) {

			const char* text = "PLACEHOLDER";
			gameAt->GetUI()->AddText(text);

			gameAt->screen->SwitchProgram(new CapturePokemon);
			gameAt->CloseCave();

			gameAt->StartCapture();
		}

	}

	if (ballIn) {
		map_cloyster_animator->SetSpeed(0.1f);
		gameAt->GetPokeball()->SetPosition({ position.x +3 , position.y + 3.5f });
		gameAt->GetPokeball()->SetVelocity({ 0,0 });
		if (mouthTimer.ReadSec() > mouthTime) {
			map_cloyster_animator->SelectAnimation("MapCloysterDrop", false);
			gameAt->App->audio->PlayFx(audioBellsproutHawkTuahId);
			if (map_cloyster_animator->HasAnimationFinished()) {
				gameAt->GetPokeball()->SetVelocity({ -20,0 });
				ballIn = false;
				map_cloyster_animator->SelectAnimation("MapCloysterIdle", true);
			}
		}
	}

	map_cloyster_animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);

	map_cloyster_animator->Update();

	return UPDATE_CONTINUE;
}

bool Cloyster::CleanUp()
{
	if (map_cloyster_animator != nullptr) {
		delete map_cloyster_animator;
		map_cloyster_animator = nullptr;
	}	
	
	gameAt->App->physics->world->DestroyBody(body);


	LOG("Unloading Cloyster");
	return true;
}
