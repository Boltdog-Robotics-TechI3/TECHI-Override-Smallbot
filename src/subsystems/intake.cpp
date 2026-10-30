//chat ;-;
#include "main.h"

IntakeState intakeState = IntakeState::IN_IDLE;

pros::Task intakeStateMachine = pros::Task([]() {
    while(1) {
        switch (intakeState) {
            case IN_IDLE:
                intake.move(0);
                if (intakeLift.is_extended()) {
                    intakeLift.retract();
                }
                break;
            case INTAKELOW:
                intake.move(100);
                if (intakeLift.is_extended()) {
                    intakeLift.retract();
                }
                break;
            case INTAKEHIGH:
                intake.move(100);
                if (!intakeLift.is_extended()) {
                    intakeLift.extend();
                }
                break;
            case OUTTAKE:
                intake.move(-100);
                if (intakeLift.is_extended()) {
                    intakeLift.retract();
                }
                break;
        }

        pros::delay(20);
    }
});

void intakeInit() {
    intake.set_brake_mode(MOTOR_BRAKE_COAST);
}

void intakePeriodic() {
    if(controller.get_digital_new_press(DIGITAL_A)){
        intake.move(127);
    } else {
        intake.move(0);
    }

    if (controller.get_digital_new_press(DIGITAL_B)){
        intakeLift.toggle();
    }
}