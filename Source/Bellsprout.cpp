#include "Bellsprout.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"
#include "Box2DFactory.h"
#include "Pokeball.h"
#include "CentralScreen.h"
#include "MapCave.h"
#include "GameUI.h"

Bellsprout::Bellsprout(ModuleGame* gameAt, b2Vec2 position, float mouthRadius) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { position.x+5 , position.y +4}, mouthRadius, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetSensor(true);
	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);


	gameAt->App->texture->CreateTexture("Assets/map_bellsprout.png", "map_bellsprout");
	map_bellsprout = gameAt->App->texture->GetTexture("map_bellsprout");

	map_bellsprout_animator = new Animator(gameAt->App);

	AnimationData mapBellsproutIdleAnim = AnimationData("MapBellsproutIdle");
	mapBellsproutIdleAnim.AddSprite(Sprite{ map_bellsprout,{1, 0}, {32,40} });
	mapBellsproutIdleAnim.AddSprite(Sprite{ map_bellsprout,{0, 0}, {32,40} });

	AnimationData mapBellsproutEatAnim = AnimationData("MapBellsproutEat");
	mapBellsproutEatAnim.AddSprite(Sprite{ map_bellsprout,{2, 0}, {32,40} });
	mapBellsproutEatAnim.AddSprite(Sprite{ map_bellsprout,{3, 0}, {32,40} });


	AnimationData mapBellsproutDropAnim = AnimationData("MapBellsproutDrop");
	mapBellsproutDropAnim.AddSprite(Sprite{ map_bellsprout,{3, 0}, {32,40} });
	mapBellsproutDropAnim.AddSprite(Sprite{ map_bellsprout,{2, 0}, {32,40} });

	map_bellsprout_animator->AddAnimation(mapBellsproutIdleAnim);
	map_bellsprout_animator->AddAnimation(mapBellsproutDropAnim);
	map_bellsprout_animator->AddAnimation(mapBellsproutEatAnim);
	map_bellsprout_animator->SetSpeed(1.f);
	map_bellsprout_animator->SelectAnimation("MapBellsproutIdle", true);

	this->position = position;
}

Bellsprout::~Bellsprout()
{
}

update_status Bellsprout::Update()
{
	map_bellsprout_animator->SetSpeed(1.f);
	if (sensor.OnTriggerEnter()) {
		ballIn = true;
		map_bellsprout_animator->SetSpeed(0.2f);
		map_bellsprout_animator->SelectAnimation("MapBellsproutEat", false);
		gameAt->pointsCounter.Add(100000);
		mouthTimer.Start();

		if (gameAt->CanCapture() && gameAt->screen->CanProgramBeOverwritten()) {

			int selectedLanguage = gameAt->App->userPreferences->GetLanguage();
			gameAt->GetUI()->AddText(catchModeUIText[selectedLanguage]);

			gameAt->screen->SwitchProgram(new CapturePokemon);
			gameAt->CloseCave();

			gameAt->StartCapture();
		}
		
	}

	if (ballIn) {
		map_bellsprout_animator->SetSpeed(0.1f);
		gameAt->GetPokeball()->SetPosition({ position.x + 5 , position.y + 2.7f });
		gameAt->GetPokeball()->SetVelocity({ 0,0 });
		if (mouthTimer.ReadSec() > mouthTime) {
			map_bellsprout_animator->SelectAnimation("MapBellsproutDrop", false);
			if (map_bellsprout_animator->HasAnimationFinished()) {
				gameAt->GetPokeball()->SetVelocity({ 0,10 });
				ballIn = false;
				map_bellsprout_animator->SelectAnimation("MapBellsproutIdle", true);
			}
		}
		
	}
	map_bellsprout_animator->Animate((int)(position.x*SCREEN_SIZE), (int)(position.y *SCREEN_SIZE), false);

	map_bellsprout_animator->Update();
	
	return UPDATE_CONTINUE;
}

bool Bellsprout::CleanUp()
{
	if (map_bellsprout_animator != nullptr) {
		delete map_bellsprout_animator;
		map_bellsprout_animator = nullptr;
	}

	gameAt->App->physics->world->DestroyBody(body);

	LOG("Unloading Bellsprout");
	return true;
}
