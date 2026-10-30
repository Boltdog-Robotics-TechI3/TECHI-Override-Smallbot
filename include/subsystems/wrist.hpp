#pragma once
#include "main.h"

enum WristState {
    WR_IDLE,
    WR_HANDOFF,
    STOWED,
    BACKINTAKE,
    FLIPPING,
    WR_SCORING
};

enum WristMessage {
    NONE,
    PIECE_GRABBED,
    PIECE_FAILED,
    FLIP_COMPLETE
};

void wristInit();

void wristPeriodic();

void setWristState(WristState state);

WristState getWristState();

void setPitch(double pitch);

void setRoll(double roll);