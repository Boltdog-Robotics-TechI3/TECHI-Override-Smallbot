#include "main.h"

ElevatorState state = ElevatorState::IDLE;

//Expressed in motor encoder units
double elevatorBottomHeight = 0;
double elevatorHandoffHeight = 0;
double scoringElevatorHeight = 0;
double targetHeight;

pros::Task elevatorStateMachine = pros::Task([]() {
    while(1){
        //Set targetHeight here. Write only
        switch (state)
        {
            case IDLE:
                //Go to bottom and hold
                targetHeight = 0;
                break;
            case SCORING:
                //Go to score height and hold
                targetHeight = scoringElevatorHeight;
                break;
            case HANDOFF:
                //Go to handoff height and hold
                targetHeight = elevatorHandoffHeight;
                break;
            case MANUAL:
                //Override height
                //Do something
                break;
        }

        pros::delay(20);
    }
});

void elevatorPeriodic()
{
    if (controller.get_digital(DIGITAL_UP)) scoringElevatorHeight += 1;
    if (controller.get_digital(DIGITAL_DOWN)) scoringElevatorHeight -= 1;
    
    //targetHeight read only
    double position = elevator_mg.get_position();
    if (position != targetHeight)
    {
        //move with PID
    }
}