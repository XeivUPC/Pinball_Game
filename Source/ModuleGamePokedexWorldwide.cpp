#include "ModuleGamePokedexWorldWide.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"


Rectangle* ModuleGamePokedexWorldWide::GetCharRect(char c)
{
	Rectangle* rect = new Rectangle{ 0,0,0,0 };
	for (int i = 0; i < charReferences.size(); i++)
	{
		if ((int)c == charReferences[i])
		{
			rect->x = i % (int)count.x * size.x;
			rect->y = i / (int)count.x * size.y;
			break;
		}
	}
	rect->width = size.x;
	rect->height = size.y;
	return rect;
}

ModuleGamePokedexWorldWide::ModuleGamePokedexWorldWide(Application* app, bool start_enabled) : ModuleText(app, start_enabled)
{
}

ModuleGamePokedexWorldWide::~ModuleGamePokedexWorldWide()
{
}

bool ModuleGamePokedexWorldWide::Init()
{
    return true;
}

bool ModuleGamePokedexWorldWide::Start()
{
	App->texture->CreateTexture("Assets/game_letters&nums.png", "game_letters&nums");
	fontTexture = App->texture->GetTexture("game_letters&nums");
	size = Vector2{ 8,16 };
	int widht, height;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
	charReferences.push_back(65);
    return true;
}


bool ModuleGamePokedexWorldWide::CleanUp()
{
    charReferences.clear();
    return true;
}


void ModuleGamePokedexWorldWide::Write(const char* text, int x, int y)
{
	int i = 0;
	while (text[i] != '\0')
	{
		Rectangle* letter = GetCharRect(text[i]);
		App->renderer->Draw(*fontTexture, (x + size.x * i), y, letter, WHITE);
		i++;
	}
}
