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

    textCurrentPos = textInitPos;
}

GameUI::~GameUI()
{
}

void GameUI::Render()
{
    ModuleGame::GameStates state = gameAt->GetState();

    if (!textQueue.empty()) {
        ShowNextText();
    }
    else {
        ShowBasicUI();
    }

	BeginMode2D(App->renderer->camera);
}

update_status GameUI::Update()
{
    Render();

    return UPDATE_CONTINUE;
}

void GameUI::AddText(std::string text)
{
    textQueue.push_back(text);
}

void GameUI::ShowNextText()
{
    showingText = true;
    std::string currentText = textQueue.front();
    EndMode2D();
    App->renderer->DrawRect(0, 134, 160, 10, BLACK);

    std::string textStr = currentText;

    int xPos = textStr.length() * 8;

    if (textCurrentPos < 0 - xPos) {
        textQueue.erase(textQueue.begin());
        textCurrentPos = textInitPos;
        paused = false;
    }
    if (textCurrentPos > (textInitPos - xPos) / 2) {
        textCurrentPos = textCurrentPos - 40 * GetFrameTime();
    }
    else if (textCurrentPos <= (textInitPos - xPos) / 2 && !paused) {
        textPauseTimer.Start();
        paused = true;
    }
    if (textPauseTimer.ReadSec() >= textPauseTime) {
        textCurrentPos = textCurrentPos - 120 * GetFrameTime();
    }
    App->text_gameUIText->Write(currentText.c_str(), (int)textCurrentPos, 134);
}

void GameUI::ShowBasicUI()
{
    std::string livesStr = std::to_string(gameAt->GetPokeball()->GetLivesPokeball());
    std::string pikachusStr = std::to_string(0);//Link to the num of Pikachus

    std::string lives_and_pikachus;
    lives_and_pikachus = "^" + pikachusStr + "  @" + livesStr;

    EndMode2D();
    App->renderer->DrawRect(0, 134, 160, 10, BLACK);

    App->text_gameUIText->Write(lives_and_pikachus.c_str(), 0, 134);

    long long int points = gameAt->pointsCounter();
    std::string pointsStr = std::to_string(points);
    std::string onlyComasStr = FormatNumberWithOnlyComas(points);

    int xPos = pointsStr.length() * 8;
    App->text_gameUIText->Write(pointsStr.c_str(), 160 - xPos, 134);
    App->text_gameUIText->Write(onlyComasStr.c_str(), 160 - xPos, 142);
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
