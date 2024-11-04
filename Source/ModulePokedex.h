#pragma once
#include "ModuleScene.h"
#include "raylib.h"
#include "pugixml.hpp"
#include "pokemon.h"
#include <vector>

using namespace pugi;
class ModulePokedex : public ModuleScene
{
private:
	std::vector<Pokemon> pokemon_list;
	int selectedLanguage;
	int localSelection = 0;
	int selectedPokemon = 0;
	int audioSelectId;
	int audioMoveId;
	float factor = 0;
	Timer lerpTimer;
	float lerpTime = 2.f;
	Texture2D* pokedexSpritesheet;
	Texture2D* pokedexSlot;
	xml_document _data;
	float slots_offset = 0;
	int option = 0;

public:
	ModulePokedex(Application* app, bool start_enabled = true);
	~ModulePokedex();
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	void LoadConfigFile();
	void SaveConfigFile();
	void LoadPokedex();
	void SavePokedex();

};