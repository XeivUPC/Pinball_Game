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

private:
	ModuleGame* gameAt;
	std::string FormatNumberWithOnlyComas(long long int number) const;
};

