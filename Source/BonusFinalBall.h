#pragma once
#include "UI.h"
#include "Counter.h"
#include <string>
#include "ModuleGame.h"
#include "Timer.h"

class BonusFinalBall : public UI
{
private:
	struct Bonus
	{
		std::vector<std::string> BonusName;
		int count;
		int points;
		bool appearWhenNull;
	};
	Timer timer;
	Texture* japaneseText = nullptr;
	Texture* worldwideText = nullptr;
	ModuleGame* gameAt = nullptr;
	std::vector<Bonus> BonusesFinalBall;
	int index = 0;
	int selectedLanguage=-1;
	long long int subtotalPoints=0;
	long long int subtotalMultipliedPoints = 0;
	long long int totalPoints = 0;
	bool scoreAdded = false;
	bool ended = false;
	float offset = 0;
	int GetMultiplier();
	std::string FormatNumberWithOnlyComas(long long int number) const;
	int getXForCenteredString(std::string line);
	int anchorAtRight(std::string line, int x);
public:
	BonusFinalBall(ModuleGame* gameAt);
	~BonusFinalBall();
	bool IsEnded();
	void Activate();
	void Deactivate();
	void AddInBonus(int bonusId);
	void Render();
	update_status Update();
};