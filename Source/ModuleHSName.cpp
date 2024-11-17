#include "ModuleHSName.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"

Rectangle ModuleHSName::GetCharRect(char c, int color)
{
	Rectangle rect = Rectangle{ 0,0,0,0 };
	for (size_t i = 0; i < charReferences.size(); i++)
	{
		if ((int)c == charReferences[i])
		{
			rect.x = i % (int)count.x * size.x;
			rect.y = i / (int)count.x * size.y + 32 * color;
			break;
		}
	}
	rect.width = size.x;
	rect.height = size.y;
	return rect;
}

ModuleHSName::ModuleHSName(Application* app, bool start_enabled) : ModuleText(app, start_enabled)
{}

ModuleHSName::~ModuleHSName()
{}

bool ModuleHSName::Init()
{
	return true;
}

bool ModuleHSName::Start()
{
	App->texture->CreateTexture("Assets/high_score_letters.png", "hs_font_name");
	fontTexture = App->texture->GetTexture("hs_font_name");
	size = Vector2{ 8,16 };
	int widht=0, height=0;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;

	// A to Z
	charReferences.push_back('A');
	charReferences.push_back('B');
	charReferences.push_back('C');
	charReferences.push_back('D');
	charReferences.push_back('E');
	charReferences.push_back('F');
	charReferences.push_back('G');
	charReferences.push_back('H');
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

	// From here on the characters wont match the sprites but this is to make the traversal through all characters easier
	// 0 to 9
	charReferences.push_back(91);
	charReferences.push_back(92);
	charReferences.push_back(93);
	charReferences.push_back(94);
	charReferences.push_back(95);
	charReferences.push_back(96);
	charReferences.push_back(97);
	charReferences.push_back(98);
	charReferences.push_back(99);
	charReferences.push_back(100);
	charReferences.push_back(101);

	// Others
	charReferences.push_back(102);
	charReferences.push_back(103);
	charReferences.push_back(104);
	charReferences.push_back(105);
	charReferences.push_back(106);
	charReferences.push_back(107);
	charReferences.push_back(108);
	charReferences.push_back(109);
	charReferences.push_back(110);

	return true;
}

update_status ModuleHSName::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleHSName::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleHSName::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleHSName::CleanUp()
{
	charReferences.clear();
	return true;
}

void ModuleHSName::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void ModuleHSName::Write(const char* text, int x, int y, int color)
{
	int i = 0;
	while (text[i] != '\0')
	{
		Rectangle letter = GetCharRect(text[i], color);
		App->renderer->Draw(*fontTexture, (int)(x + size.x * i), (int)y, &letter, WHITE);
		i++;
	}
}
