#include "ModulePokedex.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleGamePokedexJapanese.h"
#include "ModuleGamePokedexWorldwide.h"
#include "ModuleMainMenu.h"

const std::string ModulePokedex::TextFormat(int number)
{
    std::string num;
    if (number < 10)
        num = "00" + std::to_string(number);
    else if (number < 100)
        num = "0" + std::to_string(number);
    else
        num = std::to_string(number);
    return num;
}

void ModulePokedex::RenderPokemonInfo(int id)
{
    Rectangle rect;
    Vector2 xy = { 0,0 };
    if (!pokemon_list[id].captured && !pokemon_list[id].discovered)
        return;
    else if (!pokemon_list[id].captured && pokemon_list[id].discovered)
    {
        xy.x = id / 38 * 2 * 48;
        xy.y = id % 38 * 32;
    }
    else if (pokemon_list[id].captured && pokemon_list[id].discovered)
    {
        xy.x = (id / 38 * 2 + 1) * 48;
        xy.y = id % 38 * 32;
        App->text_pokedex_worldwide->Write(pokemon_list[id].height.c_str(), 72, 32, WHITE);
        App->text_pokedex_worldwide->Write(pokemon_list[id].weight.c_str(), 120, 32, WHITE);
    }
    rect = { xy.x, xy.y, 48, 32 };
    App->renderer->Draw(*pokedexPokemon, 8, 16, &rect, WHITE);
}

ModulePokedex::ModulePokedex(Application* app, bool start_enabled) : ModuleScene(app, start_enabled){}

ModulePokedex::~ModulePokedex(){}
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
    App->texture->CreateTexture("Assets/pokemons_shadow_and_color.png", "pokemon");
    pokedexPokemon = App->texture->GetTexture("pokemon");

    StartFadeOut(WHITE, 0.3f);
    return true;
}

update_status ModulePokedex::Update()
{
#pragma region Input
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN)))
    {
        StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);
        App->audio->StopMusic();
        App->audio->PlayFx(audioSelectId);
    }
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP)) || IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))))
    {
        selectedId--;
        if (selectedId < minId) {
            selectedId = minId;
        }

        localSelectedId--;
        if (localSelectedId < minLocalId) {
            localSelectedId = minLocalId;

            targetOffset = selectedId * -15;
        }




    }
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN)) || IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))))
    {
        selectedId++;
        if (selectedId > maxId) {
            selectedId = maxId;
        }

        localSelectedId++;
        if (localSelectedId > maxLocalId)
        {
            localSelectedId = maxLocalId;
            targetOffset = (selectedId-maxLocalId) * -15;
        }
    }
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT)))
    {
        selectedId-= maxLocalId+1;
        if (selectedId < minId) {
            selectedId = minId;
        }
         

        if (selectedId - maxLocalId<=minId){
            targetOffset = 0;
            localSelectedId = selectedId;
        }
        else {
            targetOffset = (selectedId - localSelectedId) * -15;
        }

    }
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT)))
    {
        selectedId+= maxLocalId+1;
        if (selectedId < minId) {
            selectedId = minId;
        }
           

        if (selectedId + maxLocalId >= maxId){
            targetOffset = (maxId - maxLocalId) * -15;
        }
        else {
            targetOffset = (selectedId - localSelectedId) * -15;


        }
    }
#pragma endregion
#pragma region Lerp
    
    //if (factor < 1 && selectedPokemon.x != selectedPokemon.y)
    //{
    //    factor = lerpTimer.ReadSec() / lerpTime;
    //    slots_offset.y = slots_offset.x + (selectedPokemon.x - selectedPokemon.y) * factor * 15;
    //    if (slots_offset.y > 0)
    //    {
    //        factor = 1;
    //    }
    //}
    //else if (factor >= 1 && selectedPokemon.x != selectedPokemon.y)
    //{
    //    slots_offset.y = round(slots_offset.y / 15.0) * 15;;
    //    slots_offset.x = slots_offset.y;
    //    factor = 0;
    //    selectedPokemon.x = selectedPokemon.y;
    //}
   
    printf("%d vs %d \n", localSelectedId, selectedId);


#pragma endregion
#pragma region Render
    Rectangle rect;
    for (size_t i = 0; i < pokemon_list.size(); i++)
    {
        rect = { 0 , (float)15 * selectedLanguage, 124 ,15 };
        App->renderer->Draw(*pokedexSlot, 10, 56 + targetOffset + 15 * i, &rect, WHITE);
        App->text_pokedex_worldwide->Write(TextFormat(i + 1).c_str(), 80, (50 + targetOffset) + (15 * i), BLACK);
    }
    rect = { 160 , 0, 160 ,144 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    rect = { 0, (float)(0 + 53 * selectedLanguage), 160, 53 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    RenderPokemonInfo(selectedId);
    rect = { 0 , 90, 124 ,15 };
    App->renderer->Draw(*pokedexSlot, 10, 144 - 15, &rect, WHITE);
    rect = { 178 , 144, 5, 8 };
    App->renderer->Draw(*pokedexSpritesheet, 25, 63 + localSelectedId * 15, &rect, WHITE);
#pragma endregion


    ModuleScene::FadeUpdate();
    return UPDATE_CONTINUE;
}

bool ModulePokedex::CleanUp()
{
    return true;
}

void ModulePokedex::LoadConfigFile()
{
    pugi::xml_parse_result result = _data.load_file("Assets/Pokedex/Pokedex2.xml");
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
    _data.save_file("Assets/Pokedex/Pokedex2.xml");
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
            pokemonIdNode.child("weight").attribute("value").as_string(),
            pokemonIdNode.child("height").attribute("value").as_string(),
            pokemonIdNode.child("pre-evolution-index").attribute("value").as_int(),
            pokemonIdNode.child("habitat-index").attribute("value").as_int(),
            pokemonNames,
            pokemonBlueMapLocations,
            pokemonRedMapLocations
        };
            
        pokemon_list.push_back(pokemon);
    }
}
