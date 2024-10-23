#include "HighScoreUIName.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"

HighScoreUIName::HighScoreUIName(Application* App) : UI(App)
{
	this->App = App;
	App->texture->CreateTexture("Assets/Font.png", "UI");
	UITexture = App->texture->GetTexture("UI");
}

HighScoreUIName::~HighScoreUIName()
{
}

void HighScoreUIName::Update() const
{
	if (!enabled) return;
	App->text->Write("HOLA", 0, 0);
}
