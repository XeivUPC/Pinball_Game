#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleWindow.h"

Box2DFactory::Box2DFactory()
{
}

Box2DFactory& Box2DFactory::GetInstance() {
	static Box2DFactory instance; // Guaranteed to be destroyed and instantiated on first use
	return instance;
}

b2Body* Box2DFactory::CreateCircle(b2World* world, b2Vec2 position, float radius, b2FixtureUserData userData)
{
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape = CreateCircleShape(radius);

	b2FixtureDef circleFixtureDef;
	circleFixtureDef.shape = &circleShape;
	circleFixtureDef.userData = userData;
	circleFixtureDef.density = 1.0f;
	circleFixtureDef.friction = 0.3f;
	body->CreateFixture(&circleFixtureDef);

	return body;
}

b2Body* Box2DFactory::CreateBox(b2World* world, b2Vec2 position, float width, float height, b2FixtureUserData userData)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape = CreateBoxShape(width, height);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.userData = userData;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.friction = 0.3f;
	body->CreateFixture(&boxFixtureDef);

	return body;
}

b2Body* Box2DFactory::CreateBevelBox(b2World* world, b2Vec2 position, float width, float height, float bevelSize, b2FixtureUserData userData)
{
	std::vector<b2Vec2> vertices;

	// Calculate half dimensions
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = world->CreateBody(&bodyDef);

	// Define vertices for the beveled box
	vertices.push_back(b2Vec2(-halfWidth + bevelSize, -halfHeight));
	vertices.push_back(b2Vec2(halfWidth - bevelSize, -halfHeight));
	vertices.push_back(b2Vec2(halfWidth, -halfHeight + bevelSize));
	vertices.push_back(b2Vec2(halfWidth, halfHeight - bevelSize));
	vertices.push_back(b2Vec2(halfWidth - bevelSize, halfHeight));
	vertices.push_back(b2Vec2(-halfWidth + bevelSize, halfHeight));
	vertices.push_back(b2Vec2(-halfWidth, halfHeight - bevelSize));
	vertices.push_back(b2Vec2(-halfWidth, -halfHeight + bevelSize));

	// Create the polygon shape
	b2PolygonShape beveledBox;
	beveledBox.Set(&vertices[0], vertices.size());

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.userData = userData;
	boxFixtureDef.shape = &beveledBox;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.friction = 0.3f;
	body->CreateFixture(&boxFixtureDef);

	return body;
}

b2Body* Box2DFactory::CreateCapsule(b2World* world, b2Vec2 position, float width, float height, float radius, b2FixtureUserData userData)
{
	float rectangleHeight = height - 2 * radius; // Adjust height to accommodate the circle ends

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape = CreateCircleShape(radius);
	b2PolygonShape boxShape = CreateBoxShape(width, rectangleHeight);

	// Create the rectangle fixture
	b2FixtureDef rectangleFixtureDef;
	rectangleFixtureDef.shape = &boxShape;
	rectangleFixtureDef.userData = userData;
	rectangleFixtureDef.density = 1.0f;
	rectangleFixtureDef.friction = 0.3f;

	body->CreateFixture(&rectangleFixtureDef);

	// Top circle
	b2FixtureDef topCircleFixtureDef;
	topCircleFixtureDef.shape = &circleShape;
	topCircleFixtureDef.density = 1.0f;
	topCircleFixtureDef.friction = 0.3f;
	circleShape.m_p.Set(0, rectangleHeight / 2.0f); // Move the circle to the top
	body->CreateFixture(&topCircleFixtureDef);

	// Bottom circle
	b2FixtureDef bottomCircleFixtureDef;
	bottomCircleFixtureDef.shape = &circleShape;
	bottomCircleFixtureDef.density = 1.0f;
	bottomCircleFixtureDef.friction = 0.3f;
	circleShape.m_p.Set(0, -rectangleHeight / 2.0f); // Move the circle to the bottom
	body->CreateFixture(&bottomCircleFixtureDef);

	return body;

}

b2Fixture* Box2DFactory::AddCircle(b2Body* bodyToAddTo, b2Vec2 offset, float radius, b2FixtureUserData userData)
{
	b2CircleShape circleShape = CreateCircleShape(radius, offset);

	b2FixtureDef circleFixtureDef;
	circleFixtureDef.shape = &circleShape;
	circleFixtureDef.density = 1.0f;
	circleFixtureDef.userData = userData;
	circleFixtureDef.friction = 0.3f;


	return bodyToAddTo->CreateFixture(&circleFixtureDef);
}

b2Fixture* Box2DFactory::AddBox(b2Body* bodyToAddTo, b2Vec2 offset, float width, float height, b2FixtureUserData userData)
{

	b2PolygonShape boxShape = CreateBoxShape(width, height, offset);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.userData = userData;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.friction = 0.3f;

	return bodyToAddTo->CreateFixture(&boxFixtureDef);

}



b2CircleShape Box2DFactory::CreateCircleShape(float radius, b2Vec2 offset)
{
	b2CircleShape circle;
	circle.m_radius = radius;
	circle.m_p.Set(offset.x, offset.y);
	return circle;
}

b2PolygonShape Box2DFactory::CreateBoxShape(float width, float height, b2Vec2 offset)
{
	b2PolygonShape rectangle;
	rectangle.SetAsBox(width / 2.0f, height / 2.0f,offset,0);
	return rectangle;
}
