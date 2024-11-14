#include "CentralScreen.h"
#include "ModuleRender.h"
#include "Application.h"

void CentralScreen::AddProgram(ScreenProgram* program)
{
	actualProgram = program;
	actualProgram->SetGameReference(gameAt);
	actualProgram->StartProgram();
}

void CentralScreen::CallScreenEvent(int index)
{
	actualProgram->CallAction(index);
}

Rectangle CentralScreen::GetScreenArea()
{
	return screenArea;
}

update_status CentralScreen::Update()
{
	if (actualProgram == nullptr)return UPDATE_CONTINUE;
	actualProgram->Logic();
	if (actualProgram == nullptr)return UPDATE_CONTINUE;
	actualProgram->Render();
	return UPDATE_CONTINUE;
}

void CentralScreen::RemoveProgram()
{
	actualProgram->EndProgram();
	actualProgram = nullptr;
}

void CentralScreen::QuitProgram()
{
	actualProgram = nullptr;
}

std::string CentralScreen::GetActualProgramIdentifier()
{
	if (actualProgram == nullptr)return "";
	return actualProgram->GetProgramIdentifier();
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
