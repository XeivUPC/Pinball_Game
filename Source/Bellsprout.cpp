#include "Bellsprout.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

Bellsprout::Bellsprout(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/map_bellsprout.png", "map_bellsprout");
	map_bellsprout = gameAt->App->texture->GetTexture("map_bellsprout");

	map_bellsprout_animator = new Animator(gameAt->App);

	AnimationData mapBellsproutAnim = AnimationData("MapBellsproutAnim");
	mapBellsproutAnim.AddSprite(Sprite{ map_bellsprout,{0, 0}, {32,40} });
	mapBellsproutAnim.AddSprite(Sprite{ map_bellsprout,{1, 0}, {32,40} });
	//mapBellsproutAnim.AddSprite(Sprite{ map_bellsprout,{2, 0}, {32,40} });
	//mapBellsproutAnim.AddSprite(Sprite{ map_bellsprout,{3, 0}, {32,40} });

	map_bellsprout_animator->AddAnimation(mapBellsproutAnim);
	map_bellsprout_animator->SetSpeed(1.f);
	map_bellsprout_animator->SelectAnimation("MapBellsproutAnim", true);

	this->position = position;
}

Bellsprout::~Bellsprout()
{
}

update_status Bellsprout::Update()
{

	map_bellsprout_animator->Animate(104, 78, false);

	map_bellsprout_animator->Update();
	
	return UPDATE_CONTINUE;
}

bool Bellsprout::CleanUp()
{
	if (map_bellsprout_animator != nullptr) {
		delete map_bellsprout_animator;
		map_bellsprout_animator = nullptr;
	}

	LOG("Unloading Bellsprout");
	return true;
}
