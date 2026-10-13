#pragma once
#include "main.h"

enum IntakeState {
  IDLE,
  INTAKELOW,
  INTAKEHIGH,
  OUTTAKE,
};

void intakeInit();

void intakePeriodic();