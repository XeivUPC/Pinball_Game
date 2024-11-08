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
    printf("%f %f   %d\n", slots_offset.x, slots_offset.y, selectedPokemon.y);
#pragma region Input
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN)))
    {
        StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);
        App->audio->StopMusic();
        App->audio->PlayFx(audioSelectId);
    }
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP)) || IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) && selectedPokemon.y > 0)
    {
        if (localSelection > 0)
        {
            selectedPokemon.x--;
            localSelection--;
        }
        if (selectedPokemon.x == selectedPokemon.y)
            lerpTimer.Start();
        selectedPokemon.y--;
    }
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN)) || IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) && selectedPokemon.y < 152)
    {
        if (localSelection < 4)
        {
            selectedPokemon.x++;
            localSelection++;
        }
        if (selectedPokemon.x == selectedPokemon.y)
            lerpTimer.Start();
        selectedPokemon.y++;
    }
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT)))
    {
        if(selectedPokemon.x - 5 < 5)
        {
            selectedPokemon.x = localSelection;
            selectedPokemon.y = localSelection;
            slots_offset.y = 0 * 15;
        }
        else
        {
            selectedPokemon.x -= 5;
            selectedPokemon.y -= 5;
            slots_offset.y += 5 * 15;
        }
    }
    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT)))
    {
        if (selectedPokemon.x + 5 > 147)
        {
            selectedPokemon.x += 5;
            selectedPokemon.y += 5;
            slots_offset.y = -147 * 15;
        }
        else
        {
            selectedPokemon.x += 5;
            selectedPokemon.y += 5;
            slots_offset.y -= 5 * 15;
        }
    }
#pragma endregion
#pragma region Lerp
    
    if (factor < 1 && selectedPokemon.x != selectedPokemon.y)
    {
        factor = lerpTimer.ReadSec() / lerpTime;
        slots_offset.y = slots_offset.x + (selectedPokemon.x - selectedPokemon.y) * factor*15;
        if (slots_offset.y > 0)
        {
            factor = 1;
        }
    }
    else if (factor >= 1 && selectedPokemon.x != selectedPokemon.y)
    {
        slots_offset.y = round(slots_offset.y / 15.0) * 15;;
        slots_offset.x = slots_offset.y;
        factor = 0;
        selectedPokemon.x = selectedPokemon.y;
    }
