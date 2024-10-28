#include "HighScoreUINum.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"

HighScoreUINum::HighScoreUINum(Application* App) : UI (App)
{
	this->App = App;
	App->texture->CreateTexture("Assets/Font.png", "UI");
	UITexture = App->texture->GetTexture("UI");
}

HighScoreUINum::~HighScoreUINum()
{
}

void HighScoreUINum::Update() const
{
	if (!enabled) return;
	App->text->Write("HOLA", 0, 0);
}
