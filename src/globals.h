#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

// Deklaráld a security változót extern-ként
extern String security;
extern char global_mqtt_server[64];
extern char global_mqtt_user[64];
extern char global_mqtt_password[64];
extern bool MQTT_Configured;
    
extern int global_minDistance; // Initialize to maximum possible value
extern int global_maxDistance; // Initialize to minimum possible value    
    


#endif // GLOBALS_H