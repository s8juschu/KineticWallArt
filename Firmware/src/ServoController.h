#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Servo.h>

void setup_servo();
void loop_servo();

void rotate_to(int dest_angle);
void rotate_cw();
void rotate_ccw();
void stop_servo();

#endif