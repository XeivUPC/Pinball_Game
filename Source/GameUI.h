#pragma once
#include "UI.h"
#include <string>
#include "ModuleGame.h"

class GameUI : public UI
{
public:
	GameUI(ModuleGame* gameAt);
	~GameUI();
	void Render();
	update_status Update();

	void AddText(std::string text);
	void ShowNextText();
	void ShowBasicUI();

private:
	ModuleGame* gameAt;
	std::string FormatNumberWithOnlyComas(long long int number) const;

	PokeBall* pokeball;

	std::vector<std::string> textQueue;
	bool showingText = false;

	bool paused = false;
	Timer textPauseTimer;
	int textPauseTime = 2;


	float textInitPos = 160;
	float textCurrentPos = 0;
};

