#include "CentralScreen.h"
#include "ModuleRender.h"
#include "Application.h"

void CentralScreen::ActivateProgram(ScreenProgram* program)
{
	actualProgram = program->Activate();
}

void CentralScreen::DrawOnScreen(Texture2D texture, int x, int y, Rectangle section, Color tint, bool flip, double angle, float pivot_x, float pivot_y)
{
	if (section.width > screenArea.width - x) section.width = screenArea.width - x;
	if (section.height > screenArea.height - y) section.height = screenArea.height - y;
	if (x > screenArea.width || y > screenArea.height)return;
	gameAt->App->renderer->Draw(texture, screenArea.x+x, screenArea.y+y, &section, tint, flip, angle, pivot_x, pivot_y);
}

void CentralScreen::AddProgram(ScreenProgram* program)
{
	ActivateProgram(program);
}

update_status CentralScreen::Update()
{
	actualProgram->Logic();
	actualProgram->Render();
	return UPDATE_CONTINUE;
}

void CentralScreen::RemoveProgram()
{
	actualProgram = nullptr;
}

CentralScreen::CentralScreen(ModuleGame* gameAt) : MapObject(gameAt)
{
	screenArea = Rectangle{ 56, 166, 48, 32};
	actualProgram = nullptr;
}

CentralScreen::~CentralScreen()
{
	actualProgram = nullptr;
}
