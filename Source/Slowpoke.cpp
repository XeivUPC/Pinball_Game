#include "Slowpoke.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

Slowpoke::Slowpoke(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/map_slowpoke.png", "map_slowpoke");
	map_slowpoke = gameAt->App->texture->GetTexture("map_slowpoke");

	map_slowpoke_animator = new Animator(gameAt->App);

	AnimationData mapSlowpokeAnim = AnimationData("MapSlowpokeAnim");
	mapSlowpokeAnim.AddSprite(Sprite{ map_slowpoke,{0, 0}, {32,32} });
	mapSlowpokeAnim.AddSprite(Sprite{ map_slowpoke,{1, 0}, {32,32} });
	mapSlowpokeAnim.AddSprite(Sprite{ map_slowpoke,{2, 0}, {32,32} });

	map_slowpoke_animator->AddAnimation(mapSlowpokeAnim);
	map_slowpoke_animator->SetSpeed(0.3f);
	map_slowpoke_animator->SelectAnimation("MapSlowpokeAnim", true);
}

Slowpoke::~Slowpoke()
{
}

update_status Slowpoke::Update()
{
	
	map_slowpoke_animator->Animate(16, 95, false);
	
	map_slowpoke_animator->Update();

	return UPDATE_CONTINUE;
}

bool Slowpoke::CleanUp()
{
	if (map_slowpoke_animator != nullptr) {
		delete map_slowpoke_animator;
		map_slowpoke_animator = nullptr;
	}

	LOG("Unloading Slowpoke");
	return true;
}
