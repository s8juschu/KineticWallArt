#include "ServoController.h"

const int SPEED = 12;
const int HOMEING_SPEED = 20;
const double MS_PER_DEGREE_CCW = 14.2;
const double MS_PER_DEGREE_CW = 10.25;

Servo myservo;
int curr_angle;
int lastTriggerState = 0;

void home();

void rotate_by(int x){
    if(x < 0){
        //rotate CCW
        myservo.write(90+SPEED);
        delay(round(abs(x)*MS_PER_DEGREE_CCW));
    } else {
        myservo.write(90-SPEED);
        delay(round(abs(x)*MS_PER_DEGREE_CW));
    }
    myservo.write(90);
}

void rotate_to(int dest_angle){
    int angle_diff = abs(dest_angle - curr_angle);
    int residual_angle = 360 - angle_diff;
    if(angle_diff < residual_angle){
        if(dest_angle < curr_angle){
            rotate_by(-angle_diff);
        }else if (dest_angle > curr_angle){
            rotate_by(angle_diff);
        }
    } else {
        if(dest_angle > curr_angle){
            rotate_by(-residual_angle);
        }else if (dest_angle < curr_angle) {
            rotate_by(residual_angle);
        }
    }
    curr_angle = dest_angle;
}

void setup_servo(){
    myservo.attach(D3);
    delay(500);
    myservo.write(90);
    curr_angle = 0;

    //attach switch
    pinMode(D7, INPUT);
    digitalWrite(D7, HIGH);

    // Home Cross
    home();

    // rotate_to(90);
    // delay(2000);
    // rotate_to(0);
    // delay(2000);
    // rotate_to(270);
    // delay(2000);
    // rotate_to(0);
    // delay(2000);
    // rotate_to(180);
    // delay(2000);
    // rotate_to(0);
}

void rotate_cw(){
    myservo.write(85);
}

void rotate_ccw(){
    myservo.write(100);
}

void stop_servo(){
    myservo.write(90);
}

void home(){
    Serial.println("Start homing sequence...");
    if(digitalRead(D7)){
        myservo.write(90+SPEED);
    }
    while(digitalRead(D7)){
        // Poll for home switch
        delay(100);
    }
    Serial.println("hit switch! slowly trying again...");
    // Rotate back and home slowly
    delay(500);
    myservo.write(82);
    while(digitalRead(D7)){
        // Poll for home switch
        delay(10);
    }
    myservo.write(90);
    Serial.println("Homing sequence completed!");
}

void switch_triggered(){
    Serial.println("++ trigger ++");
}

void loop_servo(){
    int currentTriggerState = digitalRead(D7);
    if(!currentTriggerState && lastTriggerState)
        switch_triggered();
    lastTriggerState = currentTriggerState;
}