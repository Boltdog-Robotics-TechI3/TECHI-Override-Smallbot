#include "main.h"

elevatorState state = elevatorState::IDLE;
int scoringElevatorHeight = 0;

void elevatorPeriodic()
{
    if (controller.get_digital(DIGITAL_UP)) scoringElevatorHeight += 1;
    if (controller.get_digital(DIGITAL_DOWN)) scoringElevatorHeight -= 1;
    
    
    
    
    
    //Make task
    switch (state)
    {
        case IDLE:
            break;
        case SCORING:
            break;
        case HANDOFF:
            break;
        case MANUAL:
            break;
    }
}