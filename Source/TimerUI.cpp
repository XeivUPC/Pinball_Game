#include "TimerUI.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include "ModuleTimerUIText.h"
#include <sstream>
#include <iomanip>

TimerUI::TimerUI(ModuleGame* gameAt) : UI(gameAt->App)
{
    this->gameAt = gameAt;

}

TimerUI::~TimerUI()
{
}

void TimerUI::Render()
{
    ModuleGame::GameStates state = gameAt->GetState();

    std::string timerStr = FormatTime(timerMinutes, timerSeconds);
    EndMode2D();

    App->text_timerUIText->Write(timerStr.c_str(), 127, 1);
   
    BeginMode2D(App->renderer->camera);
}

update_status TimerUI::Update()
{
    timerMinutes = totalSeconds / 60;
    timerSeconds = totalSeconds % 60;

    if (timerMinutes <= 0 && timerSeconds <= 0) {
        finished = true;
    }

    if (!finished) {

        Render();

        if (secondTimer.ReadSec() >= 1) {
            totalSeconds--;
            secondTimer.Start();
        }
    }


    return UPDATE_CONTINUE;
}

void TimerUI::AddTimer(int seconds)
{
    totalSeconds = seconds;
    finished = false;
    secondTimer.Start();
}

bool TimerUI::IsTimerFinished() const
{
    return finished;
}

std::string TimerUI::FormatTime(int timerMinutes, int timerSeconds) {
    std::ostringstream oss;
    oss << timerMinutes << ":" << std::setw(2) << std::setfill('0') << timerSeconds;
    return oss.str();
}
