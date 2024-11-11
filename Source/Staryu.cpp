#include "Staryu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

Staryu::Staryu(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/map_staryu.png", "map_staryu");
	map_staryu = gameAt->App->texture->GetTexture("map_staryu");

	map_staryu_animator = new Animator(gameAt->App);

	AnimationData mapStaryuAnim = AnimationData("MapStaryuAnim");
	mapStaryuAnim.AddSprite(Sprite{ map_staryu,{0, 0}, {24,24} });
	mapStaryuAnim.AddSprite(Sprite{ map_staryu,{1, 0}, {24,24} });

	map_staryu_animator->AddAnimation(mapStaryuAnim);
	map_staryu_animator->SetSpeed(0.3f);
	map_staryu_animator->SelectAnimation("MapStaryuAnim", true);
}

Staryu::~Staryu()
{
}

update_status Staryu::Update()
{
	map_staryu_animator->Animate(43, 105, false);

	map_staryu_animator->Update();

	return UPDATE_CONTINUE;
}

bool Staryu::CleanUp()
{
	if (map_staryu_animator != nullptr) {
		delete map_staryu_animator;
		map_staryu_animator = nullptr;
	}

	LOG("Unloading Staryu");
	return true;
}
