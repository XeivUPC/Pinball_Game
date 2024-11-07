#pragma once
#include "Bumper.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include "Timer.h"
class PoliwagBumper	: public Bumper{
   public:
	   PoliwagBumper(ModuleGame * gameAt, b2Vec2 position, std::vector<b2Vec2> vertices, float restitution, bool flip);
	   ~PoliwagBumper();

	   update_status Update();
	   bool CleanUp() override;

   protected:
	   void OnHit();
	   b2Body* body = nullptr;

   private:
	   Texture* poliwag_texture = nullptr;
	   Animator* poliwag_animator = nullptr;

	   bool hidden = false;
	   bool flip = false;

	   Timer hidden_timer;
	   float hidden_time = 0.5f;
	};

