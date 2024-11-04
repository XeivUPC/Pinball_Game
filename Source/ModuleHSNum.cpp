#include "ModuleHSNum.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"

Rectangle* ModuleHSNum::GetCharRect(char c, int color, int position, bool coma)
{
	Rectangle* rect = new Rectangle{ 0,0,0,0 };
	for (size_t i = 0; i < charReferences.size(); i++)
	{
		if ((int)c == charReferences[i])
		{
			rect->x = i % (int)count.x * size.x + 80 * coma;
			rect->y = i / (int)count.y * size.y + 80 * color + 16 * (position-1);
			break;
		}
	}
	rect->width = size.x;
	rect->height = size.y;
	return rect;
}

ModuleHSNum::ModuleHSNum(Application* app, bool start_enabled) : ModuleText(app, start_enabled)
{}

ModuleHSNum::~ModuleHSNum()
{}

bool ModuleHSNum::Init()
{
	return true;
}

bool ModuleHSNum::Start()
{
	App->texture->CreateTexture("Assets/high_score_nums.png", "hs_font_nums");
	fontTexture = App->texture->GetTexture("hs_font_nums");
	size = Vector2{ 8,16 };
	int widht=0, height =0;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;
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
	return true;
}

update_status ModuleHSNum::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleHSNum::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleHSNum::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleHSNum::CleanUp()
{
	charReferences.clear();
	return true;
}

void ModuleHSNum::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void ModuleHSNum::Write(const char* text, int x, int y, int color, int position)
{
	int i = 0;
	int length = strlen(text);
	bool coma = false;
	while (text[i] != '\0')
	{
		if ((length - i - 1) % 3 == 0 && (length - i - 1) != 0) {
			coma = true;
		}
		Rectangle* letter = GetCharRect(text[i], color, position, coma);
		App->renderer->Draw(*fontTexture, (int)(x + size.x * i), (int)y, letter, WHITE);
		coma = false;
		i++;
	}
}
