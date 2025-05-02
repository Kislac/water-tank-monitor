#include "globals.h"
#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include <WiFi.h>
#include <FS.h>     // Include the SPIFFS library for Version handling
#include <SPIFFS.h> // Include the SPIFFS library for Version handling
#include <PubSubClient.h>
#include <EEPROM.h>
//#include <esp_heap_caps.h>

//include OTA
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <HTTPUpdate.h>



//-------------------------------
#include <Wire.h>
#include <Adafruit_AHTX0.h>
// Define I2C pins for AHT10 (IO21 for SDA, IO22 for SCL)
#define AHT10_SDA 21
#define AHT10_SCL 22

// Define I2C pins for VL53L1X (IO21 for SDA, IO22 for SCL)
#define VL53L1X_SDA 21
#define VL53L1X_SCL 22

// Create a TwoWire object for I2C_NUM_1
TwoWire I2C_AHT10 = TwoWire(1);  // Specify the I2C peripheral (1 for I2C_NUM_1)

Adafruit_AHTX0 aht = Adafruit_AHTX0();  // Create the sensor object
float Temperature_Value = 0;
float Huminidity_Value = 0;


TwoWire I2C_VL53L1X = TwoWire(1);  // Specify the I2C peripheral (1 for I2C_NUM_1)
#include <VL53L1X.h>
VL53L1X sensor;// = VL53L1X();
// Define arrays to store temperature and humidity data
float temp_data[10] = {0};
float hum_data[10] = {0};
int data_index = 0;
//------------------------
bool lvgl_enabled = true;

bool vl53l1x_initialized = false;
bool aht10_initialized = false;


//Set the screen brightness to 50% initially
#define SCREEN_INITIAL_BRIGHTNESS 50
ulong next_millis;
auto lv_last_tick = millis();
char text_buffer[32];

int64_t now = 0;
String security;

bool internetOK = false;
bool wifiConnected = false;
char macAddress[18];
char device_name[32];
char device_identifiers[32];
char device_manufacturer[32];
char device_model[32];
char device_sw_version[32];

WiFiClient espClient;
PubSubClient client(espClient);
bool MQTT_Configured = false;

char global_mqtt_server[64];
char global_mqtt_user[64];
char global_mqtt_password[64];

bool FW_Update_Check = false;


int global_minDistance = INT_MAX; // Initialize to maximum possible value
int global_maxDistance = INT_MIN; // Initialize to minimum possible value

int build_number = 0;

uint8_t global_tankType = 0;
uint16_t global_rectWide = 0;
uint16_t global_rectDepth = 0;
uint16_t global_rectHeight = 0;
uint16_t global_cilDiameter = 0;
uint16_t global_cilHeight = 0;
uint16_t global_emptyTank = 0;
uint16_t global_fullTank = 0;
float global_MaxTankLevelInLiter = 0;
float global_tankVolume = 0.0f;

int distance = 0;
int CurrentLiter;
float CurrentLiterInPer;

// Inicializáld a globális változót
//lv_obj_t * global_ui_Info = NULL;

void initializeBuildInfo()
{
  
  // Get and print the build date and time
  Serial.printf("Build Date: %s, Build Time: %s\n", __DATE__, __TIME__);

  // Update the ui_BuildDateValue with the build date and time
  lv_label_set_text_fmt(ui_lblBuildDateValue, "%s %s", __DATE__, __TIME__);
  
  // Read the build number from version.txt
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  File versionFile = SPIFFS.open("/version.txt", "r");
  if (!versionFile) {
    Serial.println("Failed to open version file");
    return;
  }

  build_number = versionFile.parseInt();
  Serial.printf("Build_number: %d \n", build_number);
  versionFile.close();

  // Update the ui_VerValue with the code version
  device_sw_version[16];
  sprintf(device_sw_version, "v1.1.%d", build_number);
  lv_label_set_text(ui_lblBuildVersionValue, device_sw_version);
}


lv_obj_t * WifiInternetOKImages[1];
lv_obj_t * WifiDisconnectedImages[1];
lv_obj_t * WifiConnectedNoInternetImages[1];
void initWifiSignalImages(){
  WifiInternetOKImages[0] = ui_imWifiInternetOK1;
  //WifiInternetOKImages[1] = ui_imWifiInternetOK2;
  //WifiInternetOKImages[2] = ui_imWifiInternetOK3;
  //WifiInternetOKImages[3] = ui_imWifiInternetOK4;
  //WifiInternetOKImages[4] = ui_imWifiInternetOK5;
  WifiDisconnectedImages[0] = ui_imWifiDisconnected1;
  //WifiDisconnectedImages[1] = ui_imWifiDisconnected2;
  //WifiDisconnectedImages[2] = ui_imWifiDisconnected3;
  //WifiDisconnectedImages[3] = ui_imWifiDisconnected4;
  //WifiDisconnectedImages[4] = ui_imWifiDisconnected5;
  WifiConnectedNoInternetImages[0] = ui_imWifiConnectedNoInternet1;
  //WifiConnectedNoInternetImages[1] = ui_imWifiConnectedNoInternet2;
  //WifiConnectedNoInternetImages[2] = ui_imWifiConnectedNoInternet3;
  //WifiConnectedNoInternetImages[3] = ui_imWifiConnectedNoInternet4;
  //WifiConnectedNoInternetImages[4] = ui_imWifiConnectedNoInternet5;
}


