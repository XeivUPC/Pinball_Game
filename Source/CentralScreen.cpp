#include "CentralScreen.h"
#include "ModuleRender.h"
#include "Application.h"

void CentralScreen::AddProgram(ScreenProgram* program)
{
	actualProgram = program;
	actualProgram->StartProgram();
	actualProgram->SetGameReference(gameAt);
}

Rectangle CentralScreen::GetScreenArea()
{
	return screenArea;
}

update_status CentralScreen::Update()
{
	actualProgram->Logic();
	actualProgram->Render();
	return UPDATE_CONTINUE;
}

void CentralScreen::RemoveProgram()
{
	actualProgram->EndProgram();
	actualProgram = nullptr;
}

bool CentralScreen::CleanUp()
{
	return true;
}

CentralScreen::CentralScreen(ModuleGame* gameAt) : MapObject(gameAt)
{
	gameAt->AddObject(this);
	screenArea = Rectangle{ 56, 166, 48, 32};
	actualProgram = nullptr;
}

CentralScreen::~CentralScreen()
{
	actualProgram = nullptr;
}
