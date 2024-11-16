#include "ModuleGame.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleMainMenu.h"
#include "MapObject.h"
#include "MapEnergyBattery.h"
#include <sstream>


ModuleGame::ModuleGame(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

ModuleGame::~ModuleGame()
{
}

bool ModuleGame::Start()
{
	pointsCounter.Set(100);
	return true;
}

update_status ModuleGame::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleGame::CleanUp()
{
	habitatIndex = -1;

	saveBall = true;

	isEnergyCharged = false;
	isEnergyUsed = false;
	isBallInTopSection = false;

	canCapture = false;
	canEvolve = false;

	bonusSelectionAttempts = 1;
	return true;
}

PokeBall* ModuleGame::GetPokeball()
{
	return pokeBall;
}

GameUI* ModuleGame::GetUI()
{
	return UI;
}

void ModuleGame::NextHabitat()
{
	habitatIndex++;
	if (habitatIndex >= (int)mapHabitats.size())
		habitatIndex = 0;
}

void ModuleGame::PreviousHabitat()
{
	habitatIndex--;
	if (habitatIndex < 0)
		habitatIndex = mapHabitats.size()-1;
}

bool ModuleGame::ChangeToHabitat(int habitat)
{
	int index = 0;
	bool found=false;
	for (const auto& habitatType : mapHabitats) {
		if (habitat == habitatType) {
			found = true;
			break;
		}
		index++;
	}
	if (found)
		habitatIndex = index;

	return found;
}

int ModuleGame::GetHabitat()
{
	return mapHabitats[habitatIndex];
}

bool ModuleGame::IsEnergyCharged()
{
	return isEnergyCharged;
}

void ModuleGame::SetEnergyStatus(bool isCharged)
{
	isEnergyCharged = isCharged;
}

void ModuleGame::UseEnergy()
{
	energyBattery->Reset();
}

bool ModuleGame::CanEvolve()
{
	return canEvolve;
}

bool ModuleGame::CanCapture()
{
	return canCapture;
}

int ModuleGame::GetBonusSelectionAttempts()
{
	return bonusSelectionAttempts;
}

void ModuleGame::AddBonusSelectionAttempts()
{
	bonusSelectionAttempts++;
	if (bonusSelectionAttempts > 5)
		bonusSelectionAttempts = 1;
}

bool ModuleGame::IsBallInTopSection()
{
	return isBallInTopSection;
}

void ModuleGame::SetState(GameStates stateToChange)
{
	state = stateToChange;

}

ModuleGame::GameStates ModuleGame::GetState()
{
	return state;
}

void ModuleGame::AddObject(MapObject* object)
{
	mapObjects.emplace_back(object);
}

void ModuleGame::FromStringToVertices(std::string stringData, std::vector<b2Vec2>& vector)
{
	std::stringstream ss(stringData);
	std::string vectorValue;

	vector.clear();

	while (std::getline(ss, vectorValue, ' ')) {
		std::stringstream ss_vectorValue(vectorValue);

		std::string x_str, y_str;

		std::getline(ss_vectorValue, x_str, ',');
		std::getline(ss_vectorValue, y_str);

		float x_poly = std::stof(x_str);
		float y_poly = std::stof(y_str);


		vector.push_back(b2Vec2(x_poly / SCREEN_SIZE, y_poly / SCREEN_SIZE));
	}
}

void ModuleGame::RepositionCamera(b2Vec2 positionToTrack)
{
	if (positionToTrack.x > 160 / SCREEN_SIZE) {
		App->renderer->camera.offset.x = -31 * SCREEN_SIZE;
	}
	else {
		App->renderer->camera.offset.x = 0;
	}

	if (positionToTrack.y > 134 / SCREEN_SIZE) {
		App->renderer->camera.offset.y = -134 * SCREEN_SIZE;
		isBallInTopSection = false;
	}
	else {
		App->renderer->camera.offset.y = 0;
		isBallInTopSection = true;
	}
}
