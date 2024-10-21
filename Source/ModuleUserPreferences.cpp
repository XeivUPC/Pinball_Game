#include "ModuleUserPreferences.h"

ModuleUserPreferences::ModuleUserPreferences(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{

}

ModuleUserPreferences::~ModuleUserPreferences()
{
}

bool ModuleUserPreferences::Init()
{
	LoadUserPreferences();
	return true;
}

bool ModuleUserPreferences::CleanUp()
{
	SaveUserPreferences();
	return true;
}

ModuleUserPreferences::AppLanguage ModuleUserPreferences::GetLanguage()
{
	return language;
}

void ModuleUserPreferences::ChangeLanguage(AppLanguage language)
{
	this->language = language;
}

int ModuleUserPreferences::GetKeyValue(VirtualButton button)
{
	if (keyMap.count(button) == 0)
		return 0;
	return keyMap.at(button);
}

void ModuleUserPreferences::LoadUserPreferences()
{
	keyMap[LEFT] = KEY_A;
	keyMap[RIGHT] = KEY_D;
	keyMap[UP] = KEY_W;
	keyMap[DOWN] = KEY_S;

	keyMap[SELECT] = KEY_ENTER;

	language = English;
}

void ModuleUserPreferences::SaveUserPreferences()
{
}
