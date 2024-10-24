
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleUserPreferences.h"
#include "ModuleText.h"


#include "ModuleLevelSelection.h"
#include "ModuleCredits.h"
#include "ModuleMainMenu.h"
#include "ModuleLanguageSelect.h"
#include "ModuleSettings.h"
#include "ModuleKeybinds.h"
#include "ModuleHighScore.h"
#include "ModuleGame.h"


#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	renderer = new ModuleRender(this);
	audio = new ModuleAudio(this, true);
	physics = new ModulePhysics(this);
	userPreferences = new ModuleUserPreferences(this);
	text = new ModuleText(this);

	scene_languageSelect = new ModuleLanguageSelect(this);
	scene_credits = new ModuleCredits(this, false);
	scene_levelSelection = new ModuleLevelSelection(this, false);
	scene_mainMenu = new ModuleMainMenu(this, false);
	scene_settings = new ModuleSettings(this, false);
	scene_keybinds = new ModuleKeybinds(this, false);
	scene_highScore = new ModuleHighScore(this, false);
	scene_game = new ModuleGame(this, false);

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

	// Scenes
	AddModule(scene_languageSelect);
	AddModule(scene_credits);
	AddModule(scene_mainMenu);
	AddModule(scene_levelSelection);
	AddModule(scene_highScore);
	AddModule(scene_settings);
	AddModule(scene_keybinds);
	AddModule(scene_game);

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

void Application::AddModule(Module* mod)
{
	list_modules.emplace_back(mod);
}