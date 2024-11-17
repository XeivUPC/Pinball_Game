#include "MapEnergyBattery.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleAudio.h"
#include <string>

MapEnergyBattery::MapEnergyBattery(ModuleGame* gameAt, b2Vec2 position, int variant) : MapObject(gameAt)
{
	gameAt->AddObject(this);
	this->position = position;

	gameAt->App->texture->CreateTexture("Assets/map_energyBatery.png", "map_energyBatery");
	texture = gameAt->App->texture->GetTexture("map_energyBatery");

	animator = new Animator(gameAt->App);

	AnimationData filling = AnimationData("Filling");
	filling.AddSprite(Sprite{ texture,{0, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{1, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{2, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{3, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{4, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{5, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{6, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{7, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{8, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{9, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{10, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{11, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{12, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{13, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{14, (float)variant}, {17,18} });
	filling.AddSprite(Sprite{ texture,{15, (float)variant}, {17,18} });

	AnimationData filled = AnimationData("Filled");
	filled.AddSprite(Sprite{ texture,{16, (float)variant}, {17,18} });

	AnimationData empty = AnimationData("Empty");
	empty.AddSprite(Sprite{ texture,{0, (float)variant}, {17,18} });

	animator->SetSpeed(0);
	animator->AddAnimation(filling);
	animator->AddAnimation(empty);
	animator->AddAnimation(filled);
	animator->SelectAnimation("Filling", true);

	for (int i =1; i <=15; i++)
	{
		std::string pathName = "Assets/SFX/Map_Energy_" + std::to_string(i) + ".ogg";
		audiosEnergyIds.emplace_back(gameAt->App->audio->LoadFx(pathName.c_str()));
	}

	audioEnergyFullId = gameAt->App->audio->LoadFx("Assets/SFX/Game_EnergyCompleted.ogg");
}

MapEnergyBattery::~MapEnergyBattery()
{
}

update_status MapEnergyBattery::Update()
{
	gameAt->SetEnergyStatus(currentEnergy == totalCapacity);

	if (currentEnergy == totalCapacity) {
		if (animator->GetCurrentAnimationName() != "Filled")
		{
			gameAt->App->audio->PlayFx(audioEnergyFullId);
		}
		animator->SelectAnimation("Filled", true);
	}
	else if(currentEnergy == 0){
		animator->SelectAnimation("Empty", true);
	}
	else {
		animator->SelectAnimation("Filling", true);
	}

	int currentSprite = animator->GetCurrentAnimationSpriteIndex();
	if (previousSprite != currentSprite)
	{
		if(currentSprite!=0 && currentSprite!=15)
			gameAt->App->audio->PlayFx(audiosEnergyIds[currentSprite-1]);
	}
	previousSprite = currentSprite;

	animator->LerpUpdate(currentEnergy / totalCapacity);

	animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), true);

	return UPDATE_CONTINUE;
}

bool MapEnergyBattery::CleanUp()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}

	audiosEnergyIds.clear();
	return false;
}

void MapEnergyBattery::AddEnergy(float amount)
{
	currentEnergy+=amount;
	if (currentEnergy > totalCapacity)
		currentEnergy = totalCapacity;
}

void MapEnergyBattery::SetEnergy(float amount)
{
	currentEnergy = 0;
	AddEnergy(amount);
}

void MapEnergyBattery::Reset()
{
	currentEnergy = 0;
}
