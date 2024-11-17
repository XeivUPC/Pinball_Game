#include "BonusFinalBall.h"
#include "Application.h"
#include "ModuleGameUIText.h"
#include "ModuleUserPreferences.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleHighScore.h"

int BonusFinalBall::GetMultiplier()
{
    return (int)gameAt->bonusPointsCounter.GetMultipliersTotalValue();
}

std::string BonusFinalBall::FormatNumberWithOnlyComas(long long int number) const
{
    std::string numStr = std::to_string(number);
    std::string result;


    for (int i = numStr.length() - 1; i > 0; i--) {
        if ((i) % 3 == 0)
            result = result + "`";
        else
            result = result + " ";
    }

    return result;
}

int BonusFinalBall::getXForCenteredString(std::string line)
{
    return ((160/8 - line.size())/2)*8;
}

int BonusFinalBall::anchorAtRight(std::string line, int x)
{
    return x - 8 * line.size();
}


BonusFinalBall::BonusFinalBall(ModuleGame* gameAt) : UI(gameAt->App)
{
    this->gameAt = gameAt;
    Bonus captures = Bonus{ {"POKEMON CAPTURED", "POKEMON CAPTURED", "POKEMON CAPTURED", "POKEMON CAPTURED", "POKEMON CAPTURED", "POKEMON CAPTURED"}, 0, 500000, true };
    Bonus evolutions = Bonus{ {"POKEMON EVOLVED", "POKEMON EVOLVED", "POKEMON EVOLVED", "POKEMON EVOLVED", "POKEMON EVOLVED", "POKEMON EVOLVED"}, 0, 750000, true };
    Bonus cloyster = Bonus{ {"CLOYSTER", "CLOYSTER", "CLOYSTER", "CLOYSTER", "CLOYSTER", "CLOYSTER"}, 0, 75000, false };
    Bonus slowpoke = Bonus{ {"SLOWPOKE", "SLOWPOKE", "SLOWPOKE", "SLOWPOKE", "SLOWPOKE", "SLOWPOKE"}, 0, 75000, false };
    Bonus bellsprout = Bonus{ {"BELLSPROUT", "BELLSPROUT", "BELLSPROUT", "BELLSPROUT", "BELLSPROUT", "BELLSPROUT"}, 0, 75000, false };
    Bonus poliwag = Bonus{ {"POLIWAG", "POLIWAG", "POLIWAG", "POLIWAG", "POLIWAG", "POLIWAG"}, 0, 50000, false };
    Bonus psyduck = Bonus{ {"PSYDUCK", "PSYDUCK", "PSYDUCK", "PSYDUCK", "PSYDUCK", "PSYDUCK"}, 0, 50000, false };
    Bonus dugtrio = Bonus{ {"DUGTRIO", "DUGTRIO", "DUGTRIO", "DUGTRIO", "DUGTRIO", "DUGTRIO"}, 0, 50000, false };
    Bonus caves = Bonus{ {"CAVE SHOTS", "CAVE SHOTS", "CAVE SHOTS", "CAVE SHOTS", "CAVE SHOTS", "CAVE SHOTS"}, 0, 25000, true };
    Bonus spinner = Bonus{ {"SPINNER TURNS", "SPINNER TURNS", "SPINNER TURNS", "SPINNER TURNS", "SPINNER TURNS", "SPINNER TURNS"}, 0, 100, true };
    BonusesFinalBall.emplace_back(captures);
    BonusesFinalBall.emplace_back(evolutions);
    BonusesFinalBall.emplace_back(cloyster);
    BonusesFinalBall.emplace_back(slowpoke);
    BonusesFinalBall.emplace_back(bellsprout);
    BonusesFinalBall.emplace_back(poliwag);
    BonusesFinalBall.emplace_back(psyduck);
    BonusesFinalBall.emplace_back(dugtrio);
    BonusesFinalBall.emplace_back(caves);
    BonusesFinalBall.emplace_back(spinner);

    selectedLanguage = gameAt->App->userPreferences->GetLanguage();
    enabled = false;
}

BonusFinalBall::~BonusFinalBall()
{
    BonusesFinalBall.clear();
}

bool BonusFinalBall::IsEnded()
{
    return ended;
}

void BonusFinalBall::Activate()
{
    enabled = true;
    scoreAdded = false;
    ended = false;
    timer.Start();
    index = 0;
    subtotalPoints = 0;
    subtotalMultipliedPoints = 0;
    totalPoints = 0;
    offset = 0;
}

void BonusFinalBall::Deactivate()
{
    enabled = false;
    gameAt->pointsCounter.Set(totalPoints);
    for (size_t i = 0; i < BonusesFinalBall.size(); i++)
    {
        BonusesFinalBall.at(i).count = 0;
    }
    subtotalPoints = 0;
    subtotalMultipliedPoints = 0;
    totalPoints = 0;
}

void BonusFinalBall::AddInBonus(int bonusId)
{
    BonusesFinalBall.at(bonusId).count++;
}

