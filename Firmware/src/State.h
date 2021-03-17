#ifndef STATE_H
#define STATE_H

#include <FastLED.h>

enum StateChange {
    COLOR_0,
    COLOR_1,
    COLOR_2,
    COLOR_3,
    ON_0,
    ON_1,
    ON_2,
    ON_3,
    ANGLE
};

typedef void (*state_observer) (StateChange);

class State {
    public:
        State():
            colors{CRGB(0,0,0)},
            on{true, true, true, true}
         {
            angle = 0;
            in_obsrv = NULL;
            out_obsrv = NULL;
        }
        // arm: 0-3 index of the arm
        // color: new color of the arm
        void set_color(int arm, CRGB color, bool remote = false){
            colors[arm] = color;
            if(remote && in_obsrv != NULL) {
                in_obsrv((StateChange)arm);
            } else if (!remote && out_obsrv != NULL) {
                out_obsrv((StateChange)arm);
            }
        }

        // Get the color of [arm]
        CRGB get_color(int arm){
            return colors[arm];
        }
        
        // Turn [arm] to [state]
        void set_on_state(int arm, bool state, bool remote = false){
            on[arm] = state;
            if(remote && in_obsrv != NULL) {
                in_obsrv((StateChange)(arm+4));
            } else if (!remote && out_obsrv != NULL) {
                out_obsrv((StateChange)(arm+4));
            }
        }

        // Switch the state of [arm]
        void toggle_arm(int arm, bool remote = false){
            on[arm] = !on[arm];
            if(remote && in_obsrv != NULL) {
                in_obsrv((StateChange)(arm+4));
            } else if (!remote && out_obsrv != NULL) {
                out_obsrv((StateChange)(arm+4));
            }
        }

        // Get the current state of [arm]
        bool get_on_state(int arm){
            return on[arm];
        }

        // Set angle of cross to [new_angle]
        void set_angle(uint16_t new_angle, bool remote = false){
            angle = new_angle;
            if(remote && in_obsrv != NULL) {
                in_obsrv(StateChange::ANGLE);
            } else if (!remote && out_obsrv != NULL) {
                out_obsrv(StateChange::ANGLE);
            }
        }

        // Get angle of cross
        uint16_t get_angle(){
            return angle;
        }

        // Registers a callback when the state is changed through a network event
        void register_incoming_observer(state_observer obsrv){
            in_obsrv = obsrv;
        }

        // Registers a callbeck when the state is changed by a local call
        void register_outgoing_observer(state_observer obsrv){
            out_obsrv = obsrv;
        }
    private:
        CRGB colors[4];
        bool on[4];
        uint16_t angle;
        state_observer in_obsrv;
        state_observer out_obsrv;
};

#endif