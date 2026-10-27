#pragma once
#include "main.h"

enum WristState {
    IDLE,
    HANDOFF,
    STOWED,
    BACKINTAKE,
    FLIPPING,
    SCORING
};

void wristInit();

void wristPeriodic();

void setWristState(WristState state);

WristState getWristState();