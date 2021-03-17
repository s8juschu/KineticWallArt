#include "Connection.h"
#include "Debug.h"
#include "State.h"

WiFiClient espClient;
MQTTClient client;
extern State cross;

typedef union payload_union {
    bool on_state;
    uint16_t angle;
    struct color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } color;
} Payload;

void reconnect();
void recv_callback(MQTTClient *client, char* topic, char* payload, int length);
void state_updated(StateChange change);

void ConnectionClass::setup() {
    client.begin(MQTT_HOST, String(MQTT_PORT).toInt(), espClient);
    client.setKeepAlive(300);
    client.onMessageAdvanced(recv_callback);
    cross.register_outgoing_observer(state_updated);
    reconnect();
}

void ConnectionClass::loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}


void reconnect(){
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        set_color(CRGB(235,219,0));
        String name = String(DNAME);
        // Attempt to connect
        if (client.connect(name.c_str())) {
            Debug.println("connected");
            // Once connected, subsrcibe to channels
            client.subscribe((name + "/downstream/color/0").c_str(), 0);
            client.subscribe((name + "/downstream/color/1").c_str(), 0);
            client.subscribe((name + "/downstream/color/2").c_str(), 0);
            client.subscribe((name + "/downstream/color/3").c_str(), 0);
            client.subscribe((name + "/downstream/on/0").c_str(), 0);
            client.subscribe((name + "/downstream/on/1").c_str(), 0);
            client.subscribe((name + "/downstream/on/2").c_str(), 0);
            client.subscribe((name + "/downstream/on/3").c_str(), 0);
            client.subscribe((name + "/downstream/angle").c_str(), 0);
            set_color(CRGB(0,255,0));
            delay(1000);
            FastLED.clear();
            FastLED.show();
        } else {
            Serial.print("failed, rc=");
            Serial.printf("%d", client.lastError());
            Serial.println(" try again in 5 seconds");
            set_color(CRGB(255,0,0));
            // Wait 5 seconds before retrying
            delay(5000);
            FastLED.clear();
            FastLED.show();
        }
    }
}



void recv_callback(MQTTClient *client, char* topic, char* payload, int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.println("]");

    char field_type;
    int field_idx;
    String action(topic);
    int last_idx = action.lastIndexOf("/");
    if (action[last_idx+1] != 'a') {
        field_idx = String(action[last_idx+1]).toInt();
        field_type = action[action.lastIndexOf("/", last_idx-1)+1];
    } else {
        field_idx = -1;
        field_type = 'a';
    }
    Payload p;
    memcpy(&p, payload, length);
    switch(field_type){
        case 'a':
            cross.set_angle(p.angle, true);
            break;
        case 'c':
            cross.set_color(field_idx, CRGB(p.color.r, p.color.g, p.color.b), true);
            break;
        case 'o':
            cross.set_on_state(field_idx, p.on_state, true);
    }
}

void send_color(int idx){
    CRGB color = cross.get_color(idx);
    uint8_t buf[3] = {color.r, color.g, color.b};
    String name = String(DNAME);
    client.publish((name + "/upstream/color/" + idx).c_str(), (const char*)&buf, 3);
}

void send_on_state(int idx){
    uint8_t state = (uint8_t)cross.get_on_state(idx);
    String name = String(DNAME);
    client.publish((name + "/upstream/on/" + idx).c_str(), (const char*)&state, 1);
}

void send_angle(){
    uint16_t angle = cross.get_angle();
    String name = String(DNAME);
    client.publish((name + "/upstream/angle").c_str(), (const char*)&angle, 2);
}

void state_updated(StateChange change){
    String name = String(DNAME);
    switch(change) {
        case COLOR_0:
            send_color(0);
            break;
        case COLOR_1:
            send_color(1);
            break;
        case COLOR_2:
            send_color(2);
            break;
        case COLOR_3:
            send_color(3);
            break;
        case ON_0:
            send_on_state(0);
            break;
        case ON_1:
            send_on_state(1);
            break;
        case ON_2:
            send_on_state(2);
            break;
        case ON_3:
            send_on_state(3);
            break;
        case ANGLE:
            send_angle();
            break;
    }
}

void ConnectionClass::send(String topic, String payload){
    if(client.connected()){
        client.publish(topic.c_str(), payload.c_str());
    }
}

ConnectionClass Connection = ConnectionClass();