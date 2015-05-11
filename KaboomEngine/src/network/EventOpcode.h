#pragma once

enum EventOpcode {
    EVENT_EMPTY = 0,
    EVENT_ASSIGN = 1,
    EVENT_DISCONNECT = 2,
    EVENT_SPAWN = 3,
    EVENT_PICKUP_SPAWN = 4,
    EVENT_DESTROY = 5,
    EVENT_PLAYER_INPUT = 6,
    EVENT_POSITION = 7,
    EVENT_ROTATION = 8,
    EVENT_EXPLOSION = 9,
};
