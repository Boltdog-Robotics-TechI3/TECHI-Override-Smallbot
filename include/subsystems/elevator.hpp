#pragma once
//#include "main.h"

enum elevatorState{
    IDLE,
    SCORING,
    HANDOFF,
    MANUAL
};

void elevatorInit();

void elevatorPeriodic();

void setElevatorState();

elevatorState getElevatorState();