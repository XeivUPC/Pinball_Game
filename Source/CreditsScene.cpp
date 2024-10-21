#include "CreditsScene.h"

void CreditsScene::Update()
{
	delay.Start();

	int opacity = 255;

	if (delay.ReadSec() < 3)
	{
		DrawRectangle(0, 0, Window_Height, Window_width, WHITE);
	}
	else if (delay.ReadSec() < 6) {

		DrawTexture(texture_credits, 0, 0, WHITE);
	}
	else if(delay.ReadSec() < 9){
		
		DrawTexture(texture_credits, 0, 0, {255,255,255,opacity});
		opacity--;
	}
	else {
		//Game
	}
	
}
