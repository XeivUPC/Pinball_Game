#pragma once
#include <vector>
#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)

class CollisionSensor;

class CollisionsManager : public b2ContactListener {
public:
    CollisionsManager();
    ~CollisionsManager(); 

private:

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact)override;
};
