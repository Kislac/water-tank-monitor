#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <lvgl.h>

void CalcMaxTanklevel();
void checkForUpdate();
void printHeapStatus();

// Deklaráld a security változót extern-ként
extern String security;
extern char global_mqtt_server[64];
extern char global_mqtt_user[64];
extern char global_mqtt_password[64];
extern bool MQTT_Configured;
    
extern int global_minDistance; // Initialize to maximum possible value
extern int global_maxDistance; // Initialize to minimum possible value    
    

extern uint8_t global_tankType;
extern uint16_t global_rectWide;
extern uint16_t global_rectDepth;
extern uint16_t global_rectHeight;
extern uint16_t global_cilDiameter;
extern uint16_t global_cilHeight;
extern uint16_t global_emptyTank;
extern uint16_t global_fullTank;
extern float global_MaxTankLevelInLiter;
extern float global_tankVolume;

//extern lv_obj_t * global_ui_Info;
extern bool FW_Update_Check;





#endif // GLOBALS_H