#include "GameUI.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleGameUIText.h"
#include <sstream>

GameUI::GameUI(Application* App) : UI(App)
{
}

GameUI::~GameUI()
{
}

void GameUI::Render() const
{
	EndMode2D();
	App->renderer->DrawRect(0, 134, 160, 10, BLACK);
	App->text_gameUIText->Write("^0  @3", 0, 134);

    long long int points=384738798937LL;
	std::string pointsStr = std::to_string(points);
	std::string onlyComasStr = FormatNumberWithOnlyComas(points);

    int xPos = pointsStr.length() * 8;
	App->text_gameUIText->Write(pointsStr.c_str(),160- xPos, 134);
	App->text_gameUIText->Write(onlyComasStr.c_str(),160- xPos, 142);

	BeginMode2D(App->renderer->camera);

}

std::string GameUI::FormatNumberWithOnlyComas(int number) const
{
    std::string numStr = std::to_string(number);
    std::string result;

    
    for (int i = 0; i < numStr.length()-1; i++) {
        if((i+1)%3 == 0)
            result = result + "`";
        else
            result = result + " " ;
    }

   

    return result;
}
