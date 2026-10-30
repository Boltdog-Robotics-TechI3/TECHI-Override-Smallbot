#include "main.h"

ElevatorState elevatorState = ElevatorState::EL_IDLE;

//Expressed in motor encoder units
double const elevatorBottomHeight = 0, elevatorHandoffHeight = 0, elevatorTopHeight = 10000000; //Update        <<<<<<<<<<<<<<
double scoringElevatorHeight, targetHeight;

PIDController elevatorPID(1, 1, 1); //Update PID values               <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

pros::Task elevatorStateMachine = pros::Task([]() {
    while(1){
        //Set targetHeight here. Write only
        switch (elevatorState)
        {
            case WR_IDLE:
                //Go to bottom and hold
                targetHeight = elevatorBottomHeight;
                break;
            case WR_SCORING:
                //Go to score height and hold
                targetHeight = scoringElevatorHeight;
                break;
            case WR_HANDOFF:
                //Go to handoff height and hold
                targetHeight = elevatorHandoffHeight;
                break;
            case MANUAL:
                //Override height
                targetHeight += 1 * controller.get_analog(ANALOG_LEFT_Y); //Tune      <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                std::clamp(targetHeight, elevatorBottomHeight, elevatorTopHeight);
                break;
        }

        pros::delay(20);
    }
});

//Start elevaotor at bottom height
void elevatorInit() { elevatorState = ElevatorState::EL_IDLE; }

void elevatorPeriodic()
{
    //Remember to update offset values later                 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (controller.get_digital(DIGITAL_UP)) scoringElevatorHeight += 1;
    if (controller.get_digital(DIGITAL_DOWN)) scoringElevatorHeight -= 1;
    
    //targetHeight read only
    //Does this comparison have an error range?                     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    double position = elevator_mg.get_position();
    if (position != targetHeight) { elevator_mg.move_velocity(elevatorPID.calculate(position, targetHeight)); }
}

void setElevatorState(ElevatorState state) { elevatorState = state; }

ElevatorState getElevatorState() { return elevatorState; }