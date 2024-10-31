#include "ModuleGamePokedexJapanese.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"


Rectangle* ModuleGamePokedexJapanese::GetCharRect(int index)
{
	Rectangle* rect = new Rectangle{ 0,0,0,0 };
	rect->x = (int)((index % (int)count.x)*size.x);
	rect->y = (int)((index / (int)count.x)*size.y);
	rect->width = size.x;
	rect->height = size.y;
	return rect;
}

ModuleGamePokedexJapanese::ModuleGamePokedexJapanese(Application* app, bool start_enabled) : ModuleText(app, start_enabled)
{
}

ModuleGamePokedexJapanese::~ModuleGamePokedexJapanese()
{
}

bool ModuleGamePokedexJapanese::Init()
{
    return true;
}

bool ModuleGamePokedexJapanese::Start()
{
	App->texture->CreateTexture("Assets/pokedex-japanese.png", "font-japanese");
	fontTexture = App->texture->GetTexture("font-japanese");
	size = Vector2{ 8,16 };
	int widht, height;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;
    return true;
}


bool ModuleGamePokedexJapanese::CleanUp()
{
    charReferences.clear();
    return true;
}


void ModuleGamePokedexJapanese::Write(const char* text, int x, int y, Color color)
{
	int i = 0;
	while (text[i] != '\0')
	{
		int t = 0;
		int number = 0;
		while (text[t] != ',')
		{
			number += text[t] - 48;
			number *= 10;
			t++;
		}
		number /= 10;
		Rectangle* letter = GetCharRect(number);
		App->renderer->Draw(*fontTexture, (x + size.x * i), y, letter, color);
		i++;
	}
}
