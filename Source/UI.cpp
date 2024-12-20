#include "UI.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

UI::UI(Application* App)
{
	this->App = App;
	App->texture->CreateTexture("Assets/Font.png", "UI");
	UITexture = App->texture->GetTexture("UI");
}

UI::~UI()
{
}

void UI::ChangeVisibility()
{
	enabled = !enabled;
}

void UI::Render() const
{
	if (!enabled) return;
}
