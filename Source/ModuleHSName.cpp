#include "ModuleHSName.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"

Rectangle* ModuleHSName::GetCharRect(char c, int color)
{
	Rectangle* rect = new Rectangle{ 0,0,0,0 };
	for (int i = 0; i < charReferences.size(); i++)
	{
		if ((int)c == charReferences[i])
		{
			rect->x = i % (int)count.x * size.x;
			rect->y = i / (int)count.x * size.y + 32 * color;
			break;
		}
	}
	rect->width = size.x;
	rect->height = size.y;
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
	int widht, height;
	count.x = fontTexture->width / size.x;
	count.y = fontTexture->height / size.y;

	// A to Z
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
	charReferences.push_back(80);
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

	// From here on the characters wont match the sprites but this is to make the traversal through all characters easier
	// 0 to 9
	charReferences.push_back(91);
	charReferences.push_back(92);
	charReferences.push_back(93);
	charReferences.push_back(94);
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
	charReferences.push_back(111);

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
		Rectangle* letter = GetCharRect(text[i], color);
		App->renderer->Draw(*fontTexture, (x + size.x * i), y, letter, WHITE);
		i++;
	}
}
