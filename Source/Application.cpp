
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleUserPreferences.h"
#include "ModuleText.h"
#include "ModuleHSNum.h"
#include "ModuleHSName.h"
#include "ModuleGameUIText.h"
#include "ModuleTimerUIText.h"
#include "ModuleGamePokedexJapanese.h"
#include "ModuleGamePokedexWorldWide.h"

#include "ModuleLevelSelection.h"
#include "ModuleCredits.h"
#include "ModulePokedex.h"
#include "ModuleMainMenu.h"
#include "ModuleLanguageSelect.h"
#include "ModuleSettings.h"
#include "ModuleKeybinds.h"
#include "ModuleHighScore.h"
#include "ModuleGameRedMap.h"
#include "ModuleGameBlueMap.h"

#include "Application.h"
#include "MemLeaks.h"

Application::Application()
{
	ReportMemoryLeaks();
	window = new ModuleWindow(this);
	renderer = new ModuleRender(this);
	audio = new ModuleAudio(this, true);
	physics = new ModulePhysics(this);
	userPreferences = new ModuleUserPreferences(this);
	text = new ModuleText(this);
	text_highScoreNum = new ModuleHSNum(this);
	text_highScoreName = new ModuleHSName(this);
	text_gameUIText = new ModuleGameUIText(this);
	text_timerUIText = new ModuleTimerUIText(this);
	text_pokedex_japanese = new ModuleGamePokedexJapanese(this);
	text_pokedex_worldwide = new ModuleGamePokedexWorldWide(this);

	scene_languageSelect = new ModuleLanguageSelect(this);
	scene_credits = new ModuleCredits(this, false);
	scene_levelSelection = new ModuleLevelSelection(this,false);
	scene_mainMenu = new ModuleMainMenu(this, false);
	scene_pokedex = new ModulePokedex(this, false);
	scene_settings = new ModuleSettings(this, false);
	scene_keybinds = new ModuleKeybinds(this, false);
	scene_highScore = new ModuleHighScore(this, false);
	scene_game_redMap = new ModuleGameRedMap(this, false);
	scene_game_blueMap = new ModuleGameBlueMap(this, false);

	texture = new ModuleTexture(this);


	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(physics);
	AddModule(audio);
	AddModule(texture);
	AddModule(userPreferences);
	AddModule(text);
	AddModule(text_highScoreNum);
	AddModule(text_highScoreName);
	AddModule(text_pokedex_japanese);
	AddModule(text_pokedex_worldwide);
	AddModule(text_gameUIText);
	AddModule(text_timerUIText);

	// Scenes
	AddModule(scene_languageSelect);
	AddModule(scene_credits);
	AddModule(scene_mainMenu);
	AddModule(scene_levelSelection);
	AddModule(scene_pokedex);
	AddModule(scene_highScore);
	AddModule(scene_settings);
	AddModule(scene_keybinds);
	AddModule(scene_game_redMap);
	AddModule(scene_game_blueMap);

	// Rendering happens at the end
	AddModule(renderer);
}

Application::~Application()
{
	for (auto it = list_modules.rbegin(); it != list_modules.rend(); ++it)
	{
		Module* item = *it;
		delete item;
	}
	list_modules.clear();
	
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (auto it = list_modules.begin(); it != list_modules.end() && ret; ++it)
	{
		Module* module = *it;
		ret = module->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	for (auto it = list_modules.begin(); it != list_modules.end() && ret; ++it)
	{
		Module* module = *it;
		if(module->IsEnabled())
			ret = module->Start();
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (auto it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		Module* module = *it;
		if (module->IsEnabled())
		{
			ret = module->PreUpdate();
		}
	}

	for (auto it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		Module* module = *it;
		if (module->IsEnabled())
		{
			ret = module->Update();
		}
	}

	for (auto it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		Module* module = *it;
		if (module->IsEnabled())
		{
			ret = module->PostUpdate();
		}
	}

	if (IsKeyPressed(KEY_F4))
	{
		if (current_fps == 60) {
			ChangeTargetFPS(30);
			current_fps = 30;
		}
		else if(current_fps == 30){
			ChangeTargetFPS(60);
			current_fps = 60;
		}
	}

	if (WindowShouldClose()) ret = UPDATE_STOP;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (auto it = list_modules.rbegin(); it != list_modules.rend() && ret; ++it)
	{
		Module* item = *it;
		ret = item->CleanUp();
	}
	
	return ret;
}

void Application::ChangeTargetFPS(int fps)
{
	SetTargetFPS(fps);
}

void Application::AddModule(Module* mod)
{
	list_modules.emplace_back(mod);
}