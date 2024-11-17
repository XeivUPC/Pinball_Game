#include "HabitatSelectionProgram.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "CentralScreen.h"
#include "ModuleUserPreferences.h"
#include "HabitatSelectedProgram.h"

HabitatSelectionProgram::HabitatSelectionProgram(std::vector<int> habitatsToSelect) : ScreenProgram("HabitatSelection")
{
	this->habitatsToSelect = habitatsToSelect;
	
}

HabitatSelectionProgram::~HabitatSelectionProgram()
{

}

void HabitatSelectionProgram::CallAction(int id)
{
	canBeOverwritten = true;
	int selectedHabitatIndex = animator->GetCurrentAnimationSprite().extraData;
	gameAt->ChangeToHabitat(selectedHabitatIndex);
	gameAt->screen->SwitchProgram(new HabitatSelectedProgram());
}

void HabitatSelectionProgram::StartProgram()
{
	gameAt->App->texture->CreateTexture("Assets/map_habitats.png", "map_habitats");
	texture = gameAt->App->texture->GetTexture("map_habitats");

	animator = new Animator(gameAt->App);

	AnimationData selectAnimationBW = AnimationData("Select_Animation_BW");
	for (size_t i = 0; i < habitatsToSelect.size(); i++)
	{
		int xIndex = habitatsToSelect[i];
		selectAnimationBW.AddSprite(Sprite{ texture,{(float)xIndex, 0}, {48,32} },xIndex);
	}

	animator->AddAnimation(selectAnimationBW);
	animator->SetSpeed(0.1f);
	animator->SelectAnimation("Select_Animation_BW", true);

	audioHabitatSelectionId = gameAt->App->audio->LoadFx("Assets/SFX/Game_MapChanging.ogg");
	audioHabitatFoundId = gameAt->App->audio->LoadFx("Assets/SFX/Game_MapFound.ogg");
}

void HabitatSelectionProgram::Logic()
{
	animator->Update();

	int currentSprite = animator->GetCurrentAnimationSpriteIndex();
	if (previousSprite != currentSprite)
	{
		gameAt->App->audio->PlayFx(audioHabitatSelectionId);
	}
	previousSprite = currentSprite;


	if (IsKeyPressed(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
		CallAction(0);
	}	

}

void HabitatSelectionProgram::Render()
{
	animator->Animate((int)gameAt->screen->screenArea.x, (int)gameAt->screen->screenArea.y, false);
}

void HabitatSelectionProgram::EndProgram()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}

	habitatsToSelect.clear();
}