// Függvény a képek láthatóságának frissítésére
void updateStatusImages(bool internetOK) {
  // WiFi Disconnected képek kezelése

  int wifiDisconnectedImagesCount = sizeof(WifiInternetOKImages) / sizeof(WifiInternetOKImages[0]);
  //Serial.printf("wifiDisconnectedImages has %d elements\n", wifiDisconnectedImagesCount);
  for (int i = 0; i < wifiDisconnectedImagesCount; i++) {
    if (WifiInternetOKImages[i] == nullptr) {
      Serial.printf("wifiDisconnectedImages[%d] is nullptr\n", i);
    } else {
      //lv_obj_t* img = wifiDisconnectedImages[i];
      //if (img != nullptr) { // Ensure the pointer is not null
          if (wifiConnected && internetOK) {
              lv_obj_add_flag(WifiDisconnectedImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
              lv_obj_add_flag(WifiConnectedNoInternetImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
              lv_obj_clear_flag(WifiInternetOKImages[i], LV_OBJ_FLAG_HIDDEN); // Megjelenítés
          } else if (wifiConnected && !internetOK) {
              lv_obj_add_flag(WifiDisconnectedImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
              lv_obj_clear_flag(WifiConnectedNoInternetImages[i], LV_OBJ_FLAG_HIDDEN); // Megjelenítés
              lv_obj_add_flag(WifiInternetOKImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
          } else if (!wifiConnected){
              lv_obj_clear_flag(WifiDisconnectedImages[i], LV_OBJ_FLAG_HIDDEN); // Megjelenítés
              lv_obj_add_flag(WifiConnectedNoInternetImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
              lv_obj_add_flag(WifiInternetOKImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
          }  
    }
  }

}

// Hívás a státusz frissítésére
void CheckWifiandInternetStatus() {
    static ulong last_status_refresh_time = 0;

    if (millis() - last_status_refresh_time >= 1000) { // Refresh every second
      last_status_refresh_time = millis();

      wifiConnected = (WiFi.status() == WL_CONNECTED);
      internetOK = false;

      // Internet kapcsolat ellenőrzése
      WiFiClient client;
      if (wifiConnected && client.connect("www.google.com", 80)) {
        internetOK = true;
        client.stop();
      }

      // Frissítsd a képeket
      updateStatusImages(internetOK);
    }
}

void RefreshWifiParameters() {
  static ulong last_refresh_time = 0;

  if (millis() - last_refresh_time >= 5000) { // Refresh every 5 seconds
    last_refresh_time = millis();

    if(lv_scr_act() == ui_Wifi_Settings){
      // Refresh WiFi status
      const char *status = (WiFi.status() == WL_CONNECTED) ? "Connected" : "Disconnected";
      lv_label_set_text(ui_lblWifiStatus, status);


      if (WiFi.status() == WL_CONNECTED) {
        // Refresh SSID
        lv_label_set_text(ui_lblWifiSSID, WiFi.SSID().c_str());
        

        // Refresh IP address
        lv_label_set_text(ui_lblWifiIP, WiFi.localIP().toString().c_str());

        // Refresh RSSI
        char rssi_text[16];
        snprintf(rssi_text, sizeof(rssi_text), "%d dBm", WiFi.RSSI());
        lv_label_set_text(ui_lblWifiRSSI, rssi_text);
        //lv_label_set_text(ui_lblWifiRSSI2, rssi_text);

        // Refresh Channel
        char channel_text[16];
        snprintf(channel_text, sizeof(channel_text), "Ch: %d", WiFi.channel());
        lv_label_set_text(ui_lblWifiChannel, channel_text);

        lv_label_set_text(ui_lblWifiSecurity, security.c_str());

        
        
      } else {
        // Clear labels if not connected
        lv_label_set_text(ui_lblWifiSSID, "N/A");
        lv_label_set_text(ui_lblWifiRSSI2, "N/A");
        lv_label_set_text(ui_lblWifiIP, "N/A");
        lv_label_set_text(ui_lblWifiRSSI, "N/A");
        lv_label_set_text(ui_lblWifiChannel, "N/A");
        lv_label_set_text(ui_lblWifiSecurity, "N/A");
      }
    }else if(lv_scr_act() == ui_Main_Screen){
      if (WiFi.status() == WL_CONNECTED) {
        // Refresh RSSI
        char rssi_text[16];
        snprintf(rssi_text, sizeof(rssi_text), "%d dBm", WiFi.RSSI());
        lv_label_set_text(ui_lblWifiRSSI2, rssi_text);
      }else{
        lv_label_set_text(ui_lblWifiRSSI2, "- dBm");
      }
    }
  }
}

void runtimecalc(){
  static ulong last_runtime = 0;

  if (millis() - last_runtime >= 100) { // Refresh every 100ms
    last_runtime = millis();

    int64_t total_seconds = now / 1000;
    int years = total_seconds / (365 * 24 * 3600);
    total_seconds %= (365 * 24 * 3600);
    int days = total_seconds / (24 * 3600);
    total_seconds %= (24 * 3600);
    int hours = total_seconds / 3600;
    total_seconds %= 3600;
    int minutes = total_seconds / 60;
    float seconds = total_seconds % 60 + (now % 1000) / 1000.0;

    if (lv_tabview_get_tab_act(ui_MainTabView) == 4) {
        // Update the audio tab
        sprintf(text_buffer, "%02d-%03d %02d:%02d:%02.1f", years, days, hours, minutes, seconds);
        lv_label_set_text(ui_lblRunTimeValue, text_buffer);
        //sprintf(text_buffer, "%02d hour %02d min %02.1f sec", hours, minutes, seconds);
        //lv_label_set_text(ui_lblRuntimeHMSValue, text_buffer);
    }
  }
}

void DateAndTimeHandling(){
static ulong last_ntp_sync = 0;
static ulong last_time_update = 0;
static time_t current_time = 0; // Store the current time in seconds since epoch
//static int timezone_offset = 3600; // Default timezone offset in seconds (CET)

if (internetOK && (millis() - last_ntp_sync >= 60000*5 || current_time < 946684800)) { // Sync with NTP every 60 seconds or before year 2000
  configTzTime("CET-1CEST,M3.5.0/2,M10.5.0/3", "pool.ntp.org", "time.nist.gov"); // Configure NTP servers
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    current_time = mktime(&timeinfo); // Update current time
    last_ntp_sync = millis();
    Serial.println("Time synchronized with NTP.");
  } else {
    Serial.println("Failed to synchronize time with NTP.");
  }
}

if (millis() - last_time_update >= 1000) { // Update time every second
  last_time_update = millis();
  current_time++; // Increment the current time by one second
  //Serial.printf("Current time: %d", current_time); // Print the current time
  struct tm *timeinfo = localtime(&current_time);
  if (timeinfo) {
    char datetime_text[32];
    strftime(datetime_text, sizeof(datetime_text), "%Y.%m.%d %H:%M:%S", timeinfo);
    //lv_label_set_text(ui_lblTime, datetime_text);
    lv_label_set_text(ui_lblDataNTime, datetime_text);

  } else {
    //lv_label_set_text(ui_lblTime, "Time Unavailable");
    lv_label_set_text(ui_lblDataNTime, "Time Unavailable");
  }
}
  
}

void AutoBacklight(){
  #ifdef BOARD_HAS_CDS
  static ulong last_AutoBacklight = 0;
  static int last_slider_value = 0;

  if (millis() - last_AutoBacklight >= 100) { // Refresh every 100ms
    // Debounced EEPROM save for slider value
    static ulong last_slider_change_time = 0;
    static bool slider_changed = false;

    last_AutoBacklight = millis();
    auto cdr = analogReadMilliVolts(CDS);
    sprintf(text_buffer, "%d", cdr);
    if (lv_tabview_get_tab_act(ui_MainTabView) == 3) {
        lv_label_set_text(ui_lblLigthSensorValue, text_buffer);
    }
    
    if (lv_obj_get_state(ui_switchManualAutomatic) & LV_STATE_CHECKED) {
        float adaptive_brightness = smartdisplay_lcd_adaptive_brightness_cds();
        smartdisplay_lcd_set_backlight(adaptive_brightness);
        if (lv_tabview_get_tab_act(ui_MainTabView) == 3) {
          int slider_value = (int)(adaptive_brightness * 100);
          lv_slider_set_value(ui_LigthSensorSlider, slider_value, LV_ANIM_OFF);
          sprintf(text_buffer, "%d%%", slider_value);
          lv_label_set_text(ui_lblLigthSensorSliderValue, text_buffer);
        }
    }
    int slider_value = lv_slider_get_value(ui_LigthSensorSlider);
    if (!(lv_obj_get_state(ui_switchManualAutomatic) & LV_STATE_CHECKED) && slider_value != last_slider_value) {
        // Read the slider value
        
        
        //int slider_value = lv_slider_get_value(ui_LigthSensorSlider);
        float lcd_set_backlight = (float)slider_value / 100;
        Serial.printf("slider_value: %d | lcd_set_backlight: %.2f\n", slider_value, lcd_set_backlight);
        smartdisplay_lcd_set_backlight(max(lcd_set_backlight, 0.01f));

        // Detect slider value change
        if (slider_value != last_slider_value) {
          last_slider_change_time = millis();
          slider_changed = true;
          last_slider_value = slider_value;
        }


    }
    // Save to EEPROM if 3 seconds have passed since last change
    if (slider_changed && (millis() - last_slider_change_time >= 3000)) {
      EEPROM.begin(512);
      EEPROM.write(301, slider_value); // Store slider value at address 301
      EEPROM.commit();
      EEPROM.end();
      Serial.printf("Light sensor slider value saved (delayed): %d\n", slider_value);
      slider_changed = false;
    }

  }
  #endif
}


void publishDiscoveryMessages() {
  if (!client.connected()) return;  // Ne próbáljunk publish-olni, ha nincs kapcsolat

  Serial.println("Publishing discovery...");
  if (!client.connected()) {
    Serial.println("MQTT client is not connected.");
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi is not connected.");
      return;
  }



  char rssi_discovery_topic[128];
  snprintf(rssi_discovery_topic, sizeof(rssi_discovery_topic), "homeassistant/sensor/%s_wifi_rssi/config", macAddress);
  char rssi_discovery_payload[512];
  snprintf(rssi_discovery_payload, sizeof(rssi_discovery_payload),
  "{"
    "\"name\":\"WiFi RSSI\","
    "\"uniq_id\":\"WTM_wifi_rssi_%s\","
    "\"state_topic\":\"WTM_%s/wifi/rssi\","
    "\"unit_of_measurement\":\"dBm\","
    "\"device_class\":\"signal_strength\","
    "\"device\":{"
      "\"name\":\"%s\","
      "\"identifiers\":[\"%s\"],"
      "\"manufacturer\":\"%s\","
      "\"model\":\"%s\","
      "\"sw_version\":\"%s\""
    "}"
  "}", macAddress, macAddress, device_name, device_identifiers,device_manufacturer, device_model, device_sw_version);
  bool result_rssi = client.publish(rssi_discovery_topic, rssi_discovery_payload, false);
  Serial.print("MQTT: RSSI discovery publish result: ");
  Serial.println(result_rssi ? "OK" : "FAILED");
//  if (!result_rssi) {
//    Serial.print("MQTT client state: ");
//    Serial.println(client.state());
//  }

  // Temperature discovery
  char temp_discovery_topic[128];
  snprintf(temp_discovery_topic, sizeof(temp_discovery_topic), "homeassistant/sensor/%s_temperature/config", macAddress);
  char temp_discovery_payload[512];
  snprintf(temp_discovery_payload, sizeof(temp_discovery_payload),
  "{"
    "\"name\":\"Temperature\","
    "\"uniq_id\":\"WTM_temperature_%s\","
    "\"state_topic\":\"WTM_%s/sensor/temperature\","
    "\"unit_of_measurement\":\"°C\","
    "\"device_class\":\"temperature\","
    "\"device\":{"
      "\"name\":\"%s\","
      "\"identifiers\":[\"%s\"],"
      "\"manufacturer\":\"%s\","
      "\"model\":\"%s\","
      "\"sw_version\":\"%s\""
    "}"
  "}", macAddress, macAddress, device_name, device_identifiers, device_manufacturer, device_model, device_sw_version);
  bool result_temp = client.publish(temp_discovery_topic, temp_discovery_payload, true);
  Serial.print("MQTT: Temperature discovery publish result: ");
  Serial.println(result_temp ? "OK" : "FAILED");

  // Humidity discovery
  char hum_discovery_topic[128];
  snprintf(hum_discovery_topic, sizeof(hum_discovery_topic), "homeassistant/sensor/%s_humidity/config", macAddress);
  char hum_discovery_payload[512];
  snprintf(hum_discovery_payload, sizeof(hum_discovery_payload),
  "{"
    "\"name\":\"Humidity\","
    "\"uniq_id\":\"WTM_humidity_%s\","
    "\"state_topic\":\"WTM_%s/sensor/humidity\","
    "\"unit_of_measurement\":\"%%\","
    "\"device_class\":\"humidity\","
    "\"device\":{"
      "\"name\":\"%s\","
      "\"identifiers\":[\"%s\"],"
      "\"manufacturer\":\"%s\","
      "\"model\":\"%s\","
      "\"sw_version\":\"%s\""
    "}"
  "}", macAddress, macAddress, device_name, device_identifiers, device_manufacturer, device_model, device_sw_version);
  bool result_hum = client.publish(hum_discovery_topic, hum_discovery_payload, true);
  Serial.print("MQTT: Humidity discovery publish result: ");
  Serial.println(result_hum ? "OK" : "FAILED");

  // Distance discovery
  char distance_discovery_topic[128];
  snprintf(distance_discovery_topic, sizeof(distance_discovery_topic), "homeassistant/sensor/%s_distance/config", macAddress);
  char distance_discovery_payload[512];
  snprintf(distance_discovery_payload, sizeof(distance_discovery_payload),
  "{"
    "\"name\":\"Distance\","
    "\"uniq_id\":\"WTM_distance_%s\","
    "\"state_topic\":\"WTM_%s/sensor/distance\","
    "\"unit_of_measurement\":\"mm\","
    "\"device_class\":\"distance\","
    "\"device\":{"
      "\"name\":\"%s\","
      "\"identifiers\":[\"%s\"],"
      "\"manufacturer\":\"%s\","
      "\"model\":\"%s\","
      "\"sw_version\":\"%s\""
    "}"
  "}", macAddress, macAddress, device_name, device_identifiers, device_manufacturer, device_model, device_sw_version);
  bool result_dist = client.publish(distance_discovery_topic, distance_discovery_payload, true);
  Serial.print("MQTT: Distance discovery publish result: ");
  Serial.println(result_dist ? "OK" : "FAILED");

  // Liter discovery
  char liter_discovery_topic[128];
  snprintf(liter_discovery_topic, sizeof(liter_discovery_topic), "homeassistant/sensor/%s_liter/config", macAddress);
  char liter_discovery_payload[512];
  snprintf(liter_discovery_payload, sizeof(liter_discovery_payload),
  "{"
    "\"name\":\"Liter\","
    "\"uniq_id\":\"WTM_liter_%s\","
    "\"state_topic\":\"WTM_%s/sensor/liter\","
    "\"unit_of_measurement\":\"L\","
    "\"device_class\":\"volume\","
    "\"device\":{"
      "\"name\":\"%s\","
      "\"identifiers\":[\"%s\"],"
      "\"manufacturer\":\"%s\","
      "\"model\":\"%s\","
      "\"sw_version\":\"%s\""
    "}"
  "}", macAddress, macAddress, device_name, device_identifiers, device_manufacturer, device_model, device_sw_version);
  bool result_Liter = client.publish(liter_discovery_topic, liter_discovery_payload, true);
  Serial.print("MQTT: Liter discovery publish result: ");
  Serial.println(result_Liter ? "OK" : "FAILED");

  // TankLevel discovery
  char TankLevelPercentage_discovery_topic[128];
  snprintf(TankLevelPercentage_discovery_topic, sizeof(TankLevelPercentage_discovery_topic), "homeassistant/sensor/%s_TankLevelpercentage/config", macAddress);
  char TankLevelPercentage_discovery_payload[512];
  snprintf(TankLevelPercentage_discovery_payload, sizeof(TankLevelPercentage_discovery_payload),
  "{"
    "\"name\":\"TankLevelTankLevel\","
    "\"uniq_id\":\"WTM_TankLevelPercentage_%s\","
    "\"state_topic\":\"WTM_%s/sensor/TankLevelpercentage\","
    "\"unit_of_measurement\":\"%%\","
    "\"device_class\":\"moisture\","
    "\"device\":{"
      "\"name\":\"%s\","
      "\"identifiers\":[\"%s\"],"
      "\"manufacturer\":\"%s\","
      "\"model\":\"%s\","
      "\"sw_version\":\"%s\""
    "}"
  "}", macAddress, macAddress, device_name, device_identifiers, device_manufacturer, device_model, device_sw_version);
  bool result_TankLevelPercentage = client.publish(TankLevelPercentage_discovery_topic, TankLevelPercentage_discovery_payload, true);
  Serial.print("TankLevelPercentage discovery publish result: ");
  Serial.println(result_TankLevelPercentage ? "OK" : "FAILED");
}

bool MQTT_Connect() {
  if (client.connect("esp32_water_tank", global_mqtt_user, global_mqtt_password)) {
    Serial.println("MQTT: Connected to the MQTT server!");
    //client.subscribe("esp32/water"); Ez a fogadáshoz kell

    // Discovery topicok küldése
    publishDiscoveryMessages();
    return true;
  } else {
    Serial.print("MQTT: Not able to connect the MQTT server!, error code: ");
    Serial.println(client.state());
    return false;
  }
}

void MQTT_setup(){
  static ulong last_MQTT_Connect = 0;
  if (millis() - last_MQTT_Connect >= 5000) { // Refresh every 100ms
    last_MQTT_Connect = millis();
    if (MQTT_Configured && wifiConnected) {
      client.setServer(global_mqtt_server, 1883);
      client.setBufferSize(1024);
      //client.setCallback(callback);
      while (!client.connected()) {
        Serial.print("Kapcsolódás az MQTT szerverhez: ");
        //Serial.println(mqtt_server);
    
        if (MQTT_Connect()) {
          break;
        } else {
          
            //Serial.print("MQTT: Not able to connect the MQTT server!, error code: ");
            //Serial.print(client.state());
            Serial.println(". retry after 5 sec...");
        }
      }
    }
  }
}



void ReadMQTTSettingsFromEEPROM(){
  // Read MQTT settings from EEPROM
  EEPROM.begin(512); // Initialize EEPROM with a size of 512 bytes
  EEPROM.get(0, MQTT_Configured); // Read the configuration flag from the beginning

  if (MQTT_Configured) {
    char mqttServer[64] = {0};
    char mqttUser[64] = {0};
    char mqttPassword[64] = {0};

    EEPROM.get(1, mqttServer); // Read MQTT server starting from offset 1
    EEPROM.get(65, mqttUser); // Read MQTT user starting from offset 65
    EEPROM.get(129, mqttPassword); // Read MQTT password starting from offset 129

    // Save to global variables
    strncpy(global_mqtt_server, mqttServer, sizeof(global_mqtt_server) - 1);
    strncpy(global_mqtt_user, mqttUser, sizeof(global_mqtt_user) - 1);
    strncpy(global_mqtt_password, mqttPassword, sizeof(global_mqtt_password) - 1);

    //lv_textarea_set_text(ui_TextAreaMQTTServer, global_mqtt_server);
    //lv_textarea_set_text(ui_TextAreaMQTTuser, global_mqtt_user);
    //lv_textarea_set_text(ui_TextAreaMQTTPassword, global_mqtt_password);

    Serial.println("MQTT credentials loaded successfully from EEPROM.");
    Serial.printf("Server: %s, User: %s, Pass: %s\n", global_mqtt_server, global_mqtt_user, global_mqtt_password);
  } else {
    Serial.println("No MQTT configuration found in EEPROM.");
  }

  //EEPROM.end();
}


void publishMQTTSensoraDatas() {
  static unsigned long lastRSSIPublish = 0;
  if (MQTT_Configured && millis() - lastRSSIPublish > 5000 && client.connected()) { // 5 másodpercenként publikálja az RSSI-t
    lastRSSIPublish = millis();
    long rssi = WiFi.RSSI(); // Lekérdezi az aktuális WiFi jel erősséget
    char rssiStr[10];
    snprintf(rssiStr, sizeof(rssiStr), "%ld", rssi); // Átalakítja szöveggé
    //Serial.print("WiFi RSSI: ");
    //Serial.println(rssiStr); // Kiírja a soros monitorra
    // MQTT üzenet publikálása
    char topic[64];
    snprintf(topic, sizeof(topic), "WTM_%s/wifi/rssi", macAddress);
    client.publish(topic, rssiStr, true); // Publikálja az MQTT szerverre

    // Publish temperature data
    char tempStr[10];
    snprintf(tempStr, sizeof(tempStr), "%.2f", Temperature_Value);
    snprintf(topic, sizeof(topic), "WTM_%s/sensor/temperature", macAddress);
    client.publish(topic, tempStr, true);

    // Publish humidity data
    char humStr[10];
    snprintf(humStr, sizeof(humStr), "%.2f", Huminidity_Value);
    snprintf(topic, sizeof(topic), "WTM_%s/sensor/humidity", macAddress);
    client.publish(topic, humStr, true);

    // Publish distance data
    char distanceStr[10];
    snprintf(distanceStr, sizeof(distanceStr), "%d", sensor.ranging_data.range_mm);
    snprintf(topic, sizeof(topic), "WTM_%s/sensor/distance", macAddress);
    client.publish(topic, distanceStr, true);


    // Publish Liter data
    char literStr[10];
    snprintf(literStr, sizeof(literStr), "%d", CurrentLiter);
    snprintf(topic, sizeof(topic), "WTM_%s/sensor/liter", macAddress);
    client.publish(topic, literStr, true);

    // Publish Percentage data
    char percentageStr[10];
    snprintf(percentageStr, sizeof(percentageStr), "%.1f", CurrentLiterInPer);
    snprintf(topic, sizeof(topic), "WTM_%s/sensor/TankLevelpercentage", macAddress);
    client.publish(topic, percentageStr, true);
 }
}



void initVariables(){

  snprintf(macAddress, sizeof(macAddress), "%02X%02X%02X%02X%02X%02X", 
           WiFi.macAddress()[0], WiFi.macAddress()[1], WiFi.macAddress()[2], 
           WiFi.macAddress()[3], WiFi.macAddress()[4], WiFi.macAddress()[5]);

  //Device információk inicializálása
  snprintf(device_name, sizeof(device_name), "Water Tank Meter Modul");
  snprintf(device_identifiers, sizeof(device_identifiers), "water_tank_meter_%s", macAddress);
  snprintf(device_manufacturer, sizeof(device_manufacturer), "Kislac Workshop");
  snprintf(device_model, sizeof(device_model), "esp32-2432S032C");
  //snprintf(device_sw_version, sizeof(device_sw_version), "v1.0.%d", build_number);

  Serial.printf("Device Name: %s\n", device_name);
  Serial.printf("Device Identifiers: %s\n", device_identifiers);
  Serial.printf("Device Manufacturer: %s\n", device_manufacturer);
  Serial.printf("Device Model: %s\n", device_model);
  Serial.printf("Device SW Version: %s\n", device_sw_version);
  Serial.printf("Device MAC Address: %s\n", macAddress);

}
  
void ReadAHT10()
{

  static ulong lastReadTime = 0;
  ulong currentTime = millis();
  
  if (currentTime - lastReadTime >= 500) {
    lastReadTime = currentTime;

    sensors_event_t humidity, temp;


    if (!aht.getEvent(&humidity, &temp)) {
      Serial.println("AHT10 sensor not responding. Disabling sensor.");
      aht10_initialized = false; // Szenzor letiltása
      return;
    }
    Temperature_Value = temp.temperature;
    Huminidity_Value = humidity.relative_humidity;
//    // Store the data in the arrays
//    temp_data[data_index] = temperature;
//    hum_data[data_index] = humidity;
//    // Shift the data to the left
//    for (int i = 0; i < 9; i++) {
//      temp_data[i] = temp_data[i + 1];
//      hum_data[i] = hum_data[i + 1];
//    }
//    // Add the new data to the end
//    temp_data[9] = temperature;
//    hum_data[9] = humidity;

    //Serial.printf("\rHőmérséklet: %.2f °C | Páratartalom: %.2f%% ", temp.temperature, humidity.relative_humidity);
    sprintf(text_buffer, "%.1f °C", Temperature_Value);
    lv_label_set_text(ui_lblTempValue, text_buffer);
    sprintf(text_buffer, "%.1f %%", Huminidity_Value);
    lv_label_set_text(ui_lblHumValue, text_buffer);


  }
}

void ReadTankLevelinLiters() {
  // Calculate global_MaxTankLevelInLiter in liters (dm^3)
  
  float radius;
  float volume_dm3;
	if (global_tankType == 0) { // Cilinder
		// Volume = π * r^2 * h
		radius = global_cilDiameter / 200.0f; // mm
    volume_dm3 = 3.14159265f * (radius / 100.0f) * (radius / 100.0f) * ((global_cilHeight / 100.0f)-(distance / 100.0f)+(global_fullTank / 100.0f));
  } else if (global_tankType == 1) { // Rectangle
		// Volume = width * depth * height
		volume_dm3 = (global_rectWide/100.0f) * (global_rectDepth/ 100.0f) * ((global_rectHeight / 100.0f) - (distance/ 100.0f) + (global_fullTank/ 100.0f));
	}
  CurrentLiter = static_cast<int>(volume_dm3);
  CurrentLiterInPer = CurrentLiter /  global_MaxTankLevelInLiter * 100.0f;
  // Clamp CurrentLiterInPer between 0 and 100
  if (CurrentLiterInPer < 0.0f) CurrentLiterInPer = 0.0f;
  if (CurrentLiterInPer > 100.0f) CurrentLiterInPer = 100.0f;
  // Print all relevant variables for debugging
  //Serial.println("Debugging Variables:");
  //Serial.printf("global_tankType: %u\n", global_tankType);
  //Serial.printf("global_rectWide: %u\n", global_rectWide);
  //Serial.printf("global_rectDepth: %u\n", global_rectDepth);
  //Serial.printf("global_rectHeight: %u\n", global_rectHeight);
  //Serial.printf("global_cilDiameter: %u\n", global_cilDiameter);
  //Serial.printf("global_cilHeight: %u\n", global_cilHeight);
  //Serial.printf("global_emptyTank: %u\n", global_emptyTank);
  //Serial.printf("global_fullTank: %u\n", global_fullTank);
  //Serial.printf("global_MaxTankLevelInLiter: %.2f\n", global_MaxTankLevelInLiter);
  //Serial.printf("distance: %d\n", distance);
  //Serial.printf("CurrentLiter: %d\n", CurrentLiter);
  //Serial.printf("distance %.2f\n", distance);
  //Serial.printf("CurrentLiterInPer: %.2f\n", CurrentLiterInPer);
  // Update the UI label with the calculated maximum tank level
  sprintf(text_buffer, "%d L / %d L", CurrentLiter, (int)global_MaxTankLevelInLiter);
  lv_label_set_text(ui_lblCurrentLiter, text_buffer);

  sprintf(text_buffer, "%.0f %%", CurrentLiterInPer);
  lv_label_set_text(ui_lblCurrentLiter1, text_buffer);


  // Update the UI bar with the current tank level
  lv_bar_set_value(ui_BarCurrentState, CurrentLiter, LV_ANIM_ON);

}



void UpdateChartActualLiter() {
  static ulong lastChartUpdate = 0;
  static lv_chart_series_t *distance_series = nullptr;
  int NumberOfPoints = 360; // Number of points in the chart
  static lv_coord_t liter_values[360] = {0}; // Store last 30 values
  //int NumberOfPoints = 12; // Number of points in the chart
  //static lv_coord_t liter_values[12] = {0}; // Store last 30 values
  static bool initialized = false;

  // Initialize the array with LV_CHART_POINT_NONE only once
  if (!initialized) {
    for (int i = 0; i < NumberOfPoints; ++i) {
      liter_values[i] = LV_CHART_POINT_NONE;
    }
    initialized = true;
  }

  ulong now_ms = millis();
  if (now_ms - lastChartUpdate >= 60000) { // 60 sec
    lastChartUpdate = now_ms;


    // Shift values left
    for (int i = 0; i < NumberOfPoints-1; i++) {
      liter_values[i] = liter_values[i + 1];
    }
    // Add current liter value
    liter_values[NumberOfPoints-1] = CurrentLiter;

    // Setup chart series if not done
    if (!distance_series) {
      distance_series = lv_chart_add_series(ui_ChartActualLiter, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    }

    lv_chart_set_point_count(ui_ChartActualLiter, NumberOfPoints);
    lv_chart_set_ext_y_array(ui_ChartActualLiter, distance_series, liter_values);

    lv_chart_refresh(ui_ChartActualLiter);
    Serial.println("Chart refreshed.");
  }
}

void UpdateChartActualLiterRightToLeft() {
  static ulong lastChartUpdate = 0;
  static lv_chart_series_t *distance_series = nullptr;
  static lv_coord_t liter_values[30];
  static bool initialized = false;

  // Initialize the array with LV_CHART_POINT_NONE only once
  if (!initialized) {
    for (int i = 0; i < 30; ++i) {
      liter_values[i] = LV_CHART_POINT_NONE;
    }
    initialized = true;
  }

  ulong now_ms = millis();
  if (now_ms - lastChartUpdate >= 10000) { // 10 sec
    lastChartUpdate = now_ms;

    // Shift values right (jobbról balra frissítés)
    for (int i = 29; i > 0; i--) {
      liter_values[i] = liter_values[i - 1];
    }
    // Add current liter value to the leftmost position
    liter_values[0] = CurrentLiter;

    // Setup chart series if not done
    if (!distance_series) {
      distance_series = lv_chart_add_series(ui_ChartActualLiter, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    }

    lv_chart_set_point_count(ui_ChartActualLiter, 30);
    lv_chart_set_ext_y_array(ui_ChartActualLiter, distance_series, liter_values);

    lv_chart_refresh(ui_ChartActualLiter);
    Serial.println("Chart refreshed.");
  }
}

void DistanceSensorRead() {
  static ulong lastUSSReadTime = 0;
  ulong currentUSSTime = millis();

  if (currentUSSTime - lastUSSReadTime >= 1000) {
    lastUSSReadTime = currentUSSTime;
      sensor.read();
      //int distance = sonar.ping_cm();
      //if (distance == 0) {
      //  sprintf(text_buffer, "Out of range");
      //} else {
      //  
      distance = sensor.ranging_data.range_mm; // Corrected missing semicolon
      std::string status = VL53L1X::rangeStatusToString(sensor.ranging_data.range_status); // Use std::string
      sprintf(text_buffer, "%s", status.c_str()); // Convert std::string to C-string
      //Serial.printf("Distance: %d mm, Status: %s\n", distance, status.c_str());
      if (status != "range valid" || distance <= 1 || distance > 4000) {
        Serial.println("Distance out of range or invalid status. Ignoring measurement.");
        //distance = 0;
      }
      

        sprintf(text_buffer, "%d mm", distance);
        lv_label_set_text(ui_lblActualDistanceValue, text_buffer);
        //lv_label_set_text(ui_lblCurrentLiter, text_buffer);



        static lv_coord_t distance_values[30] = {0}; // Array to store the last 50 distance values

        // Shift the values to the left
        for (int i = 0; i < 29; i++) {
            distance_values[i] = distance_values[i + 1];
        }

        // Add the new distance value to the end
        distance_values[29] = distance;


      // Update min and max distances
      if (global_minDistance == 0 || distance < global_minDistance) {
        global_minDistance = distance;
        sprintf(text_buffer, "%d mm", global_minDistance);
        lv_label_set_text(ui_lblMinDistanceValue, text_buffer);
      }

      if (global_maxDistance == 0 || distance > global_maxDistance) {
        global_maxDistance = distance;
        sprintf(text_buffer, "%d mm", global_maxDistance);
        lv_label_set_text(ui_lblMaxDistanceValue, text_buffer);
      }

      ReadTankLevelinLiters();
      UpdateChartActualLiter();
      //UpdateChartActualLiterRightToLeft();
  }
}



void ReinitializeVL53L1X() {
  static ulong lastReinitTime = 0;
  ulong currentTime = millis();

  if (!vl53l1x_initialized && (currentTime - lastReinitTime >= 5000)) {
      lastReinitTime = currentTime;
      sprintf(text_buffer, "N/A");
      lv_label_set_text(ui_lblActualDistanceValue, text_buffer);
      lv_label_set_text(ui_lblCurrentLiter, text_buffer);
      Serial.println("Attempting to reinitialize VL53L1X sensor...");
      if (sensor.init()) {
          Serial.println("VL53L1X sensor reinitialized successfully!");
          vl53l1x_initialized = true;
          sensor.setDistanceMode(VL53L1X::Long);
          sensor.setMeasurementTimingBudget(500000);
          sensor.startContinuous(500);
      } else {
          Serial.println("VL53L1X sensor reinitialization failed.");
      }
  }
}

void ReinitializeAHT10() {
  static ulong lastReinitTime = 0;
  ulong currentTime = millis();

  if (!aht10_initialized && (currentTime - lastReinitTime >= 5000)) {
      lastReinitTime = currentTime;
      sprintf(text_buffer, "N/A");
      lv_label_set_text(ui_lblTempValue, text_buffer);
      lv_label_set_text(ui_lblHumValue, text_buffer);
      Serial.println("Attempting to reinitialize AHT10 sensor...");
      if (aht.begin(&I2C_VL53L1X)) {
          Serial.println("AHT10 sensor reinitialized successfully!");
          aht10_initialized = true;
      } else {
          Serial.println("AHT10 sensor reinitialization failed.");
      }
  }
}

void printHeapStatus() {
  Serial.printf("Total heap: %d bytes\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));
  Serial.printf("Free heap: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  Serial.printf("Largest free block: %d bytes\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  Serial.printf("Minimum free heap ever: %d bytes\n", heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT));
}

void CalcMaxTanklevel() {
  // Calculate global_MaxTankLevelInLiter in liters (dm^3)
  float radius;
  float height;
  float width;
  float depth;
  //float height;
  if (global_tankType == 0) { // Cilinder
    // Volume = π * r^2 * h
    radius = global_cilDiameter / 200.0f; // Convert mm to dm
    height = global_cilHeight / 100.0f; // Convert mm to dm
    global_MaxTankLevelInLiter = 3.14159265f * radius * radius * height; // Volume in liters (dm^3)
  } else if (global_tankType == 1) { // Rectangle
    // Volume = width * depth * height
    width = global_rectWide / 100.0f; // Convert mm to dm
    depth = global_rectDepth / 100.0f; // Convert mm to dm
    height = global_rectHeight / 100.0f; // Convert mm to dm
    global_MaxTankLevelInLiter = width * depth * height; // Volume in liters (dm^3)
  }
  Serial.println("Calculating Max Tank Level...");
  Serial.printf("Width (dm): %.2f\n", width);
  Serial.printf("Depth (dm): %.2f\n", depth);
  Serial.printf("Height (dm): %.2f\n", height);
  Serial.printf("Calculated Volume (liters): %.2f\n", global_MaxTankLevelInLiter);
  // Update the UI label with the calculated maximum tank level
  //sprintf(text_buffer, "%d L", (int)global_MaxTankLevelInLiter);
  //lv_label_set_text(ui_lblMaxValue, text_buffer);
  // Set the maximum value of ui_BarCurrentState to global_MaxTankLevelInLiter
	lv_bar_set_range(ui_BarCurrentState, 0, (int)global_MaxTankLevelInLiter);
  int max_value = (int)global_MaxTankLevelInLiter;
  Serial.printf("max_value: %d\n", max_value);
  // Set the chart Y-axis range max to global_MaxTankLevelInLiter
  lv_chart_set_range(ui_ChartActualLiter, LV_CHART_AXIS_PRIMARY_Y, 0, max_value);
  lv_scale_set_range(ui_ChartActualLiter_Yaxis1,  0, max_value);
  // Update the chart Y-axis range max to global_MaxTankLevelInLiter
  //lv_scale_set_range(ui_ChartActualDistance_Yaxis1,  0, max_value);
  lv_chart_refresh(ui_ChartActualLiter); // Refresh the chart to display the updated values
  Serial.println("Chart refreshed.");


//        lv_chart_set_range(ui_ChartActualDistance, LV_CHART_AXIS_PRIMARY_Y, 0, max_value);
//        lv_scale_set_range(ui_ChartActualDistance_Yaxis1,  0, max_value);
//        lv_chart_refresh(ui_ChartActualDistance); // Refresh the chart to display the updated values



  // Debugging all variables within CalcMaxTanklevel
  Serial.println("Debugging Variables in CalcMaxTanklevel:");
  Serial.printf("global_tankType: %u\n", global_tankType);
  Serial.printf("global_rectWide: %u\n", global_rectWide);
  Serial.printf("global_rectDepth: %u\n", global_rectDepth);
  Serial.printf("global_rectHeight: %u\n", global_rectHeight);
  Serial.printf("global_cilDiameter: %u\n", global_cilDiameter);
  Serial.printf("global_cilHeight: %u\n", global_cilHeight);
  Serial.printf("global_emptyTank: %u\n", global_emptyTank);
  Serial.printf("global_fullTank: %u\n", global_fullTank);
  Serial.printf("global_MaxTankLevelInLiter: %.2f\n", global_MaxTankLevelInLiter);
}

void ReadTankParamsFromEEPROM() {
  // Tank params start at 193
  const int tankParamBase = 193;
  EEPROM.begin(512);

  uint8_t tankType = EEPROM.read(tankParamBase + 0);
  uint16_t rectWide, rectDepth, rectHeight, cilDiameter, cilHeight, emptyTank, fullTank;
  EEPROM.get(tankParamBase + 1, rectWide);
  EEPROM.get(tankParamBase + 3, rectDepth);
  EEPROM.get(tankParamBase + 5, rectHeight);
  EEPROM.get(tankParamBase + 7, cilDiameter);
  EEPROM.get(tankParamBase + 9, cilHeight);
  EEPROM.get(tankParamBase + 11, emptyTank);
  EEPROM.get(tankParamBase + 13, fullTank);

  // Set global variables if you have them (example names)
  global_tankType = tankType;
  global_rectWide = rectWide;
  global_rectDepth = rectDepth;
  global_rectHeight = rectHeight;
  global_cilDiameter = cilDiameter;
  global_cilHeight = cilHeight;
  global_emptyTank = emptyTank;
  global_fullTank = fullTank;

  // Update UI elements
  lv_dropdown_set_selected(ui_DropdownParamTankType, tankType);

  char buf[8];
  snprintf(buf, sizeof(buf), "%u", rectWide);
  lv_textarea_set_text(ui_TextAreaRectangleWide, buf);
  snprintf(buf, sizeof(buf), "%u", rectDepth);
  lv_textarea_set_text(ui_TextAreaRectangleDepth, buf);
  snprintf(buf, sizeof(buf), "%u", rectHeight);
  lv_textarea_set_text(ui_TextAreaRectangleHeight, buf);
  snprintf(buf, sizeof(buf), "%u", cilDiameter);
  lv_textarea_set_text(ui_TextAreaCilinderDiameter, buf);
  snprintf(buf, sizeof(buf), "%u", cilHeight);
  lv_textarea_set_text(ui_TextAreaCilinderHeight, buf);
  snprintf(buf, sizeof(buf), "%u", emptyTank);
  lv_textarea_set_text(ui_TextAreaEmptyTank, buf);
  snprintf(buf, sizeof(buf), "%u", fullTank);
  lv_textarea_set_text(ui_TextAreaFullTank, buf);

  EEPROM.end();

  Serial.println("Tank parameters loaded from EEPROM.");
  // Print loaded tank parameters to Serial
  Serial.printf("Tank Type: %u\n", global_tankType);
  Serial.printf("Rectangle Wide: %u\n", global_rectWide);
  Serial.printf("Rectangle Depth: %u\n", global_rectDepth);
  Serial.printf("Rectangle Height: %u\n", global_rectHeight);
  Serial.printf("Cylinder Diameter: %u\n", global_cilDiameter);
  Serial.printf("Cylinder Height: %u\n", global_cilHeight);
  Serial.printf("Empty Tank: %u\n", global_emptyTank);
  Serial.printf("Full Tank: %u\n", global_fullTank);

  // Call funcTankTypeChanged to update UI containers
  //funcTankTypeChanged(nullptr);
  if(global_tankType == 0) {
    funcTankTypeChangedCilinder(nullptr);
  } else if(global_tankType == 1) {
    funcTankTypeChangedRectangle(nullptr);
  } else {
    Serial.println("Invalid tank type loaded from EEPROM.");
  }
  CalcMaxTanklevel();

}


char GrapValueBuf[32] = "";            // aktuális érték
char LastGrapValueBuf[32] = "";        // utoljára kiírt érték
int labelboxposx = 0;            // labelbox pozíciója
int labelboxposy = 0;            // labelbox pozíciója


void chart_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * chart = lv_event_get_target_obj(e);

  static bool chart_clicked = false;
  static int LV_EVENT_DRAW_POST_END_Number = 0;

  if (code == LV_EVENT_CLICKED) {
    chart_clicked = true;
    Serial.println("Chart clicked, chart_clicked set to true.");
  }

  if(code == LV_EVENT_VALUE_CHANGED) {
    Serial.printf("[%lu] LV_EVENT_VALUE_CHANGED triggered\n", millis());
    lv_obj_invalidate(chart);
  }
  if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
    Serial.printf("[%lu] LV_EVENT_REFR_EXT_DRAW_SIZE triggered\n", millis());
    int32_t * s = (int32_t *)lv_event_get_param(e);
    *s = LV_MAX(*s, 20);
  }
  //else if(code == LV_EVENT_DRAW_POST_END) {
  else if (code == LV_EVENT_DRAW_POST_END && chart_clicked) {
    LV_EVENT_DRAW_POST_END_Number++;
    if(LV_EVENT_DRAW_POST_END_Number > 30) {
      chart_clicked = false;
      LV_EVENT_DRAW_POST_END_Number = 0;
    }
    Serial.printf("[%lu] LV_EVENT_DRAW_POST_END triggered\n", millis());
    //Serial.printf("[%lu] Chart clicked event detected.", millis());
    uint32_t id = lv_chart_get_pressed_point(chart);
    Serial.printf("[%lu] Pressed point id: %d\n", millis(), id);
    if(id == LV_CHART_POINT_NONE) return;

    lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);
    Serial.printf("ser: %p\n", (void*)ser);
    while(ser) {
      lv_point_t p;
      lv_chart_get_point_pos_by_id(chart, ser, id, &p);

      int32_t * y_array = lv_chart_get_y_array(chart, ser);

      Serial.print("y_array: ");
      for (int i = 0; i < lv_chart_get_point_count(chart); ++i) {
        Serial.printf("%d ", y_array[i]);
      }
      Serial.println();

      
      int32_t value = y_array[id];
      lv_snprintf(GrapValueBuf, sizeof(GrapValueBuf), "%d L", value);
      Serial.printf("[%lu] Drawing value: %s at point (%d, %d)\n", millis(), GrapValueBuf, p.x, p.y);

      
          labelboxposx = p.x - lv_obj_get_width(ui_PanelGraphValue) / 2;
          labelboxposy = p.y - lv_obj_get_height(ui_PanelGraphValue) - 10; // kicsit fölé

          // Y pozíció korlátozása -30 és 80 közé
          if (labelboxposy < -30) labelboxposy = -30;
          if (labelboxposy > 80)  labelboxposy = 80;



      ser = lv_chart_get_series_next(chart, ser);
    }
  }
  else if(code == LV_EVENT_RELEASED) {
    Serial.println("LV_EVENT_RELEASED triggered");
    lv_obj_add_flag(ui_PanelGraphValue, LV_OBJ_FLAG_HIDDEN);  // panel elrejtése
    lv_obj_invalidate(chart);
    chart_clicked = false;
  }
}

void setupChart() {

lv_obj_t * scale = lv_scale_create(lv_obj_get_parent(ui_ChartActualLiter));
lv_obj_set_size(scale, lv_pct(80), 100);
lv_scale_set_mode(scale, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
lv_obj_center(scale);
lv_obj_set_size(scale, lv_obj_get_width(ui_ChartActualLiter)-18, 25); // Szélesség: a grafikon szélessége, magasság: 25 pixel
lv_obj_align_to(scale, ui_ChartActualLiter, LV_ALIGN_OUT_BOTTOM_MID, 0, 0); // Igazítás a grafikon alá, 1 pixel távolsággal
lv_scale_set_label_show(scale, true);

lv_scale_set_total_tick_count(scale, 7);
lv_scale_set_major_tick_every(scale, 1);

lv_obj_set_style_length(scale, 1, LV_PART_ITEMS);
lv_obj_set_style_length(scale, 3, LV_PART_INDICATOR);
lv_scale_set_range(scale, 6, 0);



lv_obj_set_style_bg_opa(ui_PanelGraphValue, LV_OPA_60, 0);
lv_obj_set_style_border_width(ui_PanelGraphValue, 0, 0);
// Állítsd be a grafikon típusát
lv_chart_set_type(ui_ChartActualLiter, LV_CHART_TYPE_LINE); // Csak vonal
lv_obj_set_style_size(ui_ChartActualLiter, 0, 0, LV_PART_INDICATOR); // Pontméret 0, így nem látszanak a pontok


Serial.println("setupChart() called.");

    if (!ui_ChartActualLiter) {
        Serial.println("Error: ui_ChartActualLiter is not initialized.");
        return;
    }
    Serial.println("ui_ChartActualLiter is initialized.");

    lv_obj_add_flag(ui_ChartActualLiter, LV_OBJ_FLAG_CLICKABLE); // Engedélyezi a kattintást

    // Register the event callback for the chart
    lv_obj_add_event_cb(ui_ChartActualLiter, chart_event_cb, LV_EVENT_ALL, NULL);


    // Refresh the chart
    lv_chart_refresh(ui_ChartActualLiter);
    Serial.println("Chart refreshed.");
}


void freeLVGLMemory() {
  Serial.println("Freeing LVGL memory...");
  lv_obj_clean(lv_scr_act()); // Törli az aktuális képernyő összes objektumát
  lv_mem_monitor_t mem_mon;
  lv_mem_monitor(&mem_mon);
  Serial.printf("LVGL Total: %d bytes, Free: %d bytes, Largest Free: %d bytes\n",
                (int)mem_mon.total_size, (int)mem_mon.free_size, (int)mem_mon.free_biggest_size);
  lv_deinit(); // LVGL deinitializálása
  delay(3000); // Adj időt a memória felszabadítására
}

void checkForUpdate() {
  Serial.println("--------------------------------");
  Serial.println("Checking for firmware updates...");
  Serial.printf("Free heap before OTA: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

//  // Optionally deinitialize LVGL to free memory
//  if (lvgl_enabled) {
//    Serial.println("Deinitializing LVGL to free memory...");
//    freeLVGLMemory();
//    //lvgl_enabled = false;
//    Serial.printf("Free heap after LVGL deinit: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
//}

  const char* versionUrl = "https://raw.githubusercontent.com/Kislac/water-tank-monitor/main/data/version.txt";

  WiFiClientSecure client;
  client.setInsecure(); // Skip certificate validation

  HTTPClient http;
  if (http.begin(client, versionUrl)) {
      int httpCode = http.GET();

      if (httpCode == HTTP_CODE_OK) {
          String version = http.getString();
          version.trim();
          Serial.printf("Remote version.txt content: '%s'\n", version.c_str());

          if (version.toInt() > build_number) {
              Serial.println("New firmware available. Updating...");
              // Call OTA update process here
          } else {
              Serial.println("Firmware is up to date.");
          }
      } else {
          Serial.printf("HTTP error: %d\n", httpCode);
      }

      http.end();
  } else {
      Serial.println("HTTPS connection failed.");
  }

  // Reinitialize LVGL after OTA/check
  //if (!lvgl_enabled) {
  //  Serial.println("Reinitializing LVGL...");
  //  smartdisplay_init();
  //  ui_init();
  //  lvgl_enabled = true;
  //  Serial.printf("Free heap after LVGL reinit: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  //}

  Serial.println("--------------------------------");
  Serial.println("Firmware update check completed.");
}


// Függvény, amely lekérdezi a legfrissebb GitHub release verziót és összehasonlítja a build_number-rel
bool isNewerFirmwareAvailable_GitHub(int &latest_build_number, String &latest_tag, String &download_url) {
  const char* githubApiUrl = "https://api.github.com/repos/Kislac/water-tank-monitor/releases/latest";
  WiFiClientSecure client;
  client.setInsecure(); // Skip certificate validation

  HTTPClient http;
  latest_build_number = 0;
  latest_tag = "";
  download_url = "";

  Serial.println("Checking latest release from GitHub API...");
  if (http.begin(client, githubApiUrl)) {
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      // Parse JSON
      StaticJsonDocument<2048> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        // Get tag_name or name (e.g. "v1.1.508")
        if (doc.containsKey("tag_name")) {
          latest_tag = doc["tag_name"].as<String>();
        } else if (doc.containsKey("name")) {
          latest_tag = doc["name"].as<String>();
        }
        // Try to extract build number from tag (assume format v1.1.508)
        int lastDot = latest_tag.lastIndexOf('.');
        if (lastDot > 0) {
          latest_build_number = latest_tag.substring(lastDot + 1).toInt();
        }
        // Find firmware.bin download URL
        if (doc.containsKey("assets") && doc["assets"].is<JsonArray>()) {
          for (JsonObject asset : doc["assets"].as<JsonArray>()) {
            String name = asset["name"] | "";
            if (name == "firmware.bin") {
              download_url = asset["browser_download_url"].as<String>();
              break;
            }
          }
        }
        Serial.printf("Latest tag: %s, build: %d, url: %s\n", latest_tag.c_str(), latest_build_number, download_url.c_str());
        http.end();
        return (latest_build_number > build_number);
      } else {
        Serial.println("JSON parse error.");
      }
    } else {
      Serial.printf("HTTP error: %d\n", httpCode);
    }
    http.end();
  } else {
    Serial.println("HTTPS connection failed.");
  }
  return false;
}


void ReadBacklightSettingsFromEEPROM() {
  EEPROM.begin(512);
  uint8_t mode = EEPROM.read(300); // 1 = Manual, 0 = Automatic
  uint8_t value = EEPROM.read(301); // 0-100

  Serial.printf("ReadBacklightSettingsFromEEPROM: mode=%u, value=%u\n", mode, value);

  if (mode == 0) {
    lv_obj_clear_state(ui_switchManualAutomatic, LV_STATE_CHECKED); // Manual mode
  } else {
    lv_obj_add_state(ui_switchManualAutomatic, LV_STATE_CHECKED); // Automatic mode
  }

  lv_slider_set_value(ui_LigthSensorSlider, value, LV_ANIM_OFF);
  float lcd_set_backlight = (float)value / 100;
  smartdisplay_lcd_set_backlight(max(lcd_set_backlight, 0.01f));
  sprintf(text_buffer, "%d%%", value);
  lv_label_set_text(ui_lblLigthSensorSliderValue, text_buffer);

  EEPROM.end();
}


void check_and_update_graph_value() {
  if (strcmp(GrapValueBuf, LastGrapValueBuf) != 0 && lv_tabview_get_tab_act(ui_MainTabView) == 0) {
    Serial.printf("[DEBUG] Graph value changed: %s -> %s\n", LastGrapValueBuf, GrapValueBuf);
    lv_label_set_text(ui_GraphValue, GrapValueBuf);
    strcpy(LastGrapValueBuf, GrapValueBuf);

    lv_obj_set_pos(ui_PanelGraphValue, labelboxposx, labelboxposy); // panel pozicionálása a megnyomott pont fölé
    Serial.printf("[DEBUG] Panel position set to: x=%d, y=%d\n", labelboxposx, labelboxposy);
    //lv_obj_set_style_bg_color(ui_PanelGraphValue, lv_palette_main(LV_PALETTE_GREY), 0); // panel színének beállítása
     // Panel megjelenítése
    lv_obj_clear_flag(ui_PanelGraphValue, LV_OBJ_FLAG_HIDDEN);
    Serial.println("[DEBUG] Panel shown.");
  }
}



void checkFreeHeapMemory() {
  static ulong lastHeapCheck = 0;
  if (millis() - lastHeapCheck >= 2000) {
    lastHeapCheck = millis();
    Serial.printf("Free heap: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  }
}


void setup() {
  Serial.begin(115200);

  //wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  WiFi.setSleep(true);  // Engedélyezd a WiFi energiatakarékos módját

  // Wait until connected to WiFi (timeout 10 seconds)
  Serial.print("Connecting to WiFi");
  unsigned long wifi_start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifi_start < 10000) {
    delay(100);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected.");
  } else {
    Serial.println("\nWiFi connection timeout.");
  }


//  checkForUpdate();
  // Check if newer firmware is available on GitHub
  int latest_build_number = 0;
  String latest_tag, download_url;
  if (isNewerFirmwareAvailable_GitHub(latest_build_number, latest_tag, download_url)) {
    Serial.printf("Newer firmware available: %s (build %d)\n", latest_tag.c_str(), latest_build_number);
    Serial.printf("Download URL: %s\n", download_url.c_str());
    // You can trigger OTA update here if desired
  } else {
    Serial.printf("Latest firmware on github: %s (build %d)\n", latest_tag.c_str(), latest_build_number);
    Serial.printf("Download URL: %s\n", download_url.c_str());
    Serial.println("No newer firmware available on GitHub.");
  }

  // Initialize I2C bus for VL53L1X
  I2C_VL53L1X.begin(VL53L1X_SDA, VL53L1X_SCL);
  I2C_VL53L1X.setClock(100000); // use 400 kHz I2C

  sensor.setBus(&I2C_VL53L1X);  // Set the I2C bus for VL53L1X
  sensor.setTimeout(1000);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
} else {
  Serial.println("VL53L1X sensor initialized successfully!");
  vl53l1x_initialized = true;
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(500000);
  sensor.startContinuous(500);
}



  // Initialize the AHT10 sensor on the custom I2C bus
  if (!aht.begin(&I2C_VL53L1X)) {
    Serial.println("AHT10 initialization failed.");
  } else {
    Serial.println("AHT10 sensor initialized.");
    aht10_initialized = true;
  }

  smartdisplay_init();
  Serial.println("smartdisplay_init() initialized.");
  __attribute__((unused)) auto disp = lv_disp_get_default();
   lv_disp_set_rotation(disp, LV_DISPLAY_ROTATION_90);
  // lv_disp_set_rotation(disp, LV_DISP_ROT_180);
  // lv_disp_set_rotation(disp, LV_DISP_ROT_270);
  Serial.println("Starting ui_init()...");
  ui_init();
  //ui_Main_Screen_screen_init();
	//lv_scr_load(ui_Main_Screen);

  Serial.println("Starting the program...");

//  // Set the screen brightness to 50% initially
//  smartdisplay_lcd_set_backlight(max(((float)(SCREEN_INITIAL_BRIGHTNESS) / 100), 0.01f));
//  // Update the ui_LigthSensorSlider to reflect the 50% brightness
//  lv_slider_set_value(ui_LigthSensorSlider, SCREEN_INITIAL_BRIGHTNESS, LV_ANIM_OFF);
//  sprintf(text_buffer, "%d%%", SCREEN_INITIAL_BRIGHTNESS);
//  lv_label_set_text(ui_lblLigthSensorSliderValue, text_buffer);
//
//  // Set the switch to automatic mode initially LV_STATE_CHECKED
//  lv_obj_add_state(ui_switchManualAutomatic, LV_STATE_CHECKED); //automatic mode
//  //lv_obj_add_state(ui_switchManualAutomatic, LV_STATE_DEFAULT); //manual mode
  ReadBacklightSettingsFromEEPROM();


  // Init the Wifi Signal images. Important to init after ui_init()
  initWifiSignalImages();
  initVariables();
  

  initializeBuildInfo();
  ReadMQTTSettingsFromEEPROM();
  ReadTankParamsFromEEPROM();
  //CalcMaxTanklevel();

  setupChart();
  
  //checkForUpdate();  // Ellenőrzés induláskor


}



void loop() {
  // put your main code here, to run repeatedly:
    now = millis();

    checkFreeHeapMemory();

  if (FW_Update_Check == false && lv_scr_act() == ui_Main_Screen) {
    runtimecalc();
    AutoBacklight();
    RefreshWifiParameters();
    DateAndTimeHandling();
    CheckWifiandInternetStatus();
    check_and_update_graph_value();
    aht10_initialized ? ReadAHT10() : ReinitializeAHT10();
    vl53l1x_initialized ? DistanceSensorRead() : ReinitializeVL53L1X();

    if (!client.connected()) MQTT_setup();
      client.loop();

    publishMQTTSensoraDatas();
  }  
    


    if (lvgl_enabled) {
      // Update the ticker
      lv_tick_inc(now - lv_last_tick);
      lv_last_tick = now;
      // Update the UI
      lv_timer_handler();
    }





}

