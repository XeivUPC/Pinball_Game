#pragma once
#include <vector>
#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)

class CollisionSensor;

class CollisionsManager : public b2ContactListener {
public:
    static CollisionsManager& GetInstance();


private:

    CollisionsManager();
    ~CollisionsManager(); 

    // Delete copy constructor and assignment operator to prevent copying
    CollisionsManager(const CollisionsManager&) = delete;
    CollisionsManager& operator=(const CollisionsManager&) = delete;

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact)override;
};
