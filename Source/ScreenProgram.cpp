#include "ScreenProgram.h"

ScreenProgram::ScreenProgram(const std::string id)
{
	identifier = id;
}

ScreenProgram::~ScreenProgram()
{
}

void ScreenProgram::SetGameReference(ModuleGame* game)
{
	gameAt = game;
}

bool ScreenProgram::CanBeOverwritten()
{
	return canBeOverwritten;
}

std::string ScreenProgram::GetProgramIdentifier()
{
	return identifier;
}

void ScreenProgram::StartProgram()
{
}

void ScreenProgram::CallAction(int id)
{
}

void ScreenProgram::Logic()
{
}

void ScreenProgram::Render()
{
}

void ScreenProgram::EndProgram()
{
	gameAt = nullptr;
}
