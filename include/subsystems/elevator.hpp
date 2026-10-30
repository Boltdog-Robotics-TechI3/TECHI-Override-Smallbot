#pragma once
#include "main.h"

enum ElevatorState{
    EL_IDLE,
    EL_SCORING,
    EL_HANDOFF,
    MANUAL
};

void elevatorInit();

void elevatorPeriodic();

void setElevatorState(ElevatorState state);

ElevatorState getElevatorState();