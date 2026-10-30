#pragma once
#include "main.h"

enum IntakeState {
  IN_IDLE,
  INTAKELOW,
  INTAKEHIGH,
  OUTTAKE,
};

void intakeInit();

void intakePeriodic();