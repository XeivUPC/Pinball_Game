#include "ModuleGamePokedexWorldWide.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"
#include <string>

Rectangle* ModuleGamePokedexWorldWide::GetCharRect(char c)
{
	Rectangle* rect = new Rectangle{ 0,0,0,0 };
	for (size_t i = 0; i < charReferences.size(); i++)
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
	App->texture->CreateTexture("Assets/pokedex-worldwide.png", "font-worldwide");
	fontTexture = App->texture->GetTexture("font-worldwide");
	size = Vector2{ 8,16 };
	int widht=0, height=0;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;
	// Uppercase letters A to Z
	for (char c = 'A'; c <= 'Z'; ++c) {
		charReferences.push_back(static_cast<int>(c));
	}

	// Numbers 0 to 9
	for (char c = '0'; c <= '9'; ++c) {
		charReferences.push_back(static_cast<int>(c));
	}

	// Space
	charReferences.push_back(44); // ASCII code for space
	charReferences.push_back(39); // ASCII code for space
	charReferences.push_back('+'); // ASCII code for space
	charReferences.push_back('-'); // ASCII code for space
	charReferences.push_back(32); // ASCII code for space

    return true;
}


bool ModuleGamePokedexWorldWide::CleanUp()
{
    charReferences.clear();
    return true;
}


void ModuleGamePokedexWorldWide::Write(const char* text, int x, int y, Color color)
{
	int i = 0;

	while (text[i] != '\0')
	{
		Rectangle* letter = GetCharRect(text[i]);
		if (text[i] > 96 && text[i] < 123)
			letter = GetCharRect(text[i]-32);
		if (text[i] == ',')
		{
			x -= (int)size.x;
			App->renderer->Draw(*fontTexture, (int)(x + size.x * i), (int)(y+1), letter, color);
		}
		else
			App->renderer->Draw(*fontTexture, (int)(x + size.x * i), (int)(y), letter, color);
		i++;
	}
}
