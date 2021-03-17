#include "OTA.h"
#include "Debug.h"

void onStart() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
    else // U_SPIFFS
        type = "filesystem";
    Debug.println("Start updating " + type);
}

void onEnd() {
    Debug.println("Finished Update");
}

void progress(unsigned int progress, unsigned int total) {
    Debug.printf("Progress: %u%%\r", (progress / (total / 100)));
}

void onError(ota_error_t error) {
    Debug.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
        Debug.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
        Debug.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
        Debug.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
        Debug.println("Receive Failed");
    else if (error == OTA_END_ERROR)
        Debug.println("End Failed");
}

void ota_setup() {
    ArduinoOTA.onStart(onStart);
    ArduinoOTA.onEnd(onEnd);
    ArduinoOTA.onProgress(progress);
    ArduinoOTA.onError(onError);

    ArduinoOTA.setPassword(ESP_PW);
    ArduinoOTA.begin();
    MDNS.addService("ota", "tcp", 8266);
    Debug.println("OTA setup complete"); 
}

void ota_check_for_update() {
    ArduinoOTA.handle();
}