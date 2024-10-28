#include "ModuleGameUIText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"


Rectangle* ModuleGameUIText::GetCharRect(char c)
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

ModuleGameUIText::ModuleGameUIText(Application* app, bool start_enabled) : ModuleText(app, start_enabled)
{
}

ModuleGameUIText::~ModuleGameUIText()
{
}

bool ModuleGameUIText::Init()
{
    return true;
}

bool ModuleGameUIText::Start()
{
	App->texture->CreateTexture("Assets/game_letters&nums.png", "game_letters&nums");
	fontTexture = App->texture->GetTexture("game_letters&nums");
	size = Vector2{ 8,8 };
	int widht, height;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;
	charReferences.push_back(65);
	charReferences.push_back(66);
	charReferences.push_back(67);
	charReferences.push_back(68);
	charReferences.push_back(69);
	charReferences.push_back(70);
	charReferences.push_back(71);
	charReferences.push_back(72);
	charReferences.push_back(73);
	charReferences.push_back(74);
	charReferences.push_back(75);
	charReferences.push_back(76);
	charReferences.push_back(77);
	charReferences.push_back(78);
	charReferences.push_back(79);
	charReferences.push_back(81);
	charReferences.push_back(82);
	charReferences.push_back(83);
	charReferences.push_back(84);
	charReferences.push_back(85);
	charReferences.push_back(86);
	charReferences.push_back(87);
	charReferences.push_back(88);
	charReferences.push_back(89);
	charReferences.push_back(90);
	charReferences.push_back(136);
	charReferences.push_back(39);
	charReferences.push_back(46);
	charReferences.push_back(46);
	charReferences.push_back(58);
	charReferences.push_back(33);
	charReferences.push_back(47);

	charReferences.push_back(2640);
	charReferences.push_back(2642);

	charReferences.push_back(181);
	charReferences.push_back(183);

	charReferences.push_back(212);
	charReferences.push_back(201);

	charReferences.push_back(214);
	charReferences.push_back(205);

	charReferences.push_back(165);
	charReferences.push_back(153);
	charReferences.push_back(224);

	charReferences.push_back(154);
	charReferences.push_back(233);

	charReferences.push_back(45);
	charReferences.push_back(173);

	charReferences.push_back(48);
	charReferences.push_back(49);
	charReferences.push_back(50);
	charReferences.push_back(51);
	charReferences.push_back(52);
	charReferences.push_back(53);
	charReferences.push_back(54);
	charReferences.push_back(55);
	charReferences.push_back(56);
	charReferences.push_back(57);

	charReferences.push_back(239);
	charReferences.push_back(39);

	charReferences.push_back(2192);
	charReferences.push_back(2193);
	charReferences.push_back(2191);
	charReferences.push_back(2605);
	charReferences.push_back(158);
	charReferences.push_back(94);
	charReferences.push_back(197);
	charReferences.push_back(64);
	charReferences.push_back(32);
    return true;
}


bool ModuleGameUIText::CleanUp()
{
    charReferences.clear();
    return true;
}


void ModuleGameUIText::Write(const char* text, int x, int y)
{
	int i = 0;
	while (text[i] != '\0')
	{
		Rectangle* letter = GetCharRect(text[i]);
		App->renderer->Draw(*fontTexture, (x + size.x * i), y, letter, WHITE);
		i++;
	}
}
