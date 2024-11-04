#include "ModulePokedex.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleGamePokedexJapanese.h"
#include "ModuleGamePokedexWorldwide.h"
#include "ModuleMainMenu.h"

ModulePokedex::ModulePokedex(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

ModulePokedex::~ModulePokedex()
{
}
bool ModulePokedex::Init()
{
    LoadConfigFile();
    LoadPokedex();

    return true;
}

bool ModulePokedex::Start()
{
    selectedLanguage = App->userPreferences->GetLanguage();
    audioSelectId = App->audio->LoadFx("Assets/SFX/Menu_Option_Select.ogg");
    audioMoveId = App->audio->LoadFx("Assets/SFX/Menu_Option_Move.ogg");
    App->texture->CreateTexture("Assets/pokedex-spritesheet.png", "spritesheet");
    pokedexSpritesheet = App->texture->GetTexture("spritesheet");
    App->texture->CreateTexture("Assets/index-slot.png", "slot");
    pokedexSlot = App->texture->GetTexture("slot");
    StartFadeOut(WHITE, 0.3f);
    return true;
    
}

update_status ModulePokedex::Update()
{
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN))) {
        ///Go Back
        StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);

        App->audio->StopMusic();
        App->audio->PlayFx(audioSelectId);
    }
    factor += lerpTimer.ReadSec() / lerpTime;
    int direction = 0;
    if (factor > 1)
        factor = 0;
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP)))
    {
        if (localSelection == 0 && factor < 1)
        {
            lerpTimer.Start();
            direction = 1;
        }
        else
            localSelection--;
    }
    else if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN)))
    {
        if (localSelection == 4 && factor < 1)
        {
            lerpTimer.Start();
            direction = -1;
        }
        else
            localSelection++;
    }
    else
    {
        direction = 0;
    }
        
    slots_offset += 15 * lerpTimer.ReadSec() * direction;
    printf("%f\n", factor);
    for (size_t i = 0; i < pokemon_list.size(); i++)
    {
        Rectangle rect = { 0 , 0 + 15 * selectedLanguage, 124 ,15 };
        App->renderer->Draw(*pokedexSlot, 10, 56 + slots_offset + 15 * i, &rect, WHITE);
        App->text_pokedex_worldwide->Write(std::to_string(i+1).c_str(), 80, 51 + slots_offset + 15 * i, BLACK);
        if ((i+1) < 100)
        {
            App->text_pokedex_worldwide->Write(std::to_string(0).c_str(), 72, 51 + slots_offset + 15 * i, BLACK);
            if((i+1) < 10)
                App->text_pokedex_worldwide->Write(std::to_string(0).c_str(), 64, 51 + slots_offset + 15 * i, BLACK);
        }
        
    }
    for (size_t i = 0; i < pokemon_list.size(); i++)
    {
        if (pokemon_list.at(i).captured)
        {
            switch (selectedLanguage)
            {
            case 0:
                App->text_pokedex_japanese->Write(pokemon_list[i].Names.at(0).c_str(), 48, 60 + slots_offset + 15 * i, BLACK);
                break;
            case 1:
                App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(1).c_str(), 48, 60 + slots_offset + 15 * i, BLACK);
                break;
            case 2:
                App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(2).c_str(), 48, 60 + slots_offset + 15 * i, BLACK);
                break;
            case 3:
                App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(3).c_str(), 48, 60 + slots_offset + 15 * i, BLACK);
                break;
            case 4:
                App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(4).c_str(), 48, 60 + slots_offset + 15 * i, BLACK);
                break;
            case 5:
                App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(5).c_str(), 48, 60 + slots_offset + 15 * i, BLACK);
                break;
            }
        }
    }
    
    Rectangle rect = {160 , 0, 160 ,144 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    rect = { 0, (float)(0 + 53 * selectedLanguage), 160, 53 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    ModuleScene::FadeUpdate();
    return UPDATE_CONTINUE;
}

bool ModulePokedex::CleanUp()
{
    return true;
}

void ModulePokedex::LoadConfigFile()
{
    pugi::xml_parse_result result = _data.load_file("Assets/Pokedex/Pokedex.xml");
    if (result)
    {
        LOG("config.xml parsed without errors");
    }
    else
    {
        LOG("Error loading config.xml: %s", result.description());
    }
}

void ModulePokedex::SaveConfigFile()
{
    _data.save_file("Assets/Pokedex/Pokedex.xml");
}

void ModulePokedex::LoadPokedex()
{
    xml_node pokedex = _data.child("pokedex");
    for (pugi::xml_node pokemonIdNode = pokedex.child("id"); pokemonIdNode != NULL; pokemonIdNode = pokemonIdNode.next_sibling("id"))
    {
        std::vector<std::string> pokemonNames;
        std::vector<int> pokemonBlueMapLocations;
        std::vector<int> pokemonRedMapLocations;
        for (pugi::xml_node language = pokemonIdNode.child("name"); language != NULL; language = language.next_sibling("name"))
        {
            pokemonNames.emplace_back(language.attribute("value").as_string());
        }
        for (pugi::xml_node bluemap = pokemonIdNode.child("bluemaploc"); bluemap != NULL; bluemap = bluemap.next_sibling("bluemaploc"))
        {
            pokemonBlueMapLocations.emplace_back(bluemap.attribute("value").as_int());
        }
        for (pugi::xml_node redmap = pokemonIdNode.child("redmaploc"); redmap != NULL; redmap = redmap.next_sibling("redmaploc"))
        {
            pokemonRedMapLocations.emplace_back(redmap.attribute("value").as_int());
        }

        Pokemon pokemon = Pokemon
        {
            pokemonIdNode.attribute("value").as_int(),
            pokemonIdNode.child("discovered").attribute("value").as_bool(),
            pokemonIdNode.child("captured").attribute("value").as_bool(),
            pokemonIdNode.child("weight").attribute("value").as_float(),
            pokemonIdNode.child("height").attribute("value").as_float(),
            pokemonIdNode.child("preevolution-index").attribute("value").as_int(),
            pokemonIdNode.child("overworld-index").attribute("value").as_int(),
            pokemonNames,
            pokemonBlueMapLocations,
            pokemonRedMapLocations
        };
            
        pokemon_list.push_back(pokemon);
    }
}
