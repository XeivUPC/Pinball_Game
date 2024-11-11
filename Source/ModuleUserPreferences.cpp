#include "ModuleUserPreferences.h"


ModuleUserPreferences::ModuleUserPreferences(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleUserPreferences::~ModuleUserPreferences()
{
}

bool ModuleUserPreferences::Init()
{
	LoadConfigFile();
	LoadUserPreferences();
	return true;
}

bool ModuleUserPreferences::CleanUp()
{	
	SaveUserPreferences();
	preferencesFile.reset();
	return true;
}

ModuleUserPreferences::Vibration ModuleUserPreferences::GetVibration()
{
	return vibration;
}

ModuleUserPreferences::AppLanguage ModuleUserPreferences::GetLanguage()
{
	return language;
}

int ModuleUserPreferences::GetMusicVolume()
{
	return musicVolume;
}

int ModuleUserPreferences::GetSfxVolume()
{
	return sfxVolume;
}

void ModuleUserPreferences::ChangeLanguage(AppLanguage language)
{
	this->language = language;
	
	SaveUserPreferences();
}

ModuleUserPreferences::AppLanguage ModuleUserPreferences::NextLanguage()
{
	int maxLimit = (int)NONE;
	int minLimit = 0;

	int current = (int)language;
	current++;
	if (current >= maxLimit)
		current = minLimit;
	if (current < minLimit)
		current = maxLimit-1;

	ChangeLanguage((AppLanguage)current);

	return language;
}

ModuleUserPreferences::AppLanguage ModuleUserPreferences::PreviousLanguage()
{
	int maxLimit = (int)NONE;
	int minLimit = 0;

	int current = (int)language;
	current--;
	if (current >= maxLimit)
		current = minLimit;
	if (current < minLimit)
		current = maxLimit - 1;

	ChangeLanguage((AppLanguage)current);

	return language;
}

void ModuleUserPreferences::ChangeVibration(Vibration vibration)
{
	this->vibration = vibration;

	SaveUserPreferences();
}

ModuleUserPreferences::Vibration ModuleUserPreferences::NextVibration()
{
	int maxLimit = (int)(Off)+1;
	int minLimit = 0;

	int current = (int)vibration;
	current++;
	if (current >= maxLimit)
		current = minLimit;
	if (current < minLimit)
		current = maxLimit - 1;

	ChangeVibration((Vibration)current);

	return vibration;
}

ModuleUserPreferences::Vibration ModuleUserPreferences::PreviousVibration()
{
	int maxLimit = (int)Off +1;
	int minLimit = 0;

	int current = (int)vibration;
	current--;
	if (current >= maxLimit)
		current = minLimit;
	if (current < minLimit)
		current = maxLimit - 1;

	ChangeVibration((Vibration)current);

	return vibration;
}

int ModuleUserPreferences::GetKeyValue(VirtualButton button)
{
	if (keyBinds.count(button) == 0)
		return 0;
	return keyBinds.at(button);
}

void ModuleUserPreferences::LoadUserPreferences()
{
	xml_node keybindsNode = preferencesFile.child("config").child("keyBinds");

	keyBinds[LEFT] = keybindsNode.child("left").attribute("value").as_int();
	keyBinds[RIGHT] = keybindsNode.child("right").attribute("value").as_int();
	keyBinds[UP] = keybindsNode.child("up").attribute("value").as_int();
	keyBinds[DOWN] = keybindsNode.child("down").attribute("value").as_int();

	keyBinds[SELECT] = keybindsNode.child("select").attribute("value").as_int();
	keyBinds[RETURN] = keybindsNode.child("return").attribute("value").as_int();

	language = (AppLanguage)preferencesFile.child("config").child("language").attribute("value").as_int();
	vibration = (Vibration)preferencesFile.child("config").child("vibration").attribute("value").as_int();
}

void ModuleUserPreferences::SaveUserPreferences()
{
	xml_node keybindsNode = preferencesFile.child("config").child("keyBinds");

	keybindsNode.child("left").attribute("value").set_value(keyBinds[LEFT]);
	keybindsNode.child("right").attribute("value").set_value(keyBinds[RIGHT]);
	keybindsNode.child("up").attribute("value").set_value(keyBinds[UP]);
	keybindsNode.child("down").attribute("value").set_value(keyBinds[DOWN]);

	keybindsNode.child("select").attribute("value").set_value(keyBinds[SELECT]);
	keybindsNode.child("return").attribute("value").set_value(keyBinds[RETURN]);

	int languageIndex = (int)language;
	preferencesFile.child("config").child("language").attribute("value").set_value(languageIndex);

	int vibrationIndex = (int)vibration;
	preferencesFile.child("config").child("vibration").attribute("value").set_value(vibrationIndex);

	SaveConfigFile();

}

void ModuleUserPreferences::LoadConfigFile()
{
	pugi::xml_parse_result result = preferencesFile.load_file("Assets/Preferences/UserPreferences.xml");
	if (result)
	{
		LOG("config.xml parsed without errors");
	}
	else
	{
		LOG("Error loading config.xml: %s", result.description());
	}

}

void ModuleUserPreferences::SaveConfigFile()
{
	preferencesFile.save_file("Assets/Preferences/UserPreferences.xml");
}
