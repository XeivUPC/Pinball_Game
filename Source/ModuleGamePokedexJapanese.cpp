#include "ModuleGamePokedexJapanese.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"


Rectangle ModuleGamePokedexJapanese::GetCharRect(int index)
{
	Rectangle rect = Rectangle{ 0,0,0,0 };
	rect.x = (float)((int)((index % (int)count.x)*size.x));
	rect.y = (float)((int)((index / (int)count.x)*size.y));
	rect.width = size.x;
	rect.height = size.y;
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
	int widht=0, height=0;
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
	int t = 0;
	while ((text[i] > 47 && text[i] < 58) && text[i] != ',')
	{
		int number = 0;
		while ((text[i] > 47 && text[i] < 58) && text[i] != ',')
		{
			number += text[i] - 48;
			number *= 10;
			i++;
		}
		number /= 10;
		Rectangle letter = GetCharRect(number);
		App->renderer->Draw(*fontTexture, (int)((x + size.x * t)), y+1, &letter, color);
		i++;
		t++;
	}
}
