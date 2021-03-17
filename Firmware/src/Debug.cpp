#include "Debug.h"

String debug_topic = (String(DNAME) + "/debug").c_str();

void DebugClass::print(String str) {
    Serial.print(str);
    Connection.send(debug_topic, str);
}
void DebugClass::print(char c) {
    Serial.print(c);
    Connection.send(debug_topic, String(c));
}

void DebugClass::println(String str) {
    Serial.println(str);
    Connection.send(debug_topic, str);
}
void DebugClass::println(char c) {
    Serial.println(c);
    Connection.send(debug_topic, String(c));
}

DebugClass Debug = DebugClass();


