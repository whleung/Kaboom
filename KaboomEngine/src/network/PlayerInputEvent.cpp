#include "PlayerInputEvent.h"

PlayerInputEvent::PlayerInputEvent(bool movingForward,
    bool movingBackward,
    bool movingLeft,
    bool movingRight,
    bool jumping,
    bool firing,
    float yaw,
    float pitch) :
    movingForward(movingForward),
    movingBackward(movingBackward),
    movingLeft(movingLeft),
    movingRight(movingRight),
    jumping(jumping),
    firing(firing),
    yaw(yaw),
    pitch(pitch) {
}

PlayerInputEvent::~PlayerInputEvent() {
}


const bool &PlayerInputEvent::getMovingForward() const {
    return movingForward;
}

const bool &PlayerInputEvent::getMovingBackward() const {
    return movingBackward;
}

const bool &PlayerInputEvent::getMovingLeft() const {
    return movingLeft;
}

const bool &PlayerInputEvent::getMovingRight() const {
    return movingRight;
}

const bool &PlayerInputEvent::getJumping() const {
    return jumping;
}

const bool &PlayerInputEvent::getFiring() const {
    return firing;
}

const float &PlayerInputEvent::getYaw() const {
    return yaw;
}

const float &PlayerInputEvent::getPitch() const {
    return pitch;
}
