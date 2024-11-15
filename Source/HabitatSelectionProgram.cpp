#include "HabitatSelectionProgram.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "CentralScreen.h"
#include "ModuleUserPreferences.h"

HabitatSelectionProgram::HabitatSelectionProgram(std::vector<int> habitatsToSelect) : ScreenProgram("HabitatSelection")
{
	this->habitatsToSelect = habitatsToSelect;
}

HabitatSelectionProgram::~HabitatSelectionProgram()
{
}

void HabitatSelectionProgram::SetID(int id)
{

}

void HabitatSelectionProgram::CallAction(int id)
{
	if (alreadySelected)
		return;
	selectedHabitatIndex = animator->GetCurrentAnimationSprite().extraData;
	alreadySelected = true;
	gameAt->ChangeToHabitat(selectedHabitatIndex);
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

}

void HabitatSelectionProgram::Logic()
{
	animator->Update();
	
	if (IsKeyPressed(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		CallAction(0);
	}
}

void HabitatSelectionProgram::Render()
{
	if (!alreadySelected) {
		animator->Animate(gameAt->screen->screenArea.x, gameAt->screen->screenArea.y, false);
	}
	else {
		Rectangle rect = { selectedHabitatIndex*48,1*32,48,32 };
		gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x, gameAt->screen->screenArea.y, &rect);
	}
}

void HabitatSelectionProgram::EndProgram()
{
}
