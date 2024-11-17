#include "ModuleTimerUIText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"


Rectangle ModuleTimerUIText::GetCharRect(char c)
{
	Rectangle rect =  Rectangle{ 0,0,0,0 };
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

ModuleTimerUIText::ModuleTimerUIText(Application* app, bool start_enabled) : ModuleText(app, start_enabled)
{
}

ModuleTimerUIText::~ModuleTimerUIText()
{
}

bool ModuleTimerUIText::Init()
{
	return true;
}

bool ModuleTimerUIText::Start()
{
	App->texture->CreateTexture("Assets/timer_numbers.png", "timer_numbers");
	fontTexture = App->texture->GetTexture("timer_numbers");
	size = Vector2{ 8,16 };
	int widht = 0, height = 0;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;
	charReferences.push_back(':');
	charReferences.push_back('0');
	charReferences.push_back('1');
	charReferences.push_back('2');
	charReferences.push_back('3');
	charReferences.push_back('4');
	charReferences.push_back('5');
	charReferences.push_back('6');
	charReferences.push_back('7');
	charReferences.push_back('8');
	charReferences.push_back('9');

	return true;
}


bool ModuleTimerUIText::CleanUp()
{
	charReferences.clear();
	return true;
}


void ModuleTimerUIText::Write(const char* text, int x, int y)
{
	int i = 0;
	while (text[i] != '\0')
	{
		Rectangle letter = GetCharRect(text[i]);
		App->renderer->Draw(*fontTexture, (int)(x + size.x * i), (int)y, &letter, WHITE);
		i++;
	}
}
