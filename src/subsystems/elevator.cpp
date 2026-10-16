#include "main.h"
#include "elevator.hpp"

ElevatorState elevatorState = ElevatorState::IDLE;

//Expressed in motor encoder units
double const elevatorBottomHeight = 0, elevatorHandoffHeight = 0;
double scoringElevatorHeight, targetHeight;

pros::Task elevatorStateMachine = pros::Task([]() {
    while(1){
        //Set targetHeight here. Write only
        //Also have logic for state transitions?                        <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        switch (elevatorState)
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
                //Do something                                          <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                break;
        }

        pros::delay(20);
    }
});

//Move elevaotor to bottom height
void elevatorInit()
{
    targetHeight = elevatorBottomHeight;
}

void elevatorPeriodic()
{
    //Remember to update offset values later
    if (controller.get_digital(DIGITAL_UP)) scoringElevatorHeight += 1;
    if (controller.get_digital(DIGITAL_DOWN)) scoringElevatorHeight -= 1;
    
    //targetHeight read only
    double position = elevator_mg.get_position();
    //Does this comparison have an error value?                     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (position != targetHeight)
    {
        //Move with PID                                             <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    }
}

void setElevatorState(ElevatorState state)
{
    //Validate state check, then                                    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    elevatorState = state;
}

ElevatorState getElevatorState()
{
    return elevatorState;
}