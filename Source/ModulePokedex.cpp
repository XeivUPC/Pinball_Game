#include "ModulePokedex.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleGamePokedexJapanese.h"
#include "ModuleGamePokedexWorldwide.h"
#include "ModuleMainMenu.h"
#include <sstream>
#include <string>

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

    ScrollBarAnimator = new Animator(App);
    AnimationData ScrollBarAnim = AnimationData("ScrollBar");
    ScrollBarAnim.AddSprite(Sprite{ pokedexSpritesheet, {27,72}, { 6, 2}});
    ScrollBarAnim.AddSprite(Sprite{ pokedexSpritesheet, {28,72}, { 6, 2}});
    ScrollBarAnim.AddSprite(Sprite{ pokedexSpritesheet, {29,72}, { 6, 2}});
    ScrollBarAnimator->AddAnimation(ScrollBarAnim);
    ScrollBarAnimator->SetSpeed(0.1f);
    ScrollBarAnimator->SelectAnimation("ScrollBar", true);
    StartFadeOut(WHITE, 0.3f);
    return true;
}

update_status ModulePokedex::Update()
{
    moving = false;
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
        if (selectedId < minId)
        {
            selectedId = minId;
        }

        localSelectedId--;
        if (localSelectedId < minLocalId)
        {
            localSelectedId = minLocalId;
            targetOffset = selectedId * -16.f;
        }
        lerpTimer.Start();
        direction = 1;
        moving = true;
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
        moving = true;
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
              direction = -1;
              moving = true;
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
        direction = 1;
        moving = true;
    }
#pragma endregion
#pragma region Lerp
    
    if (targetOffset!=offset)
    {
        float factor =(float)(lerpTimer.ReadSec() / lerpTime);
        int distance = (int)abs(targetOffset - offset);
        offset = offset + distance * factor * direction;
        distance = (int)abs(targetOffset - offset);
        if (distance < 1) {
            offset = targetOffset;
        }
    }
#pragma endregion
#pragma region Render
    ScrollBarAnimator->Update();
    arrowCurrentTime -= GetFrameTime();

    if (arrowCurrentTime <= 0)
    {
        arrowCurrentTime = arrowAnimSpeed;
        arrowAppeared = !arrowAppeared;
    }
    if (moving)
    {
        arrowAppeared = true;
        arrowCurrentTime = arrowAnimSpeed;
    }
        
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
        if (pokemon_list.at(i).discovered)
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
    rect = { 180 , 144, 5, 8 };
    if(arrowAppeared)
        App->renderer->Draw(*pokedexSpritesheet, 25, 63 + localSelectedId * 16, &rect, WHITE);
    App->renderer->DrawRect(10,139, SCREEN_WIDTH-36,5,WHITE);
    App->renderer->DrawRect(10,56, SCREEN_WIDTH-36,3, WHITE);

    ScrollBarAnimator->Animate(145, (73 + (134 - 73) * selectedId / pokemon_list.size()), true);
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

    SaveConfigFile();
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


        std::string blueMapIndexs = pokemonIdNode.child("blue-habitat-index").attribute("value").as_string();

        if (blueMapIndexs != "-1") {
            std::stringstream ss(blueMapIndexs);
            std::string temp;

            while (std::getline(ss, temp, ',')) {
                pokemonBlueMapLocations.push_back(std::stoi(temp));
            }
        }



        std::string redMapIndexs = pokemonIdNode.child("red-habitat-index").attribute("value").as_string();

        if (redMapIndexs != "-1") {

            std::stringstream ss(redMapIndexs);
            std::string temp;

            while (std::getline(ss, temp, ',')) {
                pokemonRedMapLocations.push_back(std::stoi(temp));
            }
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
            pokemonRedMapLocations,
            pokemonBlueMapLocations
        };
            
        pokemon_list.push_back(pokemon);
    }
    /*for (size_t i = 0; i < 18; i++)
    {
        printf("%d ->", i);
        for (size_t x = 0; x < pokemon_list.size(); x++)
        {
            for (size_t y = 0; y < pokemon_list[x].blueMapLocations.size(); y++)
            {
                if(pokemon_list[x].blueMapLocations[y] == i)
                    printf(" %s,", pokemon_list[x].Names[1].c_str());
                    
            }
        }
        printf("\n");
    }*/
}

int ModulePokedex::GetPokemonListCount()
{
    return pokemon_list.size();
}

std::vector<int> ModulePokedex::GetBlueMapHabitats(int i)
{
    return pokemon_list.at(i).blueMapLocations;
}

std::vector<int> ModulePokedex::GetRedMapHabitats(int i)
{
    return pokemon_list.at(i).redMapLocations;
}

int ModulePokedex::GetPokemonRarity(int i)
{
    return 0;
}

void ModulePokedex::DiscoverPokemon(int id)
{
    pokemon_list.at(id).discovered = true;
    SavePokemon(pokemon_list.at(id).ID);
}

void ModulePokedex::CapturePokemon(int id)
{

    pokemon_list.at(id).discovered = true;
    pokemon_list.at(id).captured = true;

    SavePokemon(pokemon_list.at(id).ID);

    while (SearchEvolutionID(id) != -1)
    {
        pokemon_list.at(SearchEvolutionID(id)).discovered = true;
        SavePokemon(pokemon_list.at(SearchEvolutionID(id)).ID);
        id = SearchEvolutionID(id);
    }
}

void ModulePokedex::SavePokemon(int id)
{
    xml_node pokedex = _data.child("pokedex");

    for (pugi::xml_node pokemonIdNode = pokedex.child("id"); pokemonIdNode != NULL; pokemonIdNode = pokemonIdNode.next_sibling("id"))
    {
        if (pokemonIdNode.attribute("value").as_int() == id)
        {
            pokemonIdNode.child("discovered").attribute("value").set_value(pokemon_list[id-1].discovered);
            pokemonIdNode.child("captured").attribute("value").set_value(pokemon_list[id-1].captured);
            break;
        }
    }
    SaveConfigFile();
}

int ModulePokedex::SearchEvolutionID(int id)
{
    for (size_t i = 0; i < pokemon_list.size(); i++)
    {
        if (pokemon_list.at(i).preevolutionIndex == pokemon_list.at(id).ID)
            return i;
    }
    return -1;
}
