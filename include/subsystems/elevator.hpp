#pragma once
//#include "main.h"

enum ElevatorState{
    IDLE,
    SCORING,
    HANDOFF,
    MANUAL
};

void elevatorInit();

void elevatorPeriodic();

void setElevatorState(ElevatorState state);

ElevatorState getElevatorState();