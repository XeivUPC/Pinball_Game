#pragma once
#include "UI.h"

class GameUI : public UI
{
public:
	GameUI(Application* App);
	~GameUI();
	void Render()const;
};

