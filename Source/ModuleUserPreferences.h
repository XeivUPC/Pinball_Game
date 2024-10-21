#pragma once
#include "ModuleGame.h"
#include <unordered_map>

class ModuleUserPreferences : public ModuleGame
{
public:
	

	enum VirtualButton
	{
		SELECT,
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	enum AppLanguage
	{
		Japanese,
		English,
		French,
		German,
		Spanish,
		Italian
	};
	
	ModuleUserPreferences(Application* app, bool start_enabled=true);
	~ModuleUserPreferences();

	bool Init();
	bool CleanUp();

	AppLanguage GetLanguage();
	void ChangeLanguage(AppLanguage language);
	int GetKeyValue(VirtualButton button);
private:

	void LoadUserPreferences();
	void SaveUserPreferences();

	AppLanguage language;
	std::unordered_map<VirtualButton, int> keyMap;
};

