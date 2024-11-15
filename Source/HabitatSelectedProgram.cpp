#include "HabitatSelectedProgram.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "CentralScreen.h"
#include "Application.h"

HabitatSelectedProgram::HabitatSelectedProgram() : ScreenProgram("HabitatSelected")
{

}

HabitatSelectedProgram::~HabitatSelectedProgram()
{

}

void HabitatSelectedProgram::CallAction(int id)
{

}

void HabitatSelectedProgram::StartProgram()
{
	gameAt->App->texture->CreateTexture("Assets/map_habitats.png", "map_habitats");
	texture = gameAt->App->texture->GetTexture("map_habitats");
}

void HabitatSelectedProgram::Logic()
{
	if (timer.ReadSec() > minTimeInScreen)
		canBeOverwritten = true;
}

void HabitatSelectedProgram::Render()
{
	Rectangle rect = { gameAt->GetHabitat() * 48.f,1 * 32.f,48.f,32.f };
	gameAt->App->renderer->Draw(*texture, (int)gameAt->screen->screenArea.x, (int)gameAt->screen->screenArea.y, &rect);
}

void HabitatSelectedProgram::EndProgram()
{
}
