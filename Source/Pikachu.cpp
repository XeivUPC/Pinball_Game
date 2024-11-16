#include "Pikachu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"
#include "Box2DFactory.h"
#include "Pokeball.h"
#include "CentralScreen.h"

Pikachu::Pikachu(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	width /= SCREEN_SIZE;
	height /= SCREEN_SIZE;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateBox(gameAt->App->physics->world, { position.x + width - 0.2f, position.y - height / 2 - 0.7f }, (float)width, (float)height, fixtureData);
	body->SetType(b2_dynamicBody);
	body->GetFixtureList()[0].SetSensor(true);
	body->SetGravityScale(0);
	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	gameAt->App->texture->CreateTexture("Assets/map_pikachu.png", "map_pikachu");
	map_pikachu = gameAt->App->texture->GetTexture("map_pikachu");

	map_pikachu_animator = new Animator(gameAt->App);

	AnimationData mapPikachuAnim = AnimationData("MapPikachuAnim");
	mapPikachuAnim.AddSprite(Sprite{ map_pikachu,{0, 0}, {16,16} });
	mapPikachuAnim.AddSprite(Sprite{ map_pikachu,{1, 0}, {16,16} });

	AnimationData mapPikachuEnergizeAnim = AnimationData("MapPikachuEnergizeAnim");
	mapPikachuEnergizeAnim.AddSprite(Sprite{ map_pikachu,{2, 0}, {16,16} });

	map_pikachu_animator->AddAnimation(mapPikachuEnergizeAnim);
	map_pikachu_animator->AddAnimation(mapPikachuAnim);
	map_pikachu_animator->SetSpeed(0.3f);
	map_pikachu_animator->SelectAnimation("MapPikachuAnim", true);


	gameAt->App->texture->CreateTexture("Assets/map_pikachuEnergy.png", "map_pikachuEnergy");
	map_pikachuEnergy = gameAt->App->texture->GetTexture("map_pikachuEnergy");

	map_pikachuEnergy_animator = new Animator(gameAt->App);

	AnimationData mapPikachuEnergyAnim = AnimationData("MapPikachuEnergyAnim");
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{0, 0}, {16,32} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{1, 0}, {16,32} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{2, 0}, {16,32} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{3, 0}, {16,32} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{4, 0}, {16,32} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{5, 0}, {16,32} });
	

	AnimationData mapPikachuEnergyIdleAnim = AnimationData("MapPikachuEnergyIdleAnim");
	mapPikachuEnergyIdleAnim.AddSprite(Sprite{ map_pikachuEnergy,{6, 0}, {16,16} });

	map_pikachuEnergy_animator->AddAnimation(mapPikachuEnergyIdleAnim);
	map_pikachuEnergy_animator->AddAnimation(mapPikachuEnergyAnim);
	map_pikachuEnergy_animator->SetSpeed(0.3f);
	map_pikachuEnergy_animator->SelectAnimation("MapPikachuEnergyIdleAnim", true);

	bool is_in_left = true;

	this->position = position;

}

Pikachu::~Pikachu()
{

}

update_status Pikachu::Update()
{
	map_pikachu_animator->SetSpeed(0.3f);
	//Configure position
	if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		position.x = 8.f / SCREEN_SIZE;
		body->SetTransform({ position.x + width - 0.5f, position.y - height / 2 - 0.7f}, 0);
	}
	else if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		position.x = 139.f / SCREEN_SIZE;
		body->SetTransform({ position.x + width - 0.2f, position.y - height / 2 - 0.7f }, 0);
	}
	
	if (sensor.OnTriggerEnter() && gameAt->IsEnergyCharged()) {
		gameAt->UseEnergy();
		ballIn = true;
		map_pikachu_animator->SelectAnimation("MapPikachuEnergizeAnim", false);
		map_pikachuEnergy_animator->SelectAnimation("MapPikachuEnergyAnim", false);

		energizeTimer.Start();
		gameAt->GetPokeball()->SetIfBlockMovement(true);
	}
	if (ballIn) {
		map_pikachu_animator->SetSpeed(0.1f);
		gameAt->GetPokeball()->SetVelocity({ 0,0 });
		gameAt->GetPokeball()->SetPosition(gameAt->GetPokeball()->GetPosition());
		if (energizeTimer.ReadSec() > energizeTime) {
			if (map_pikachuEnergy_animator->HasAnimationFinished()) {
				gameAt->GetPokeball()->SetIfBlockMovement(false);
				gameAt->GetPokeball()->SetVelocity({ 0,-100 });
				ballIn = false;
				map_pikachu_animator->SelectAnimation("MapPikachuAnim", true);
				map_pikachuEnergy_animator->SelectAnimation("MapPikachuEnergyIdleAnim", true);
			}
		}
	}

	map_pikachu_animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);
	map_pikachu_animator->Update();

	map_pikachuEnergy_animator->Animate((int)(position.x * SCREEN_SIZE), (int)((position.y - (32/SCREEN_SIZE)) * SCREEN_SIZE), false);
	map_pikachuEnergy_animator->Update();

	return UPDATE_CONTINUE;
}

bool Pikachu::CleanUp()
{
	if (map_pikachu_animator != nullptr) {
		delete map_pikachu_animator;
		map_pikachu_animator = nullptr;
	}
	if (map_pikachuEnergy_animator != nullptr) {
		delete map_pikachuEnergy_animator;
		map_pikachuEnergy_animator = nullptr;
	}

	gameAt->App->physics->world->DestroyBody(body);

	LOG("Unloading cute companion");
	return true;
}
