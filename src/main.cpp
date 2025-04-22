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
float global_MaxTankLevel = 0;
float global_tankVolume = 0.0f;

int distance = 0;

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
  sprintf(device_sw_version, "v1.0.%d", build_number);
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

      // Refresh Channel
      char channel_text[16];
      snprintf(channel_text, sizeof(channel_text), "Ch: %d", WiFi.channel());
      lv_label_set_text(ui_lblWifiChannel, channel_text);

      lv_label_set_text(ui_lblWifiSecurity, security.c_str());

      
      
        } else {
      // Clear labels if not connected
      lv_label_set_text(ui_lblWifiSSID, "N/A");
      lv_label_set_text(ui_lblWifiIP, "N/A");
      lv_label_set_text(ui_lblWifiRSSI, "N/A");
      lv_label_set_text(ui_lblWifiChannel, "N/A");
      lv_label_set_text(ui_lblWifiSecurity, "N/A");
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
    lv_label_set_text(ui_lblTime, datetime_text);
    lv_label_set_text(ui_lblDataNTime, datetime_text);

  } else {
    lv_label_set_text(ui_lblTime, "Time Unavailable");
    lv_label_set_text(ui_lblDataNTime, "Time Unavailable");
  }
}
  
}

void AutoBacklight(){
  #ifdef BOARD_HAS_CDS
  static ulong last_AutoBacklight = 0;
  static int last_slider_value = 0;

  if (millis() - last_AutoBacklight >= 100) { // Refresh every 100ms
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
        last_slider_value = slider_value;
        //int slider_value = lv_slider_get_value(ui_LigthSensorSlider);
        float lcd_set_backlight = (float)slider_value / 100;
        Serial.printf("slider_value: %d | lcd_set_backlight: %.2f\n", slider_value, lcd_set_backlight);
        smartdisplay_lcd_set_backlight(max(lcd_set_backlight, 0.01f));
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
  Serial.print("RSSI discovery publish result: ");
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
  Serial.print("Temperature discovery publish result: ");
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
  Serial.print("Humidity discovery publish result: ");
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
  Serial.print("Distance discovery publish result: ");
  Serial.println(result_dist ? "OK" : "FAILED");
  Serial.println("Discovery messages published.");
}

bool MQTT_Connect() {
  if (client.connect("esp32_water_tank", global_mqtt_user, global_mqtt_password)) {
    Serial.println("MQTT kapcsolat sikeres!");
    //client.subscribe("esp32/water"); Ez a fogadáshoz kell

    // Discovery topicok küldése
    publishDiscoveryMessages();
    return true;
  } else {
    Serial.print("MQTT kapcsolat sikertelen, hiba kód: ");
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
          Serial.println("Kapcsolódás sikeres!");
          break;
        } else {
          
            Serial.print("MQTT kapcsolat sikertelen, hiba kód: ");
            Serial.print(client.state());
            Serial.println(". Újrapróbálkozás 5 másodperc múlva...");
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

    lv_textarea_set_text(ui_TextAreaMQTTServer, global_mqtt_server);
    lv_textarea_set_text(ui_TextAreaMQTTuser, global_mqtt_user);
    lv_textarea_set_text(ui_TextAreaMQTTPassword, global_mqtt_password);

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
  // Calculate global_MaxTankLevel in liters (dm^3)
  int CurrentLiter;
	if (global_tankType == 0) { // Cilinder
		// Volume = π * r^2 * h
		float radius = global_cilDiameter / 200.0f; // mm
    float volume_dm3 = 3.14159265f * (radius / 100.0f) * (radius / 100.0f) * ((global_fullTank / 100.0f) - (distance / 100.0f));
    
  } else if (global_tankType == 1) { // Rectangle
		// Volume = width * depth * height
		float volume_dm3 = global_rectWide/100 * global_rectDepth * (global_fullTank-distance);
	}
  CurrentLiter = static_cast<int>(volume_dm3);
  float CurrentLiterInPer = CurrentLiter /  global_MaxTankLevel;
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
  //Serial.printf("global_MaxTankLevel: %.2f\n", global_MaxTankLevel);
  //Serial.printf("distance: %d\n", distance);
  //Serial.printf("CurrentLiter: %d\n", CurrentLiter);
  //Serial.printf("CurrentLiterInPer: %.2f\n", CurrentLiterInPer);
  // Update the UI label with the calculated maximum tank level
  sprintf(text_buffer, "%u L", CurrentLiter);
  lv_label_set_text(ui_lblCurrentLiter, text_buffer);

  sprintf(text_buffer, "%.2f %%", CurrentLiterInPer);
  lv_label_set_text(ui_lblCurrentLiter1, text_buffer);

  // Set the maximum value of ui_BarCurrentState to global_MaxTankLevel
	lv_bar_set_range(ui_BarCurrentState, 0, (int)global_MaxTankLevel);
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
      Serial.printf("Distance: %d mm, Status: %s\n", distance, status.c_str());
      if (status != "range valid" || distance <= 1 || distance > 4500) {
        Serial.println("Distance out of range or invalid status. Ignoring measurement.");
        //distance = 0;
      }
      

        sprintf(text_buffer, "%d mm", distance);
        lv_label_set_text(ui_lblActualDistanceValue, text_buffer);
        //lv_label_set_text(ui_lblCurrentLiter, text_buffer);


        //
        //lv_label_set_text(ui_lblDistanceStatus, text_buffer);

        static int last8Distances[8] = {0}; // Array to store the last 8 distance values
        // Shift the values to the left
        for (int i = 0; i < 7; i++) {
            last8Distances[i] = last8Distances[i + 1];
        }
        // Add the new distance value to the end
        last8Distances[7] = distance;

        // Format the last 8 distances into the text buffer
        snprintf(text_buffer, sizeof(text_buffer), 
            "%d mm\n%d mm\n%d mm\n%d mm\n%d mm\n%d mm\n%d mm\n%d mm",
            last8Distances[0], last8Distances[1], last8Distances[2], last8Distances[3],
            last8Distances[4], last8Distances[5], last8Distances[6], last8Distances[7]);

        //lv_label_set_text(ui_lblLast8Distance, text_buffer);


        static lv_coord_t distance_values[30] = {0}; // Array to store the last 50 distance values

        // Shift the values to the left
        for (int i = 0; i < 29; i++) {
            distance_values[i] = distance_values[i + 1];
        }

        // Add the new distance value to the end
        distance_values[29] = distance;

        // Update the chart with the new values
//        lv_chart_set_point_count(ui_ChartActualDistance, 30); // Ensure the chart has 50 points
//        static lv_chart_series_t *ui_ChartActualDistance_series = nullptr;
//        if (ui_ChartActualDistance_series == nullptr) {
//            ui_ChartActualDistance_series = lv_chart_add_series(ui_ChartActualDistance, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
//        }
//        //static lv_chart_series_t * ui_ChartActualDistance_series = nullptr;
//        //ui_ChartActualDistance_series = lv_chart_add_series(ui_ChartActualDistance, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
//        //if (status != "range valid") {
//        //  ui_ChartActualDistance_series = lv_chart_add_series(ui_ChartActualDistance, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
//        //} else {
//        //  ui_ChartActualDistance_series = lv_chart_add_series(ui_ChartActualDistance, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
//        //}
//
//        lv_chart_set_ext_y_array(ui_ChartActualDistance, ui_ChartActualDistance_series, distance_values);
//        // Dynamically adjust the Y-axis range based on the maximum value in distance_values
//        lv_coord_t max_value = 100; // Minimum maximum value
//        for (int i = 0; i < 30; i++) {
//            if (distance_values[i] > max_value) {
//          max_value = distance_values[i];
//            }
//        }
//        max_value = min(max_value, 4500); // Cap the maximum value at 4500
//        lv_chart_set_range(ui_ChartActualDistance, LV_CHART_AXIS_PRIMARY_Y, 0, max_value);
//        lv_scale_set_range(ui_ChartActualDistance_Yaxis1,  0, max_value);
//        lv_chart_refresh(ui_ChartActualDistance); // Refresh the chart to display the updated values

        // Update the ui_BarCurrentState with the current distance value
        //lv_bar_set_value(ui_BarCurrentState, distance, LV_ANIM_ON);
      
//      else {
//        Serial.println("Out of range");
//        lv_chart_set_point_count(ui_ChartActualDistance, 50); // Ensure the chart has 50 points
//        static lv_chart_series_t * ui_ErrorChart_series = lv_chart_add_series(ui_ChartActualDistance, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
//        static lv_coord_t error_values[50] = {0}; // Array to store the last 50 error values
//
//        // Shift the values to the left
//        for (int i = 0; i < 49; i++) {
//            error_values[i] = error_values[i + 1];
//        }
//        // Add a 0 value to the end for invalid measurement
//        error_values[49] = 0;
//
//        // Update the chart with the new error values
//        lv_chart_set_ext_y_array(ui_ChartActualDistance, ui_ErrorChart_series, error_values);
//        lv_chart_refresh(ui_ChartActualDistance); // Refresh the chart to display the updated values
//      }
      
      //static int minDistance = INT_MAX; // Initialize to maximum possible value
      //static int maxDistance = INT_MIN; // Initialize to minimum possible value

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
  // Calculate global_MaxTankLevel in liters (dm^3)
  float radius;
  float height;
  float width;
  float depth;
  //float height;
  if (global_tankType == 0) { // Cilinder
    // Volume = π * r^2 * h
    radius = global_cilDiameter / 200.0f; // Convert mm to dm
    height = global_cilHeight / 100.0f; // Convert mm to dm
    global_MaxTankLevel = 3.14159265f * radius * radius * height; // Volume in liters (dm^3)
  } else if (global_tankType == 1) { // Rectangle
    // Volume = width * depth * height
    width = global_rectWide / 100.0f; // Convert mm to dm
    depth = global_rectDepth / 100.0f; // Convert mm to dm
    height = global_rectHeight / 100.0f; // Convert mm to dm
    global_MaxTankLevel = width * depth * height; // Volume in liters (dm^3)
  }
  Serial.println("Calculating Max Tank Level...");
  Serial.printf("Width (dm): %.2f\n", width);
  Serial.printf("Depth (dm): %.2f\n", depth);
  Serial.printf("Height (dm): %.2f\n", height);
  Serial.printf("Calculated Volume (liters): %.2f\n", global_MaxTankLevel);
  // Update the UI label with the calculated maximum tank level
  sprintf(text_buffer, "%d L", (int)global_MaxTankLevel);
  lv_label_set_text(ui_lblMaxValue, text_buffer);
  // Set the maximum value of ui_BarCurrentState to global_MaxTankLevel
	lv_bar_set_range(ui_BarCurrentState, 0, (int)global_MaxTankLevel);
  
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
  Serial.printf("global_MaxTankLevel: %.2f\n", global_MaxTankLevel);
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
  funcTankTypeChanged(nullptr);
  CalcMaxTanklevel();

}





void setup() {
  Serial.begin(115200);

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

  Serial.println("Starting the program...");

  // Set the screen brightness to 50% initially
  smartdisplay_lcd_set_backlight(max(((float)(SCREEN_INITIAL_BRIGHTNESS) / 100), 0.01f));
  // Update the ui_LigthSensorSlider to reflect the 50% brightness
  lv_slider_set_value(ui_LigthSensorSlider, SCREEN_INITIAL_BRIGHTNESS, LV_ANIM_OFF);
  sprintf(text_buffer, "%d%%", SCREEN_INITIAL_BRIGHTNESS);
  lv_label_set_text(ui_lblLigthSensorSliderValue, text_buffer);

  // Set the switch to automatic mode initially LV_STATE_CHECKED
  lv_obj_add_state(ui_switchManualAutomatic, LV_STATE_CHECKED); //automatic mode
  //lv_obj_add_state(ui_switchManualAutomatic, LV_STATE_DEFAULT); //manual mode



  //wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  WiFi.setSleep(true);  // Engedélyezd a WiFi energiatakarékos módját
  // Init the Wifi Signal images. Important to init after ui_init()
  initWifiSignalImages();
  initVariables();
  

  initializeBuildInfo();
  ReadMQTTSettingsFromEEPROM();
  ReadTankParamsFromEEPROM();
  //CalcMaxTanklevel();


  Serial.begin(115200);

  if (psramFound()) {
      Serial.println("PSRAM is available!");
      Serial.printf("Total PSRAM: %d bytes\n", ESP.getPsramSize());
      Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
  } else {
      Serial.println("PSRAM is NOT available.");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
    now = millis();
    static ulong lastHeapPrint = 0;
//    if (now - lastHeapPrint >= 2000) {
//      lastHeapPrint = now;
//      printHeapStatus();
//      lv_mem_monitor_t mem_mon;
//      lv_mem_monitor(&mem_mon);
//      printf("Total: %d bytes, Free: %d bytes, Largest Free: %d bytes\n",
//        (int)mem_mon.total_size, (int)mem_mon.free_size, (int)mem_mon.free_biggest_size);
//    }

    runtimecalc();
    AutoBacklight();
    RefreshWifiParameters();
    DateAndTimeHandling();
    CheckWifiandInternetStatus();

    aht10_initialized ? ReadAHT10() : ReinitializeAHT10();
    vl53l1x_initialized ? DistanceSensorRead() : ReinitializeVL53L1X();

    if (!client.connected()) MQTT_setup();
      client.loop();

    publishMQTTSensoraDatas();
    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;
    // Update the UI
    lv_timer_handler();
}

