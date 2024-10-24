#include "GameUI.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

GameUI::GameUI(Application* App) : UI(App)
{
}

GameUI::~GameUI()
{
}

void GameUI::Render() const
{
	App->renderer->DrawRect(0, 134, 160, 10, BLACK);
}
