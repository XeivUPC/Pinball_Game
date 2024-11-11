#include "GameUI.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "PokeBall.h"

#include "ModuleGameUIText.h"
#include <sstream>

GameUI::GameUI(ModuleGame* gameAt) : UI(gameAt->App)
{
    this->gameAt = gameAt;

    
    pokeball = gameAt->GetPokeball();
}

GameUI::~GameUI()
{
}

void GameUI::Render() const
{
	EndMode2D();
	App->renderer->DrawRect(0, 134, 160, 10, BLACK);
	App->text_gameUIText->Write(lives_and_pikachus.c_str(), 0, 134);

    long long int points=gameAt->pointsCounter();
	std::string pointsStr = std::to_string(points);
	std::string onlyComasStr = FormatNumberWithOnlyComas(points);

    int xPos = pointsStr.length() * 8;
	App->text_gameUIText->Write(pointsStr.c_str(),160- xPos, 134);
	App->text_gameUIText->Write(onlyComasStr.c_str(),160- xPos, 142);

	BeginMode2D(App->renderer->camera);

}

update_status GameUI::Update()
{
    std::string livesStr = std::to_string(pokeball->GetLivesPokeball());
    std::string pikachusStr = std::to_string(0);//Link to the num of Pikachus

    lives_and_pikachus = "^" + pikachusStr + "  @" + livesStr;

    return UPDATE_CONTINUE;
}

std::string GameUI::FormatNumberWithOnlyComas(long long int number) const
{
    std::string numStr = std::to_string(number);
    std::string result;

    
    for (int i = numStr.length()-1; i > 0 ; i--) {
        if((i)%3 == 0)
            result = result + "`";
        else
            result = result + " " ;
    }

   

    return result;
}
