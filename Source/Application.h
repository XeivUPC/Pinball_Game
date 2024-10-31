#pragma once

#include "Globals.h"
#include "Timer.h"
#include <vector>

class Module;
class ModuleWindow;
class ModuleRender;
class ModuleAudio;
class ModulePhysics;
class ModuleTexture;
class ModuleText;
class ModuleHSNum;
class ModuleHSName;
class ModuleGameUIText;
class ModuleGamePokedexJapanese;
class ModuleGamePokedexWorldWide;

class ModuleUserPreferences;

class ModuleLevelSelection;
class ModuleCredits;
class ModuleMainMenu;
class ModuleLanguageSelect;
class ModuleSettings;
class ModuleKeybinds;
class ModulePokedex;
class ModuleHighScore;
class ModuleGame;


class Application
{
public:

	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleAudio* audio;
	ModulePhysics* physics;
	ModuleUserPreferences* userPreferences;

	ModuleLevelSelection* scene_levelSelection;
	ModuleCredits* scene_credits;
	ModuleMainMenu* scene_mainMenu;
	ModuleLanguageSelect* scene_languageSelect;
	ModuleSettings* scene_settings;
	ModuleKeybinds* scene_keybinds;
	ModuleHighScore* scene_highScore;
	ModulePokedex* scene_pokedex;
	ModuleGame* scene_game;

	ModuleTexture* texture;
	ModuleText* text;
	ModuleHSNum* text_highScoreNum;
	ModuleHSName* text_highScoreName;
	ModuleGameUIText* text_gameUIText;
	ModuleGamePokedexJapanese* text_pokedex_japanese;
	ModuleGamePokedexWorldWide* text_pokedex_worldwide;

private:

	std::vector<Module*> list_modules;
    uint64 frame_count = 0;

	Timer ptimer;
	Timer startup_time;
	Timer frame_time;
	Timer last_sec_frame_time;

	uint32 last_sec_frame_count = 0;
	uint32 prev_last_sec_frame_count = 0;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* module);
};