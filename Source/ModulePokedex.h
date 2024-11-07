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
	int audioSelectId;
	int audioMoveId;

	int localSelection = 0;
	Vector2 selectedPokemon = { 0,0 };
	int direction = 0;
	double factor = 0;
	Vector2 slots_offset = { 0,0 };

	Timer lerpTimer;
	double lerpTime = 0.5f;

	Texture2D* pokedexSpritesheet;
	Texture2D* pokedexPokemon;
	Texture2D* pokedexSlot;

	xml_document _data;

	const std::string TextFormat(int number);
	void RenderPokemonInfo(int id);
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