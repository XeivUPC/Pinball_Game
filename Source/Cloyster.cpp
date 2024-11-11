#include "Cloyster.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

Cloyster::Cloyster(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/map_cloyster.png", "map_cloyster");
	map_cloyster = gameAt->App->texture->GetTexture("map_cloyster");

	map_cloyster_animator = new Animator(gameAt->App);

	AnimationData mapCloysterAnim = AnimationData("MapCloysterAnim");
	mapCloysterAnim.AddSprite(Sprite{ map_cloyster,{0, 0}, {24,32} });
	mapCloysterAnim.AddSprite(Sprite{ map_cloyster,{1, 0}, {24,32} });
	mapCloysterAnim.AddSprite(Sprite{ map_cloyster,{2, 0}, {24,32} });

	map_cloyster_animator->AddAnimation(mapCloysterAnim);
	map_cloyster_animator->SetSpeed(0.3f);
	map_cloyster_animator->SelectAnimation("MapCloysterAnim", true);
}

Cloyster::~Cloyster()
{
}

update_status Cloyster::Update()
{
	
	map_cloyster_animator->Animate(110, 90, false);

	map_cloyster_animator->Update();

	return UPDATE_CONTINUE;
}

bool Cloyster::CleanUp()
{
	if (map_cloyster_animator != nullptr) {
		delete map_cloyster_animator;
		map_cloyster_animator = nullptr;
	}

	LOG("Unloading Cloyster");
	return true;
}