void BonusFinalBall::Render()
{
    if(!enabled) return;
    gameAt->App->renderer->DrawRect(0, 232, 160, 48, BLACK);
    
    if(index < (int)BonusesFinalBall.size())
    {
       
        std::string line = std::to_string(BonusesFinalBall.at(index).count);
        line += " ";
        line += BonusesFinalBall.at(index).BonusName.at(selectedLanguage);
        gameAt->App->text_gameUIText->Write(line.c_str(), getXForCenteredString(line), SCREEN_HEIGHT * 2 - 56);
        gameAt->App->text_gameUIText->Write("BONUS", 16, SCREEN_HEIGHT * 2 - 40);
        gameAt->App->text_gameUIText->Write((FormatNumberWithOnlyComas(BonusesFinalBall.at(index).points * BonusesFinalBall.at(index).count)).c_str(), anchorAtRight(FormatNumberWithOnlyComas(BonusesFinalBall.at(index).points * BonusesFinalBall.at(index).count), 144), SCREEN_HEIGHT * 2 - 32);
        gameAt->App->text_gameUIText->Write(std::to_string(BonusesFinalBall.at(index).points * BonusesFinalBall.at(index).count).c_str(), anchorAtRight(std::to_string(BonusesFinalBall.at(index).points * BonusesFinalBall.at(index).count), 152), SCREEN_HEIGHT * 2 - 40);
        gameAt->App->text_gameUIText->Write("SUBTOTAL", 16, SCREEN_HEIGHT * 2 - 24);
        gameAt->App->text_gameUIText->Write(FormatNumberWithOnlyComas(subtotalPoints).c_str(), anchorAtRight(FormatNumberWithOnlyComas(subtotalPoints), 144), SCREEN_HEIGHT * 2 - 16);
        gameAt->App->text_gameUIText->Write(std::to_string(subtotalPoints).c_str(), anchorAtRight(std::to_string(subtotalPoints), 152), SCREEN_HEIGHT * 2 - 24);
    }
    else
    {
        if (index == BonusesFinalBall.size() + 2)
        {
            ended = true;
            Deactivate();
        }
        if (index == BonusesFinalBall.size())
        {
            gameAt->App->text_gameUIText->Write("SUBTOTAL", 16, SCREEN_HEIGHT * 2 - 56);
            gameAt->App->text_gameUIText->Write(FormatNumberWithOnlyComas(subtotalPoints).c_str(), anchorAtRight(FormatNumberWithOnlyComas(subtotalPoints), 144), SCREEN_HEIGHT * 2 - 48);
            gameAt->App->text_gameUIText->Write(std::to_string(subtotalPoints).c_str(), anchorAtRight(std::to_string(subtotalPoints), 152), SCREEN_HEIGHT * 2 - 56);
        }

        gameAt->App->text_gameUIText->Write("MULTIPLIER", 16, (int)(SCREEN_HEIGHT * 2 - 40 - 16 * offset));
        gameAt->App->text_gameUIText->Write(FormatNumberWithOnlyComas(GetMultiplier()).c_str(), anchorAtRight(FormatNumberWithOnlyComas(GetMultiplier()), 144), (int)(SCREEN_HEIGHT * 2 - 32 - 16 * offset));
        gameAt->App->text_gameUIText->Write(std::to_string(GetMultiplier()).c_str(), anchorAtRight(std::to_string(GetMultiplier()), 152), (int)(SCREEN_HEIGHT * 2 - 40 - 16 * offset));

        gameAt->App->text_gameUIText->Write("SUBTOTAL", 16, (int)(SCREEN_HEIGHT * 2 - 24 - 16 * offset));
        gameAt->App->text_gameUIText->Write(FormatNumberWithOnlyComas(subtotalMultipliedPoints).c_str(), anchorAtRight(FormatNumberWithOnlyComas(subtotalMultipliedPoints), 144), (int)(SCREEN_HEIGHT * 2 - 16 - 16 * offset));
        gameAt->App->text_gameUIText->Write(std::to_string(subtotalMultipliedPoints).c_str(), anchorAtRight(std::to_string(subtotalMultipliedPoints), 152), (int)(SCREEN_HEIGHT * 2 - 24 - 16 * offset));

        gameAt->App->text_gameUIText->Write("TOTAL", 16, (int)(SCREEN_HEIGHT * 2 - 8 - 16 * offset));
        gameAt->App->text_gameUIText->Write(FormatNumberWithOnlyComas(totalPoints).c_str(), anchorAtRight(FormatNumberWithOnlyComas(totalPoints), 144), (int)(SCREEN_HEIGHT * 2 - 16 * offset));
        gameAt->App->text_gameUIText->Write(std::to_string(totalPoints).c_str(), anchorAtRight(std::to_string(totalPoints), 152), (int)(SCREEN_HEIGHT * 2 - 8 - 16 * offset));
    }
}

update_status BonusFinalBall::Update()
{
    if (!enabled)return UPDATE_CONTINUE;
    if ((IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT)) || timer.ReadSec() >= 3))
    {
        timer.Start();
        scoreAdded = false;
        index++;
    }
    while (index < (int)BonusesFinalBall.size()-1 && BonusesFinalBall.at(index).count == 0 && !BonusesFinalBall.at(index).appearWhenNull)
        index++;
    if (!scoreAdded && index < (int)BonusesFinalBall.size())
    {
        subtotalPoints += BonusesFinalBall.at(index).count * BonusesFinalBall.at(index).points;
        scoreAdded = true;
    }
    else if (index >= (int)BonusesFinalBall.size() && !scoreAdded)
    {
        subtotalMultipliedPoints = subtotalPoints * GetMultiplier();
        totalPoints = gameAt->pointsCounter() + subtotalMultipliedPoints;
        gameAt->pointsCounter.Set(totalPoints);
        scoreAdded = true;
    }
    if (index == BonusesFinalBall.size() + 1 && offset < 1)
        offset = (float)(2*timer.ReadSec());
    if (offset > 1)
        offset = 1;
    Render();
    
    return UPDATE_CONTINUE;
}