#pragma endregion
#pragma region Render
    Rectangle rect;
    for (size_t i = 0; i < pokemon_list.size(); i++)
    {
        rect = { 0 , (float)15 * selectedLanguage, 124 ,15 };
        App->renderer->Draw(*pokedexSlot, 10, 56 + slots_offset.y + 15 * i, &rect, WHITE);
        App->text_pokedex_worldwide->Write(TextFormat(i + 1).c_str(), 80, (50 + slots_offset.y) + (15 * i), BLACK);
    }
    rect = { 160 , 0, 160 ,144 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    rect = { 0, (float)(0 + 53 * selectedLanguage), 160, 53 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    RenderPokemonInfo(selectedPokemon.x);
    rect = { 0 , 90, 124 ,15 };
    App->renderer->Draw(*pokedexSlot, 10, 144 - 15, &rect, WHITE);
    rect = { 178 , 144, 5, 8 };
    App->renderer->Draw(*pokedexSpritesheet, 25, 63 + localSelection * 15, &rect, WHITE);
#pragma endregion


    //if (IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP)) || IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP)))
    //{
    //    if (localSelection == 0 && factor == 0 && selectedPokemon > 0)
    //    {
    //        lerpTimer.Start();
    //        direction = 1;
    //        selectedPokemon--;
    //    }
    //    else if (selectedPokemon > 0 && localSelection > 0)
    //    {
    //        localSelection--;
    //        selectedPokemon--;
    //    }
    //}
    //else if (IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN)) || IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN)))
    //{
    //    if (localSelection == 4 && factor == 0 && selectedPokemon < 150)
    //    {
    //        lerpTimer.Start();
    //        direction = -1;
    //        selectedPokemon++;
    //    }
    //    else if (selectedPokemon < 150 && localSelection < 4)
    //    {
    //        localSelection++;
    //        selectedPokemon++;
    //    }
    //}
    //else if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT)))
    //{
    //    if (selectedPokemon-5 < 5)
    //    {
    //        slots_offset.y = 0;
    //        selectedPokemon = localSelection;
    //    }
    //    else
    //    {
    //        selectedPokemon -= 5;
    //        slots_offset.y += 5 * 15;
    //    }
    //}
    //else if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT)))
    //{
    //    if (selectedPokemon + 5 > 145)
    //    {
    //        slots_offset.y = 15*145;
    //        selectedPokemon = 145+localSelection;
    //    }
    //    else
    //    {
    //        selectedPokemon += 5;
    //        slots_offset.y -= 5 * 15;
    //    }
    //}
    //
    //factor += lerpTimer.ReadSec() / lerpTime;
    //if (factor > 0 && factor < 1)
    //    slots_offset.y += 15 * direction / lerpTime * lerpTimer.ReadSec();
    //else if (direction != 0)
    //{
    //    int slots = slots_offset.y / 15;
    //    slots_offset.y = (slots + direction) * 15;
    //    if (direction == 1)
    //        slots_offset.y -= direction * 15;
    //}
    //if (factor > 1)
    //{
    //    factor = 0;
    //    direction = 0;
    //}
    //for (size_t i = 0; i < pokemon_list.size(); i++)
    //{
    //    Rectangle rect = { 0 , 0 + 15 * selectedLanguage, 124 ,15 };
    //    App->renderer->Draw(*pokedexSlot, 10, 56 + slots_offset.y + 15 * i, &rect, WHITE);
    //    App->text_pokedex_worldwide->Write(TextFormat(i + 1).c_str(), 80, (50 + slots_offset.y) + (15 * i), BLACK);
    //}

    //Rectangle rect = { 0 , 90, 124 ,15 };
    //App->renderer->Draw(*pokedexSlot, 10, 144 - 15, &rect, WHITE);
    //for (size_t i = 0; i < pokemon_list.size(); i++)
    //{
    //    if (pokemon_list.at(i).captured)
    //    {
    //        switch (selectedLanguage)       //Names
    //        {
    //        case 0:
    //            App->text_pokedex_japanese->Write(pokemon_list[i].Names.at(0).c_str(), 48, 60 + slots_offset.y + 15 * i, BLACK);
    //            break;
    //        case 1:
    //            App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(1).c_str(), 48, 60 + slots_offset.y + 15 * i, BLACK);
    //            break;
    //        case 2:
    //            App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(2).c_str(), 48, 60 + slots_offset.y + 15 * i, BLACK);
    //            break;
    //        case 3:
    //            App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(3).c_str(), 48, 60 + slots_offset.y + 15 * i, BLACK);
    //            break;
    //        case 4:
    //            App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(4).c_str(), 48, 60 + slots_offset.y + 15 * i, BLACK);
    //            break;
    //        case 5:
    //            App->text_pokedex_worldwide->Write(pokemon_list[i].Names.at(5).c_str(), 48, 60 + slots_offset.y + 15 * i, BLACK);
    //            break;
    //        }
    //    }
    //}
    //rect = { 160 , 0, 160 ,144 };
    //App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    //rect = { 0, (float)(0 + 53 * selectedLanguage), 160, 53 };
    //App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    //rect = { 178 , 144, 5, 8 };
    //App->renderer->Draw(*pokedexSpritesheet, 25, 63 + localSelection * 15, &rect, WHITE);
    //App->text_pokedex_worldwide->Write(TextFormat(selectedPokemon + 1).c_str(), 32, 0, WHITE);
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
            pokemonIdNode.child("weight").attribute("value").as_string(),
            pokemonIdNode.child("height").attribute("value").as_string(),
            pokemonIdNode.child("preevolution-index").attribute("value").as_int(),
            pokemonIdNode.child("overworld-index").attribute("value").as_int(),
            pokemonNames,
            pokemonBlueMapLocations,
            pokemonRedMapLocations
        };
            
        pokemon_list.push_back(pokemon);
    }
}
