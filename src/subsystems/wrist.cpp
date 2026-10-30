#include "main.h"

WristState wristState = WristState::WR_IDLE, transitionState = WristState::WR_IDLE;
WristMessage wristMessage = WristMessage::NONE;

double const wristIdle = 270, wristStowed = 270, wristIntake = 225, wristHandoff = 270, wristScoring = 180, wristGearRatio = 24.0/36.0;
double wristRoll = 0, wristPitch = 0, leftSetpoint = 0, rightSetpoint = 0; // Defaults for when the robot is initialized


PIDController wristPID(1, 1, 1); // Update PID values

// pros::Task leverTask = pros::Task([]() {
pros::Task wristStateMachine = pros::Task([]() {
    while(1) { 
        //If state can transition, move to transition state when ready. Case checks when ready
        switch(wristState) 
        {
            case WR_IDLE:
                //Angle wrist straight down 
                setPitch(wristIdle);
                break;
            case WR_HANDOFF:
                //Angle at downward angle needed for handoff. if grab piece, go to stowed, else go to idle
                //Handoff is dependent on multiple systems, so this reads state of other systems to do it or robot manages timing
                if (wristMessage == WristMessage::PIECE_GRABBED) {
                    wristState = WristState::STOWED;
                    wristMessage = WristMessage::NONE;
                    break;
                } else if (wristMessage == WristMessage::PIECE_FAILED) {
                    wristState = WristState::WR_IDLE;
                    wristMessage = WristMessage::NONE;
                    break;
                }

                setPitch(wristHandoff);
                break;
            case STOWED:
                //Idle, but claw is holding piece. need to determine orientation of piece when design is finalized.
                //Find pitch and roll
                break;
            case BACKINTAKE:
                //Angle at roughly downward 45 degree angle. if grab piece, go to stowed, else go to idle
                if (wristMessage == WristMessage::PIECE_GRABBED) {
                    wristState = WristState::STOWED;
                    wristMessage = WristMessage::NONE;
                    break;
                } else if (wristMessage == WristMessage::PIECE_FAILED) {
                    wristState = WristState::WR_IDLE;
                    wristMessage = WristMessage::NONE;
                    break;
                }

                setPitch(wristIntake);
                break;
            case FLIPPING:
                //Flip upsidedown. When complete, go to previous state
                if (wristMessage == WristMessage::FLIP_COMPLETE) {
                    wristState = transitionState;
                    wristMessage = WristMessage::NONE;
                    break;
                }
                
                //Find way to use relative form of roll
                setRoll(180);
                break;
            case WR_SCORING:
                //Angle straight out. when score done, go to idle
                //When scoreing is done robot state changes, so robot sets state after scoreing.
                setPitch(wristScoring);
                break;
        }

        pros::delay(20);

    }
});

void wristInit() { wristState = WristState::WR_IDLE; }

void wristPeriodic() {
    if(controller.get_digital_new_press(DIGITAL_A)){
        setPitch(180);
    }
    //Claw state dependent on robot state, so no player input

    //Do movement
    /*
    delta of motor speeds determines how fast wrist rotates on its axis
    linear relation
    0 delta means wrist revolves around motors only
    calculate rotation and revolution speeds with gear ratios
    output degree turned / motor degree turned for revolution
    output degree turned / delta motor degree turned for rotation 
    
    use math to increment roll and pitch vars
    */
   if (wristLeft.get_position() != leftSetpoint) wristLeft.move_velocity(wristPID.calculate(wristLeft.get_position(), leftSetpoint));
   if (wristRight.get_position() != rightSetpoint) wristRight.move_velocity(wristPID.calculate(wristRight.get_position(), rightSetpoint));
}

void setWristState(WristState state) { wristState = state; }

WristState getWristState() { return wristState; }

//0 degree angle is towards robot
void setPitch(double pitch) {
    leftSetpoint = (pitch + (wristRoll / 2.0)) / gearRatio;
    rightSetpoint = (pitch - (wristRoll / 2.0)) / gearRatio;

}

void setRoll(double roll) {
    leftSetpoint = (wristPitch + (roll / 2.0)) / gearRatio;
    rightSetpoint = (wristPitch - (roll / 2.0)) / gearRatio;
}