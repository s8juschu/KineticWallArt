#ifndef LED_H
#define LED_H

#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN D6
#define FADE_DIFF 5

void inti_leds();
CRGB get_arm(int arm);
void set_arm(int arm, CRGB color);
void fade_arm_towards(int arm, CRGB target);
void fade_off(int arm);
void set_color(CRGB color);

#endif