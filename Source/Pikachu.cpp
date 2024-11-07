#include "Pikachu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

Pikachu::Pikachu(ModuleGame* gameAt, b2Vec2 position, float restitution) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/map_pikachu.png", "map_pikachu");
	map_pikachu = gameAt->App->texture->GetTexture("map_pikachu");

	map_pikachu_animator = new Animator(gameAt->App);

	AnimationData MapPikachuAnim = AnimationData("MapPikachuAnim");
	MapPikachuAnim.AddSprite(Sprite{ map_pikachu,{0, 0}, {16,16} });
	MapPikachuAnim.AddSprite(Sprite{ map_pikachu,{1, 0}, {16,16} });
	MapPikachuAnim.AddSprite(Sprite{ map_pikachu,{2, 0}, {16,16} });

	map_pikachu_animator->AddAnimation(MapPikachuAnim);
	map_pikachu_animator->SetSpeed(0.2f);
	map_pikachu_animator->SelectAnimation("MapPikachuAnim", true);
	map_pikachu_animator->SetDirection(-1);

	bool is_in_left = true;
	position_x = 10;
}

Pikachu::~Pikachu()
{

}

update_status Pikachu::Update()
{
	if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		position_x = 6;//Configure pos x
		is_in_left = true;
	}
	else if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		position_x = 138;//Configure pos x
		is_in_left = false;
	}

	if (is_in_left)
	{
		map_pikachu_animator->Animate(position_x, 245, true);//Configure pos y
	}
	else
	{
		map_pikachu_animator->Animate(position_x, 245, false);//Configure pos y
	}

	map_pikachu_animator->Update();

	return UPDATE_CONTINUE;
}

bool Pikachu::CleanUp()
{
	if (map_pikachu_animator != nullptr) {
		delete map_pikachu_animator;
		map_pikachu_animator = nullptr;
	}

	LOG("Unloading cute companion");
	return true;
}
