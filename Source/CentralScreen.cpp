#include "CentralScreen.h"
#include "ModuleRender.h"
#include "Application.h"

void CentralScreen::AddProgram(ScreenProgram* program)
{
	actualProgram = program;
	actualProgram->SetGameReference(gameAt);
	actualProgram->StartProgram();
}

void CentralScreen::SetDefaultProgram(ScreenProgram* program)
{
	if (defaultProgram != nullptr) {
		defaultProgram->EndProgram();
		delete defaultProgram;
		defaultProgram = nullptr;
	}
	defaultProgram = program;
	defaultProgram->SetGameReference(gameAt);
	defaultProgram->StartProgram();
}

void CentralScreen::SwitchProgram(ScreenProgram* program)
{
	if (actualProgram == nullptr) {
		AddProgram(program);
		return;
	}
	RemoveProgram();
	AddProgram(program);
}

void CentralScreen::CallScreenEvent(int index)
{
	actualProgram->CallAction(index);
}

bool CentralScreen::HasProgram()
{
	return actualProgram != nullptr;
}

bool CentralScreen::CanProgramBeOverwritten()
{
	if (actualProgram == nullptr)
		return true;
	return actualProgram->CanBeOverwritten();
}

Rectangle CentralScreen::GetScreenArea()
{
	return screenArea;
}

update_status CentralScreen::Update()
{
	if (actualProgram == nullptr) {
		if (defaultProgram == nullptr)
			return UPDATE_CONTINUE;
		else
			defaultProgram->Logic();
	}
	else {
		actualProgram->Logic();	
	}

	if (actualProgram == nullptr) {
		if (defaultProgram == nullptr)
			return UPDATE_CONTINUE;
		else
			defaultProgram->Render();
	}
	else {
		actualProgram->Render();
	}
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


std::string CentralScreen::GetActualProgramIdentifier()
{
	if (actualProgram == nullptr)return "";
	return actualProgram->GetProgramIdentifier();
}

std::string CentralScreen::GetDefaultProgramIdentifier()
{
	if (defaultProgram == nullptr)return "";
	return defaultProgram->GetProgramIdentifier();
}

bool CentralScreen::CleanUp()
{
	if (actualProgram != nullptr) 
	{
		actualProgram->EndProgram();
		delete actualProgram;
		actualProgram = nullptr;
	}

	if (defaultProgram != nullptr) {
		defaultProgram->EndProgram();
		delete defaultProgram;
		defaultProgram = nullptr;
	}

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
