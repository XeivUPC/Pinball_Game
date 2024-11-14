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

bool CentralScreen::HasProgram()
{
	return actualProgram != nullptr;
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
	if (actualProgram == nullptr)
		return;
	actualProgram->EndProgram();
	delete actualProgram;
	actualProgram = nullptr;
}

void CentralScreen::QuitProgram()
{
	if (actualProgram == nullptr)
		return;
	delete actualProgram;
	actualProgram = nullptr;
}

std::string CentralScreen::GetActualProgramIdentifier()
{
	if (actualProgram == nullptr)return "";
	return actualProgram->GetProgramIdentifier();
}

bool CentralScreen::CleanUp()
{
	if (actualProgram == nullptr)
		return true;
	delete actualProgram;
	actualProgram = nullptr;
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
	
}
