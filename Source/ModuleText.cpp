#include "ModuleText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Application.h"

Rectangle* ModuleText::GetCharRect(char c)
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

ModuleText::ModuleText(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleText::~ModuleText()
{}

bool ModuleText::Init()
{
	return true;
}

bool ModuleText::Start()
{
	App->texture->CreateTexture("Assets/Font.png", "font");
	fontTexture = App->texture->GetTexture("font");
	size = Vector2{ 8,8 };
	int widht=0, height=0;
	count.x = fontTexture->width/size.x;
	count.y = fontTexture->height/size.y;
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
	charReferences.push_back('a');
	charReferences.push_back('b');
	charReferences.push_back('c');
	charReferences.push_back('d');
	charReferences.push_back('e');
	charReferences.push_back('f');
	charReferences.push_back('g');
	charReferences.push_back('h');
	charReferences.push_back('i');
	charReferences.push_back('j');
	charReferences.push_back('k');
	charReferences.push_back('l');
	charReferences.push_back('m');
	charReferences.push_back('n');
	charReferences.push_back('o');
	charReferences.push_back('p');
	charReferences.push_back('q');
	charReferences.push_back('r');
	charReferences.push_back('s');
	charReferences.push_back('t');
	charReferences.push_back('u');
	charReferences.push_back('v');
	charReferences.push_back('w');
	charReferences.push_back('x');
	charReferences.push_back('y');
	charReferences.push_back('z');
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
	charReferences.push_back('.'); // 46
	charReferences.push_back(':'); // 58
	charReferences.push_back(','); // 44
	charReferences.push_back(';'); // 59
	charReferences.push_back('('); // 40
	charReferences.push_back('*'); // 42
	charReferences.push_back('!'); // 33
	charReferences.push_back('?'); // 63
	charReferences.push_back(' '); // 32
	charReferences.push_back(')'); // 41
	charReferences.push_back('#'); // 35
	charReferences.push_back('$'); // 36
	charReferences.push_back('%'); // 37
	charReferences.push_back('&'); // 38
	charReferences.push_back('-'); // 45
	charReferences.push_back('+'); // 43

	return true;
}

update_status ModuleText::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleText::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleText::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleText::CleanUp()
{
	charReferences.clear();
	return true;
}

void ModuleText::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void ModuleText::Write(const char* text, int x, int y, Color color)
{
	int i = 0;
	while (text[i] != '\0')
	{
		Rectangle* letter = GetCharRect(text[i]);
		App->renderer->Draw(*fontTexture, (int)(x + size.x * i), (int)y, letter, color);
		i++;
	}
}
