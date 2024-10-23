#include "HighScoreUIName.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"

HighScoreUIName::HighScoreUIName(Application* App) : UI(App)
{
	this->App = App;
	App->texture->CreateTexture("Assets/high_score_letters.png", "HighScoreUIName");
	UITexture = App->texture->GetTexture("HighScoreUIName");
}

HighScoreUIName::~HighScoreUIName()
{
}

void HighScoreUIName::Update() const
{
	if (!enabled) return;
	App->text->Write("HighScoreUIName", 0, 0);
}
