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
	actualProgram->Render();
	return UPDATE_CONTINUE;
}

void CentralScreen::RemoveProgram()
{
	actualProgram->EndProgram();
	actualProgram = nullptr;
}

std::string CentralScreen::GetActualProgramIdentifier()
{
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
	AddProgram(new CapturePokemon);
}

CentralScreen::~CentralScreen()
{
	actualProgram = nullptr;
}
