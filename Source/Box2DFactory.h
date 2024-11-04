#pragma once

#pragma once
#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)

class Box2DFactory //factory Box2DFactory --> PhysicsFactory
{
public:
	static Box2DFactory& GetInstance();
	
	b2Body* CreateCircle(b2World* world, b2Vec2 position,float radius, b2FixtureUserData userData = b2FixtureUserData());
	b2Body* CreateBox(b2World* world, b2Vec2 position, float width, float height, b2FixtureUserData userData = b2FixtureUserData());
	b2Body* CreateBevelBox(b2World* world, b2Vec2 position, float width, float height, float bevelSize, b2FixtureUserData userData = b2FixtureUserData());
	b2Body* CreateCapsule(b2World* world, b2Vec2 position, float width, float height, float radius, b2FixtureUserData userData = b2FixtureUserData());

	b2Fixture* AddCircle(b2Body* bodyToAddTo, b2Vec2 offset, float radius, b2FixtureUserData userData = b2FixtureUserData());
	b2Fixture* AddBox(b2Body* bodyToAddTo, b2Vec2 offset, float width, float height, b2FixtureUserData userData = b2FixtureUserData());


private:
	Box2DFactory();

	// Delete copy constructor and assignment operator to prevent copying
	Box2DFactory(const Box2DFactory&) = delete;
	Box2DFactory& operator=(const Box2DFactory&) = delete;


	b2CircleShape CreateCircleShape(float radius, b2Vec2 offset = b2Vec2_zero);
	b2PolygonShape CreateBoxShape(float width, float height, b2Vec2 offset = b2Vec2_zero);
};

