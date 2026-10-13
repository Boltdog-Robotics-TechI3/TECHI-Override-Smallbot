#pragma once
#include "main.h"

enum wristStates {
    IDLE,
    HANDOFF,
    STOWED,
    BACKINTAKE,
    FLIPPING,
    SCORING
}

void wristInit();

void wristPeriodic();