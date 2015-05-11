#pragma once

#include <btBulletDynamicsCommon.h>

btVector3 getViewDirection(float x, float y, float z, float yaw, float pitch);

btVector3 getImpulseVector(btVector3 pointA, btVector3 pointB, btScalar knockBackRatio);

float getDistance(float x1, float y1, float z1, float x2, float y2, float z2);
