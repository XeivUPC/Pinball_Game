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

std::string ScreenProgram::GetProgramIdentifier()
{
	return identifier;
}

void ScreenProgram::StartProgram()
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
