#include "CollisionSensor.h"


CollisionSensor::CollisionSensor()
{

}

CollisionSensor::~CollisionSensor()
{
    bodiesColliding.clear();
}

void CollisionSensor::SetBodyToTrack(b2Fixture* bodyToTrack)
{
    this->bodyToTrack = bodyToTrack;
}

bool CollisionSensor::IsBeingTriggered()
{
    return bodiesInside!=0;
}

void CollisionSensor::AcceptOnlyTriggers(bool acceptOnlyTriggers)
{
    onlyTriggers = acceptOnlyTriggers;
}

bool CollisionSensor::OnTriggerEnter()
{
    if (lastBodyEnter != nullptr) {
        lastBodyEnter = nullptr;
        return true;
    }
    return false;
}

bool CollisionSensor::OnTriggerExit()
{
    if (lastBodyExit != nullptr) {
        lastBodyExit = nullptr;
        return true;
    }
    return nullptr;
}

b2Body* CollisionSensor::OnTriggerEnterGet()
{
    if (lastBodyEnter != nullptr) {
        b2Body* aux = lastBodyEnter;
        lastBodyEnter = nullptr;
        return aux;
    }
    return false;
}

b2Body* CollisionSensor::OnTriggerExitGet()
{
    if (lastBodyExit != nullptr) {
        b2Body* aux = lastBodyExit;
        lastBodyExit = nullptr;
        return aux;
    }
    return nullptr;
}


void CollisionSensor::BeginContact(b2Contact* contact)
{
    // Get the two fixtures involved in the contact
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    // Check if the tracked body is involved
    if (fixtureA == bodyToTrack || fixtureB == bodyToTrack) {
        // Determine which fixture is the sensor (if any)
        if (!onlyTriggers || fixtureA->IsSensor() || fixtureB->IsSensor()) {
            bodiesInside++;
            b2Body* bodyA = fixtureA->GetBody();
            b2Body* bodyB = fixtureB->GetBody();
            lastBodyEnter = GetDifferentBody(bodyA, bodyB, bodyToTrack->GetBody());
            bodiesColliding.emplace(lastBodyEnter);
        }
    }
}

void CollisionSensor::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    // Check if the tracked body is involved
    if (fixtureA == bodyToTrack || fixtureB == bodyToTrack) {
        // Determine which fixture is the sensor (if any)
        if (!onlyTriggers || fixtureA->IsSensor() || fixtureB->IsSensor()) {
            bodiesInside--;
            b2Body* bodyA = fixtureA->GetBody();
            b2Body* bodyB = fixtureB->GetBody();
            lastBodyExit = GetDifferentBody(bodyA, bodyB, bodyToTrack->GetBody());
            bodiesColliding.erase(lastBodyEnter);
        }
    }
}

std::set<b2Body*> CollisionSensor::GetBodiesColliding()
{
    return bodiesColliding;
}

b2Body* CollisionSensor::GetDifferentBody(b2Body* body1, b2Body* body2, b2Body* bodyToBeDifferentFrom)
{
    if (body1 != bodyToBeDifferentFrom)
        return body1;
    return body2;
}


