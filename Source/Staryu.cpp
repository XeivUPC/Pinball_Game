#include "Staryu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleGameRedMap.h"
#include "ModuleUserPreferences.h"

Staryu::Staryu(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/map_staryu.png", "map_staryu");
	map_staryu = gameAt->App->texture->GetTexture("map_staryu");

	map_staryu_animator = new Animator(gameAt->App);

	AnimationData mapStaryuActiveAnim = AnimationData("MapStaryuActiveAnim");
	mapStaryuActiveAnim.AddSprite(Sprite{ map_staryu,{0, 0}, {24,24} });
	mapStaryuActiveAnim.AddSprite(Sprite{ map_staryu,{1, 0}, {24,24} });

	AnimationData mapStaryuInactiveAnim = AnimationData("MapStaryuInactiveAnim");
	mapStaryuInactiveAnim.AddSprite(Sprite{ map_staryu,{0, 1}, {24,24} });
	mapStaryuInactiveAnim.AddSprite(Sprite{ map_staryu,{1, 1}, {24,24} });

	map_staryu_animator->AddAnimation(mapStaryuActiveAnim);
	map_staryu_animator->AddAnimation(mapStaryuInactiveAnim);
	map_staryu_animator->SetSpeed(0.3f);
	map_staryu_animator->SelectAnimation("MapStaryuActiveAnim", true);
}

Staryu::~Staryu()
{
	 
}

update_status Staryu::Update()
{
	ModuleGameRedMap* redMap = static_cast<ModuleGameRedMap*>(gameAt);
	if (redMap != nullptr) {
		if (redMap->IsTopSideCovered()) {
			map_staryu_animator->SelectAnimation("MapStaryuActiveAnim", true);
		}
		else {
			map_staryu_animator->SelectAnimation("MapStaryuInactiveAnim", true);
		}
	}
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
