#include "BonusStartProgram.h"

#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "CentralScreen.h"
#include "ModuleUserPreferences.h"

BonusStartProgram::BonusStartProgram() : ScreenProgram("BonusStart")
{
}

BonusStartProgram::~BonusStartProgram()
{
}

void BonusStartProgram::CallAction(int id)
{
	int attempt = gameAt->GetBonusSelectionAttempts();
	gameAt->AddBonusSelectionAttempts();
	gameAt->screen->SwitchProgram(new BonusSelectionProgram(attempt));
}

void BonusStartProgram::StartProgram()
{
	int selectedLanguage = gameAt->App->userPreferences->GetLanguage() - 1;
	if (selectedLanguage < 0)
		selectedLanguage = 0;

	section = { 14 * 48.f,((6 * selectedLanguage) + 5) * 32.f,48.f,32.f };

	gameAt->App->texture->CreateTexture("Assets/map_bonusSprites.png", "map_bonusSprites");
	texture = gameAt->App->texture->GetTexture("map_bonusSprites");
}

void BonusStartProgram::Logic()
{
	canBeOverwritten = true;

}

void BonusStartProgram::Render()
{
	gameAt->App->renderer->Draw(*texture, (int)gameAt->screen->screenArea.x, (int)gameAt->screen->screenArea.y, &section);
}

void BonusStartProgram::EndProgram()
{
}
