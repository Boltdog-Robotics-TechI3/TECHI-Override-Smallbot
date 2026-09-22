//chat ;-;
#include "main.h"

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