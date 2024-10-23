#include "ModuleHSNum.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"

Rectangle* ModuleHSNum::GetCharRect(char c, int color, bool coma)
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
	App->texture->CreateTexture("Assets/high_score_letters.png", "hs_font_name");
	fontTexture = App->texture->GetTexture("hs_font_name");
	size = Vector2{ 8,16 };
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
	charReferences.push_back(97);
	charReferences.push_back(98);
	charReferences.push_back(99);
	charReferences.push_back(100);
	charReferences.push_back(101);
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
	charReferences.push_back(112);
	charReferences.push_back(113);
	charReferences.push_back(114);
	charReferences.push_back(115);
	charReferences.push_back(116);
	charReferences.push_back(117);
	charReferences.push_back(118);
	charReferences.push_back(119);
	charReferences.push_back(120);
	charReferences.push_back(121);
	charReferences.push_back(122);
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
	charReferences.push_back(46);
	charReferences.push_back(58);
	charReferences.push_back(44);
	charReferences.push_back(59);
	charReferences.push_back(40);
	charReferences.push_back(42);
	charReferences.push_back(33);
	charReferences.push_back(63);
	charReferences.push_back(32);
	charReferences.push_back(41);
	charReferences.push_back(35);
	charReferences.push_back(36);
	charReferences.push_back(37);
	charReferences.push_back(38);
	charReferences.push_back(45);
	charReferences.push_back(43);
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

void ModuleHSNum::Write(const char* text, int x, int y, int color, bool coma)
{
	int i = 0;
	while (text[i] != '\0')
	{
		Rectangle* letter = GetCharRect(text[i], color, coma);
		App->renderer->Draw(*fontTexture, (x + size.x * i), y, letter, WHITE);
		i++;
	}
}
