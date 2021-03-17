#include "LED.h"

CRGB leds[NUM_LEDS];

void inti_leds(){
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
}

CRGB get_arm(int arm){
    switch(arm){
        case 0:
            return leds[10];
        case 1:
            return leds[5];
        case 2:
            return leds[0];
        case 3:
            return leds[15];
        default:
            return leds[0];
    }
}

void set_arm(int arm, CRGB color){
    FastLED.setBrightness(50);
    int start = 0;
    switch(arm){
        case 0:
            start = 10;
            break;
        case 1:
            start = 5;
            break;
        case 2:
            start = 0;
            break;
        case 3:
            start = 15;
            break;
        default:
            return;
    }
    for(int i = start; i < start+5; i++){
        leds[i] = color;
    }
    FastLED.show();
}

void fade_arm_towards(int arm, CRGB target){
    CRGB curr = get_arm(arm);
    if(target == curr){
        return;
    }
    int new_r = target.r;
    int new_g = target.g;
    int new_b = target.b;
    if(target.r > curr.r){
        new_r = curr.r + FADE_DIFF;
        if(new_r > target.r){
            new_r = target.r;
        }
    } else if(target.r < curr.r){
        new_r = curr.r - FADE_DIFF;
        if(new_r < target.r){
            new_r = target.r;
        }
    }
    if(target.g > curr.g){
        new_g = curr.g + FADE_DIFF;
        if(new_g > target.g){
            new_g = target.g;
        }
    } else if(target.g < curr.g){
        new_g = curr.g - FADE_DIFF;
        if(new_g < target.g){
            new_g = target.g;
        }
    }
    if(target.b > curr.b){
        new_b = curr.b + FADE_DIFF;
        if(new_b > target.b){
            new_b = target.b;
        }
    } else if(target.b < curr.b){
        new_b = curr.b - FADE_DIFF;
        if(new_b < target.b){
            new_b = target.b;
        }
    }
    set_arm(arm, CRGB(new_r, new_g, new_b));
}

void fade_off(int arm){
    int start = 0;
    switch(arm){
        case 0:
            start = 10;
            break;
        case 1:
            start = 5;
            break;
        case 2:
            start = 0;
            break;
        case 3:
            start = 15;
            break;
        default:
            return;
    }
    for(int i = start; i < start+5; i++){
        leds[i].fadeToBlackBy(255);
    }
    FastLED.show();
}

void set_color(CRGB color){
    FastLED.setBrightness(50);
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = color;
    }
    FastLED.show();
}