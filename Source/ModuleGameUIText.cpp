#include "ModuleGameUIText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"


Rectangle ModuleGameUIText::GetCharRect(char c)
{
	Rectangle rect = Rectangle{ 0,0,0,0 };
	for (size_t i = 0; i < charReferences.size(); i++)
	{
		if ((int)c == charReferences[i])
		{
			rect.x = i % (int)count.x * size.x;
			rect.y = i / (int)count.x * size.y;
			break;
		}
	}
	rect.width = size.x;
	rect.height = size.y;
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
	int widht=0, height=0;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;
	charReferences.push_back('A');
charReferences.push_back('B');
charReferences.push_back('C');
charReferences.push_back('D');
charReferences.push_back('E');
charReferences.push_back('F');
charReferences.push_back('G');
charReferences.push_back('H');
charReferences.push_back('I');
charReferences.push_back('J');
charReferences.push_back('K');
charReferences.push_back('L');
charReferences.push_back('M');
charReferences.push_back('N');
charReferences.push_back('O');
charReferences.push_back('P');
charReferences.push_back('Q');
charReferences.push_back('R');
charReferences.push_back('S');
charReferences.push_back('T');
charReferences.push_back('U');
charReferences.push_back('V');
charReferences.push_back('W');
charReferences.push_back('X');
charReferences.push_back('Y');
charReferences.push_back('Z');
charReferences.push_back('ë'); // 234
charReferences.push_back('\''); // 39
charReferences.push_back('.'); // 46
charReferences.push_back(':'); // 58
charReferences.push_back('!'); // 33
charReferences.push_back('/'); // 47

charReferences.push_back(0xA8C0); // 2640
charReferences.push_back(0xA8C2); // 2642

charReferences.push_back('Á'); // 181
charReferences.push_back('À'); // 183

charReferences.push_back('È'); // 212
charReferences.push_back('É'); // 201

charReferences.push_back('Í'); // 214
charReferences.push_back('Ì'); // 205

charReferences.push_back('Ñ'); // 165
charReferences.push_back('Ö'); // 153
charReferences.push_back('Ó'); // 224

charReferences.push_back('Ü'); // 154
charReferences.push_back('Ú'); // 233

charReferences.push_back('-'); // 45
charReferences.push_back('­¡'); // 173 (no visible character)

charReferences.push_back('0'); // 48
charReferences.push_back('1'); // 49
charReferences.push_back('2'); // 50
charReferences.push_back('3'); // 51
charReferences.push_back('4'); // 52
charReferences.push_back('5'); // 53
charReferences.push_back('6'); // 54
charReferences.push_back('7'); // 55
charReferences.push_back('8'); // 56
charReferences.push_back('9'); // 57

charReferences.push_back('`'); // 96
charReferences.push_back('\''); // 39

charReferences.push_back(0x2228); // 2192
charReferences.push_back(0x2229); // 2193
charReferences.push_back(0x2227); // 2191
charReferences.push_back('*'); // 2605
charReferences.push_back('x'); // 158
charReferences.push_back('^'); // 94
charReferences.push_back('¬'); // 197
charReferences.push_back('@'); // 64
charReferences.push_back(' '); // 32




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
		Rectangle letter = GetCharRect(text[i]);
		App->renderer->Draw(*fontTexture, (int)(x + size.x * i), (int)y, &letter, WHITE);
		i++;
	}
}
