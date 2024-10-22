#pragma once
#include "Module.h"
#include <unordered_map>
#include "pugixml.hpp"

using namespace pugi;

class ModuleUserPreferences : public Module
{
public:
	

	enum VirtualButton
	{
		SELECT,
		RETURN,
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
	int GetMusicVolume();
	int GetSfxVolume();
	void ChangeLanguage(AppLanguage language);
	int GetKeyValue(VirtualButton button);
private:


	void LoadUserPreferences();
	void SaveUserPreferences();

	void LoadConfigFile();
	xml_document preferencesFile;

	int musicVolume=100;
	int sfxVolume=100;

	AppLanguage language;
	std::unordered_map<VirtualButton, int> keyBinds;
};

