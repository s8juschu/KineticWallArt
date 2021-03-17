 #include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

typedef void (*touch_callback) (int);


class TouchSensor {
    public:
        TouchSensor(touch_callback touched, touch_callback released, touch_callback arm_touched, touch_callback arm_released){
            cap = Adafruit_MPR121();
            t_callback = touched;
            r_callback = released;
            t_arm_callback = arm_touched;
            r_arm_callback = arm_released;
            lasttouched = 0;
        }
        void setup(){
            Debug.println("MPR121 Capacitive Touch Init...");
            
            if (!cap.begin(0x5A)) {
                Debug.println("MPR121 not found, check wiring?");
                while (1);
            }

            Debug.println("MPR121 found!"); 
        }
        void loop(){
            int currtouched = cap.touched();
            for (int i = 0; i < 8; i++){
                // if it *is* touched and *was not* touched before -> touched!
                if (is_touched(currtouched, i) && !is_touched(lasttouched, i)){
                    t_callback(i);
                }
                // if it *was* touched and now *isnt* -> released!
                if (!is_touched(currtouched, i) && is_touched(lasttouched, i)){
                    r_callback(i);
                }

            }
            for(int arm = 0; arm < 4; arm++){
                int pad1;
                int pad2;
                switch(arm){
                    case 0:
                        pad1 = 0;
                        pad2 = 1;
                        break;
                    case 1:
                        pad1 = 2;
                        pad2 = 3;
                        break;
                    case 2:
                        pad1 = 4;
                        pad2 = 5;
                        break;
                    case 3:
                        pad1 = 6;
                        pad2 = 7;
                        break;
                    default:
                        pad1 = 0;
                        pad2 = 1;
                        break;
                }
                if (is_touched(currtouched, pad1) && is_touched(currtouched, pad2) && !(is_touched(lasttouched, pad1) && is_touched(lasttouched, pad2))){
                    t_arm_callback(arm);
                }
                if (!(is_touched(currtouched, pad1) && is_touched(currtouched, pad2)) && is_touched(lasttouched, pad1) && is_touched(lasttouched, pad2)){
                    r_arm_callback(arm);
                }

            }
            lasttouched = currtouched;
        }

    private:
        Adafruit_MPR121 cap;
        touch_callback t_callback;
        touch_callback t_arm_callback;
        touch_callback r_callback;
        touch_callback r_arm_callback;
        int lasttouched;

        bool is_touched(int touched, int cap){
            return touched & _BV(cap);
        }
};