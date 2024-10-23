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
		Italian,

		NONE
	};

	enum Vibration
	{
		Strong,
		Mild,
		Off
	};
	
	ModuleUserPreferences(Application* app, bool start_enabled=true);
	~ModuleUserPreferences();

	bool Init();
	bool CleanUp();

	Vibration GetVibration();
	AppLanguage GetLanguage();
	int GetMusicVolume();
	int GetSfxVolume();

	void ChangeLanguage(AppLanguage language);
	AppLanguage NextLanguage();
	AppLanguage PreviousLanguage();

	void ChangeVibration(Vibration vibration);
	Vibration NextVibration();
	Vibration PreviousVibration();

	int GetKeyValue(VirtualButton button);
private:


	void LoadUserPreferences();
	void SaveUserPreferences();

	void LoadConfigFile();
	void SaveConfigFile();
	xml_document preferencesFile;

	int musicVolume=100;
	int sfxVolume=100;

	AppLanguage language;
	Vibration vibration;
	std::unordered_map<VirtualButton, int> keyBinds;
};

