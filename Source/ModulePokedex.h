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

	Texture2D* pokedexSpritesheet;
	Texture2D* pokedexPokemon;
	Texture2D* pokedexSlot;

	xml_document _data;






	///////////// 
	int minId = 0;
	int maxId = 150;


	int minLocalId = 0;
	int maxLocalId = 4;

	int selectedId=0;
	int localSelectedId=0;

	float offset=0;
	float targetOffset=0;

	Timer lerpTimer;
	float lerpTime=0.1f;

	float direction = 1;
	



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