#include "ModulePokedex.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleGamePokedexJapanese.h"
#include "ModuleGamePokedexWorldwide.h"
#include "ModuleMainMenu.h"

const std::string ModulePokedex::Text0Format(int number)
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

int ModulePokedex::AnchorToRight(const std::string& text, int x)
{
    x -= text.size()*8;
    int commas = 0;
    size_t i = 0;
    while (i < text.size())
    {
        if (text[i] == ',')
            commas++;
        i++;
    }
    x += 8 * commas;
    return x;
}

void ModulePokedex::RenderPokemonInfo(int id)
{
    Rectangle rect;
    Vector2 xy = { 0,0 };
    App->text_pokedex_worldwide->Write(Text0Format(id+1).c_str(), 32, 0, WHITE);
    if (!pokemon_list[id].captured && !pokemon_list[id].discovered)
        return;
    else if (!pokemon_list[id].captured)
    {
        xy.x = (float)(id / 38 * 2 * 48);
        xy.y = (float)(id % 38 * 32);
    }
    else
    {
        xy.x = (float)((id / 38 * 2 + 1) * 48);
        xy.y = (float)(id % 38 * 32);
        if (selectedLanguage == 1)
        {
            App->text_pokedex_worldwide->Write(ToLibras(pokemon_list[id].weight).c_str(), AnchorToRight(ToLibras(pokemon_list[id].weight).c_str(), 144), 32, WHITE);
            App->text_pokedex_worldwide->Write(ToFeet(pokemon_list[id].height).c_str(), AnchorToRight(ToFeet(pokemon_list[id].height).c_str(), 80), 32, WHITE);
            App->text_pokedex_worldwide->Write(ToInchDecimal(pokemon_list[id].height).c_str(), AnchorToRight(ToInchDecimal(pokemon_list[id].height).c_str(), 96), 32, WHITE);
        }
        else
        {
            if(selectedLanguage == 0)
                App->text_pokedex_worldwide->Write(pokemon_list[id].weight.c_str(), AnchorToRight(pokemon_list[id].weight.c_str(), 136), 32, WHITE);
            else
                App->text_pokedex_worldwide->Write(pokemon_list[id].weight.c_str(), AnchorToRight(pokemon_list[id].weight.c_str(), 144), 32, WHITE);
            App->text_pokedex_worldwide->Write(pokemon_list[id].height.c_str(), AnchorToRight(pokemon_list[id].height.c_str(), 88), 32, WHITE);
        }
    }
    if(selectedLanguage == 0)
        App->text_pokedex_japanese->Write(pokemon_list[id].Names.at(selectedLanguage).c_str(), 64, 10, WHITE);
    else
        App->text_pokedex_worldwide->Write(pokemon_list[id].Names.at(selectedLanguage).c_str(), 64, 10, WHITE);
    rect = { xy.x, xy.y, 48, 32 };
    App->renderer->Draw(*pokedexPokemon, 8, 16, &rect, WHITE);
}

float ModulePokedex::StringToNumber(std::string string)
{
    float integerweight = 0;
    float decimalweight = 0;
    int count = 0;
    size_t i = 0;
    while (i < string.size())
    {
        integerweight += string[i] - 48;
        integerweight *= 10;
        i++;
        if (string[i] == ',')
            break;
    }
    integerweight /= 10;
    i++;
    while (i < string.size())
    {
        decimalweight += string[i] - 48;
        decimalweight *= 10;
        i++;
        count++;
    }
    decimalweight /= 10;
    decimalweight /= (float)pow(10, count);

    float w = (integerweight + decimalweight);
    return w;
}

std::string ModulePokedex::ToLibras(std::string weight)
{
    float w = StringToNumber(weight)* 2.205f;
    w = std::round(w*10)/10;
    std::string str = std::to_string(w);
    size_t i = 0;
    while (i < str.size())
    {
        if (str[i] == '.')
        {
            str[i] = ',';
            i++;
            break;
        }
        i++;
    }
    for (size_t t = str.size(); t > i+1; t--)
    {
        str.pop_back();
    }
    return str;
}

std::string ModulePokedex::ToFeet(std::string height)
{
    float w = trunc(StringToNumber(height) * 3.28084f);
    std::string str = std::to_string((int)w);
    return str;
}

