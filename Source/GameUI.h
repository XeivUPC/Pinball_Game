#pragma once
#include "UI.h"
#include <string>
#include "ModuleGame.h"

class GameUI : public UI
{
public:
	GameUI(ModuleGame* gameAt);
	~GameUI();
	void Render()const;
	update_status Update();

private:
	ModuleGame* gameAt;
	std::string FormatNumberWithOnlyComas(long long int number) const;

	std::string lives_and_pikachus;

	PokeBall* pokeball;
};

