#include "Pikachu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

Pikachu::Pikachu(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/map_pikachu.png", "map_pikachu");
	map_pikachu = gameAt->App->texture->GetTexture("map_pikachu");

	map_pikachu_animator = new Animator(gameAt->App);

	AnimationData mapPikachuAnim = AnimationData("MapPikachuAnim");
	mapPikachuAnim.AddSprite(Sprite{ map_pikachu,{0, 0}, {16,16} });
	mapPikachuAnim.AddSprite(Sprite{ map_pikachu,{1, 0}, {16,16} });

	map_pikachu_animator->AddAnimation(mapPikachuAnim);
	map_pikachu_animator->SetSpeed(0.3f);
	map_pikachu_animator->SelectAnimation("MapPikachuAnim", true);


	gameAt->App->texture->CreateTexture("Assets/map_pikachuEnergy.png", "map_pikachuEnergy");
	map_pikachuEnergy = gameAt->App->texture->GetTexture("map_pikachuEnergy");

	map_pikachuEnergy_animator = new Animator(gameAt->App);

	AnimationData mapPikachuEnergyAnim = AnimationData("MapPikachuEnergyAnim");
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{0, 0}, {16,16} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{1, 0}, {16,16} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{2, 0}, {16,16} });
	mapPikachuEnergyAnim.AddSprite(Sprite{ map_pikachuEnergy,{3, 0}, {16,16} });

	bool is_in_left = true;
	position_x = 139;
}

Pikachu::~Pikachu()
{

}

update_status Pikachu::Update()
{
	if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		position_x = 8;//Configure pos x
		is_in_left = true;
	}
	else if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		position_x = 139;//Configure pos x
		is_in_left = false;
	}

	if (is_in_left)
	{
		map_pikachu_animator->Animate(position_x, 244, false);
	}
	else
	{
		map_pikachu_animator->Animate(position_x, 244, false);
	}

	map_pikachu_animator->Update();

	if (gameAt->IsEnergyCharged())
	{

	}

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

	LOG("Unloading cute companion");
	return true;
}
