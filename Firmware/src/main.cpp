#include <Arduino.h>
#include <Servo.h>

#include <OTA.h>
#include <Connection.h>
#include <LED.h>
#include <Touch_Control.h>
#include <State.h>
#include <ServoController.h>

State cross;

void led_touched(int cap);
void leds_range(int f, int t, CRGB color, int br);
void fadeOff();
void wifi_setup();
void pad_touched(int side);
void arm_touched(int arm);
void pad_released(int side);
void arm_released(int arm);

TouchSensor touch(pad_touched, pad_released, arm_touched, arm_released);

void test_obsrv(StateChange change){
  Serial.print("changed ");
  int angle = cross.get_angle();
  switch (change) {
    case ON_0:
      if(!cross.get_on_state(0)){
        fade_off(0);
      }
      break;
    case ON_1:
      if(!cross.get_on_state(1)){
        fade_off(1);
      }
      break;
    case ON_2:
      if(!cross.get_on_state(2)){
        fade_off(2);
      }
      break;
    case ON_3:
      if(!cross.get_on_state(3)){
        fade_off(3);
      }
      break;
    case ANGLE:
      
      rotate_to(angle);
      break;
    default:
      break;
  }
}

void setup(){
  Serial.begin(9600);
  inti_leds();

  //Connect to Wifi
  wifi_setup();
  
  ota_setup();
  Connection.setup();
  cross.register_incoming_observer(test_obsrv);
  
  touch.setup();

  setup_servo();
  Debug.println("Init done...");
}

void update_leds(){
  for(int i = 0; i < 4; i++){
    if(cross.get_on_state(i)){
      fade_arm_towards(i, cross.get_color(i));
    }
  }
}

void loop(){
  ota_check_for_update();
  Connection.loop();
  touch.loop();
  update_leds();
  loop_servo();

  delay(100);
}

void pad_touched(int side){
  if (side % 2 == 0){
    rotate_cw();
  }
  else {
    rotate_ccw();
  }
}

void pad_released(int side){
  stop_servo();
}

void arm_touched(int arm){
  Serial.print("Arm ");
  Serial.print(arm);
  Serial.println(" touched");
  cross.toggle_arm(arm);
  fade_off(arm);
}

void arm_released(int arm){
  Serial.print("Arm ");
  Serial.print(arm);
  Serial.println(" released");
}


void wifi_setup(){
  //Configure static IP
  IPAddress ip;
  ip.fromString(SIP);
  IPAddress gateway;
  gateway.fromString(GATEWAY);
  IPAddress subnet;
  subnet.fromString(SUBNET);
  if (!WiFi.config(ip, gateway, subnet)) {
    Serial.println("STA Failed to configure");
    set_color(CRGB(255,0,0));
    delay(3000);
    ESP.restart();
  }


  WiFi.begin(WIFI_SSID, WIFI_PW);
  Serial.printf("Connecting to Wifi: %s\n", WIFI_SSID);
  unsigned long startTime = millis();
  int arm = 0;
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000)
  {
      set_arm(arm%4, CRGB(0, 127, 255));
      Serial.print(".");
      delay(500);
      FastLED.clear();
      arm++;
  }
  Serial.println();
  if(WiFi.status() != WL_CONNECTED)
  {
      Serial.println("Connection Failed! Rebooting...");
      FastLED.clear();
      set_color(CRGB(255,0,0));
      delay(3000);
      ESP.restart();
  }
  FastLED.clear();
  set_color(CRGB(0,255,0));
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  FastLED.clear();
  FastLED.show();
}