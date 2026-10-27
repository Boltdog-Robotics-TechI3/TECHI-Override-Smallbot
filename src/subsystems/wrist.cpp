#include "main.h"

WristState wristState = WristState::IDLE;

double const wristIdle = 0, wristStowed = 0, wristIntake = 0, wristHandoff = 0, wristScoring = 0, 

// pros::Task leverTask = pros::Task([]() {
pros::Task wristStateMachine = pros::Task([]() {
    while(1) { 
        switch(WristState) 
        {
            case IDLE:

                break;
            case HANDOFF:
                
                break;
            case STOWED:
                
                break;
            case BACKINTAKE:
                
                break;
            case FLIPPING:
                
                break;
            case SCORING:

                break;
        }

        pros::delay(20);

    }
});

void wristInit() { wristState = WristState::IDLE; }

void wristPeriodic() {

}

void setWristState(WristState state) { wristState = state; }

WristState getWristState() { return wristState; }