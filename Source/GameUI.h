#pragma once
#include "UI.h"
#include <string>

class GameUI : public UI
{
public:
	GameUI(Application* App);
	~GameUI();
	void Render()const;

private:
	std::string FormatNumberWithOnlyComas(int number) const;
};