std::string ModulePokedex::ToInchDecimal(std::string height)
{
    float w = StringToNumber(height) * 3.28084f;
    w -= (int)w;
    w *= 12;
    w = trunc(w);
    std::string str = std::to_string((int)w);
    return str;
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

            targetOffset = selectedId * -16.f;
        }
        lerpTimer.Start();
        direction = 1;
    }
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN)) || IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))))
    {
        selectedId++;
        if (selectedId > maxId)
        {
            selectedId = maxId;
        }

        localSelectedId++;
        if (localSelectedId > maxLocalId)
        {
            localSelectedId = maxLocalId;
            targetOffset = (selectedId-maxLocalId) * -16.f;
        }
        lerpTimer.Start();
        direction = -1;
    }
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT)) || IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))))
    {
        selectedId-= maxLocalId+1;
        if (selectedId < minId) {
            selectedId = minId;
        }
         
        if (selectedId - maxLocalId<=minId)
        {
            targetOffset = 0;
            localSelectedId = selectedId;
        }
        else
        {
            targetOffset = (selectedId - localSelectedId) * -16.f;
        }
              offset = targetOffset;
    }
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT)) || IsKeyPressedRepeat(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))))
    {
        selectedId+= maxLocalId+1;
        if (selectedId > maxId)
        {
            selectedId = maxId;
        }
           
        if (selectedId + maxLocalId >= maxId)
        {
            targetOffset = (maxId - maxLocalId) * -16.f;

            localSelectedId = maxLocalId - (maxId - selectedId);
        }
        else
        {
            targetOffset = (selectedId - localSelectedId) * -16.f;
        }

        offset = targetOffset;
    }
#pragma endregion
#pragma region Lerp
    

    if (targetOffset!=offset) {
        float factor = lerpTimer.ReadSec() / lerpTime;
        int distance = abs(targetOffset - offset);
        offset = offset + distance * factor * direction;
        distance = abs(targetOffset - offset);
        if (distance < 1) {
            offset = targetOffset;
        }
    }

#pragma endregion
#pragma region Render
    App->renderer->DrawRect(0, 0, SCREEN_WIDTH , SCREEN_HEIGHT, WHITE);
    Rectangle rect;
    for (size_t i = 0; i < pokemon_list.size(); i++)
    {
        rect = { 0 , 16.f * selectedLanguage, 124 ,16 };
        App->renderer->Draw(*pokedexSlot, 10, (int)(56 + offset + 16 * i), &rect, WHITE);
        App->text_pokedex_worldwide->Write(Text0Format(i + 1).c_str(), 56, (int)((49 + offset) + (16 * i)), BLACK);
    }
    for (size_t i = 0; i < pokemon_list.size(); i++)
    {
        if (pokemon_list.at(i).captured)
        {
            if(selectedLanguage == 0)
                App->text_pokedex_japanese->Write(pokemon_list.at(i).Names.at(selectedLanguage).c_str(), 48, (int)(60+ 16 * i + offset), BLACK);
            else
                App->text_pokedex_worldwide->Write(pokemon_list.at(i).Names.at(selectedLanguage).c_str(), 48, (int)(60 + 16 * i + offset), BLACK);
        }
    }


    rect = { 160 , 0, 160 ,144 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    rect = { 0, (float)(0 + 53 * selectedLanguage), 160, 53 };
    App->renderer->Draw(*pokedexSpritesheet, 0, 0, &rect, WHITE);
    RenderPokemonInfo(selectedId);
    rect = { 178 , 144, 5, 8 };
    App->renderer->Draw(*pokedexSpritesheet, 25, 63 + localSelectedId * 16, &rect, WHITE);  /// Add Animation
    App->renderer->DrawRect(10,139, SCREEN_WIDTH-36,5,WHITE);
    App->renderer->DrawRect(10,56, SCREEN_WIDTH-36,3, WHITE);
#pragma endregion
    ModuleScene::FadeUpdate();
    return UPDATE_CONTINUE;
}

bool ModulePokedex::CleanUp()
{
    selectedId = 0;
    localSelectedId = 0;
    offset = 0;
    targetOffset = 0;
    return true;
}

void ModulePokedex::LoadConfigFile()
{
    pugi::xml_parse_result result = _data.load_file("Assets/Data/Pokedex.xml");
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
    _data.save_file("Assets/Data/Pokedex.xml");
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
            std::string name = language.attribute("value").as_string();
            pokemonNames.emplace_back(name);
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

void ModulePokedex::SavePokedex()
{
}