// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: WaterTank
#include "globals.h"
#include "ui.h"
#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <WiFi.h>
#include <FS.h>     // Include the SPIFFS library for Version handling
#include <SPIFFS.h> // Include the SPIFFS library for Version handling
#include <EEPROM.h>




void funcRotateScreen(lv_event_t * e){
	static bool rotated = false;
	rotated = !rotated; // Toggle rotation state
	lv_disp_set_rotation(lv_disp_get_default(), rotated ? LV_DISPLAY_ROTATION_270 : LV_DISPLAY_ROTATION_90);
	Serial.printf("Screen rotated to %s\n", rotated ? "180°" : "0°");
  }

void funcSWReset(lv_event_t * e){
Serial.println("Software reset triggered.");
// Perform a software reset
esp_restart();
}

void funcResetWifi(lv_event_t * e){
	WiFi.disconnect(true, true); // Disconnect and erase WiFi credentials
	
	WiFi.mode(WIFI_OFF);   // Turn off WiFi to reset the state
	delay(100);            // Small delay to ensure the reset takes effect
	WiFi.mode(WIFI_STA);   // Set WiFi mode back to station mode
	// Clear labels if not connected
	lv_label_set_text(ui_lblWifiSSID, "N/A");
	lv_label_set_text(ui_lblWifiIP, "N/A");
	lv_label_set_text(ui_lblWifiRSSI, "N/A");
	lv_label_set_text(ui_lblWifiChannel, "N/A");
	lv_label_set_text(ui_lblWifiSecurity, "N/A");
  }

void funcWifiScan(lv_event_t * e)
{
	Serial.println("funcWifiScan");
	Serial.println("Starting WiFi scan...");
  
	lv_obj_clear_flag(ui_panelScanningWifi, LV_OBJ_FLAG_HIDDEN);
	//now = millis();
	//lv_tick_inc(now - lv_last_tick);
	//Serial.printf("now: %lld, lv_last_tick: %lld\n", now, lv_last_tick);
	//lv_last_tick = now;
	lv_obj_clean(ui_PanelWifiList);
	lv_timer_handler(); // Refresh the LVGL display to reflect the changes
	lv_refr_now(NULL);  // Azonnali frissítés az LVGL-ben
  
  
	
	WiFi.scanDelete(); // fontos, ha előzőleg futott
	Serial.printf("WiFi Scan Deleted");
	//WiFi.scanNetworks();  //
	int n = WiFi.scanNetworks(); // Perform a WiFi scan
	Serial.printf("Found %d networks\n", n);
  
	if (n == 0) {
	  Serial.println("No networks found");
	  lv_obj_t *btn = lv_btn_create(ui_PanelWifiList);
	  lv_obj_t *label = lv_label_create(btn);
	  lv_label_set_text(label, "No networks found");
	  lv_obj_center(label);
	} else {
	  //lv_obj_add_flag(ui_panelScanningWifi, LV_OBJ_FLAG_HIDDEN);
  
	  // Create a label to display the number of WiFi networks found
	  lv_obj_t *ui_LabelWifiCount = lv_label_create(ui_PanelWifiList);
	  lv_label_set_text_fmt(ui_LabelWifiCount, "Found %d networks. Closest 8 listed:", n);
	  //lv_obj_set_style_text_font(ui_LabelWifiCount, &lv_font_montserrat_8, 0); // Set font size to small
	  lv_obj_set_style_text_align(ui_LabelWifiCount, LV_TEXT_ALIGN_LEFT, 0);
	  lv_obj_align(ui_LabelWifiCount, LV_ALIGN_TOP_LEFT, 10, 15); // Position the label at the top-left corner
  
	  for (int i = 0; i < 8; ++i) {
		
		String ssid = WiFi.SSID(i);
		char ssid_text[16];
		sprintf(ssid_text, "%s", ssid.c_str());
		int rssi = WiFi.RSSI(i);
		int channel = WiFi.channel(i);
		wifi_auth_mode_t authMode = WiFi.encryptionType(i);
  
		
		switch (authMode) {
		  case WIFI_AUTH_OPEN: security = "Open"; break;
		  case WIFI_AUTH_WEP: security = "WEP"; break;
		  case WIFI_AUTH_WPA_PSK: security = "WPA"; break;
		  case WIFI_AUTH_WPA2_PSK: security = "WPA2"; break;
		  case WIFI_AUTH_WPA_WPA2_PSK: security = "WPA/WPA2"; break;
		  case WIFI_AUTH_WPA2_ENTERPRISE: security = "WPA2-Enterprise"; break;
		  default: security = "Unknown"; break;
		}
  
		Serial.printf("%d: %s (%d dBm, Ch: %d, Sec: %s)\n", i + 1, ssid.c_str(), rssi, channel, security.c_str());
  
  
		Serial.print("--A");
		if (ui_PanelWifiList == nullptr) {
			Serial.println("Error: ui_PanelWifiList is not initialized.");
			// Initialize ui_PanelWifiList to avoid null pointer dereference
			ui_PanelWifiList = lv_obj_create(lv_scr_act());
			lv_obj_set_size(ui_PanelWifiList, lv_pct(100), lv_pct(100));
			lv_obj_set_align(ui_PanelWifiList, LV_ALIGN_CENTER);
		}
		Serial.print("--B");
		// Create a button for each WiFi network
		lv_obj_t *ui_Button_WifiSSID = lv_btn_create(ui_PanelWifiList);
		lv_obj_set_width(ui_Button_WifiSSID, lv_pct(100));
		lv_obj_set_height(ui_Button_WifiSSID, LV_SIZE_CONTENT);
		lv_obj_set_align(ui_Button_WifiSSID, LV_ALIGN_CENTER);
		lv_obj_set_flex_flow(ui_Button_WifiSSID, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(ui_Button_WifiSSID, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  
		Serial.print("--C");
  
		// Create the first label for SSID
		lv_obj_t *ui_LabelSSID = lv_label_create(ui_Button_WifiSSID);
		Serial.print("-C1");
		lv_obj_set_width(ui_LabelSSID, lv_pct(70));
		Serial.print("-C2");
		lv_obj_set_height(ui_LabelSSID, LV_SIZE_CONTENT);
		Serial.print("-C3");
		lv_obj_set_align(ui_LabelSSID, LV_ALIGN_CENTER);
		Serial.print("-C4");
		lv_label_set_long_mode(ui_LabelSSID, LV_LABEL_LONG_SCROLL);
		Serial.print("-C5");
		lv_obj_set_style_text_align(ui_LabelSSID, LV_TEXT_ALIGN_LEFT, 0);
		Serial.print("-C6");
		lv_label_set_text(ui_LabelSSID, ssid_text); // Set the SSID text dynamically
  
		Serial.print("--D");
  
		// Create the second label for RSSI
		lv_obj_t *ui_LabelRSSI = lv_label_create(ui_Button_WifiSSID);
		lv_obj_set_width(ui_LabelRSSI, lv_pct(30));
		lv_obj_set_height(ui_LabelRSSI, LV_SIZE_CONTENT);
		lv_obj_set_align(ui_LabelRSSI, LV_ALIGN_RIGHT_MID);
		char rssi_text[16];
		snprintf(rssi_text, sizeof(rssi_text), "%d dBm", rssi);
		lv_label_set_text(ui_LabelRSSI, rssi_text);
		
		Serial.print("--E");
  
		// Add an event callback to handle button clicks
		lv_obj_add_event_cb(ui_Button_WifiSSID, [](lv_event_t *e) {
		  Serial.print("-E1");
		  //lv_obj_t *btn = lv_event_get_target(e);
		  lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e); 
		  Serial.print("-E2");
		  lv_obj_t *label_ssid = lv_obj_get_child(btn, 0); // Get the first child (SSID label)
		  Serial.print("-E3");
		  const char *ssid = lv_label_get_text(label_ssid);
		  Serial.print("-E4");
		  lv_label_set_text(ui_lblWifiSSIDToBeConnect, ssid); // Set the SSID to the target label
		  Serial.print("-E5");
		  Serial.printf("Selected SSID: %s\n", ssid);
		  Serial.print("-E6");
		  lv_textarea_set_text(ui_textareaWifiPassword, "");
  
		  // Change screen to "ConnectToWifi"
		  Serial.print("-E7");
		  lv_scr_load(ui_ConnectToWifi);
		  Serial.print("-E8");
		}, LV_EVENT_CLICKED, NULL);
		Serial.print("-E9");
		
		lv_timer_handler(); // Refresh the LVGL display to reflect the changes
		lv_refr_now(NULL);  // Azonnali frissítés az LVGL-ben
		Serial.println("--F");
		delay(100);
  
	  }
	  Serial.println("WiFi scan completed");
	}
	Serial.println("WiFi scan finished");
	// Hide the "ScanningWifi" panel
	lv_obj_add_flag(ui_panelScanningWifi, LV_OBJ_FLAG_HIDDEN);
	lv_timer_handler(); // Refresh the LVGL display to reflect the changes
	lv_refr_now(NULL);  // Azonnali frissítés az LVGL-ben
}

void funcConnectToWifiButtonPress(lv_event_t * e)
{
	const char *ssid = lv_label_get_text(ui_lblWifiSSIDToBeConnect);
	const char *password = lv_textarea_get_text(ui_textareaWifiPassword);
	lv_obj_clear_flag(ui_panelConnectingToWifi, LV_OBJ_FLAG_HIDDEN);
  
	Serial.printf("Attempting to connect to SSID: %s with password: %s\n", ssid, password);
  
	WiFi.begin(ssid, password);
  
	int max_attempts = 20; // Maximum number of attempts to connect
	int attempt = 0;
  
	while (WiFi.status() != WL_CONNECTED && attempt < max_attempts) {
	  static ulong last_attempt_time = 0;
	  if (millis() - last_attempt_time >= 500) {
		  last_attempt_time = millis();
		  Serial.print(".");
		  attempt++;
  
		  // Update the attempt number on the UI
		  char attempt_text[16];
		  snprintf(attempt_text, sizeof(attempt_text), "%d/20", attempt);
		  lv_label_set_text(ui_lblAttemptNumber, attempt_text);
		  Serial.printf("Attempt %d/20\n", attempt);
		  // Unhide the "ConnectingToWifi" panel
		  
  
		  // Refresh the LVGL display to show the updated attempt number
		  lv_timer_handler();
		  lv_refr_now(NULL);
		  //lv_tick_inc(500); // Simulate the delay time for LVGL
	  }
	}
  
	if (WiFi.status() == WL_CONNECTED) {
	  Serial.println("\nWiFi connected successfully!");
	  lv_obj_clear_flag(ui_panelConnectionSuccess, LV_OBJ_FLAG_HIDDEN);
	  lv_obj_add_flag(ui_panelNotConnected, LV_OBJ_FLAG_HIDDEN);
	  lv_obj_add_flag(ui_panelConnectingToWifi, LV_OBJ_FLAG_HIDDEN);
  
  
  
  
  
  
	} else {
	  Serial.println("\nFailed to connect to WiFi.");
	  lv_obj_clear_flag(ui_panelNotConnected, LV_OBJ_FLAG_HIDDEN);
	  lv_obj_add_flag(ui_panelConnectionSuccess, LV_OBJ_FLAG_HIDDEN);
	  lv_obj_add_flag(ui_panelConnectingToWifi, LV_OBJ_FLAG_HIDDEN);
	}  
}


void funcRetryButtonWrongPassword(lv_event_t * e)
{
	lv_textarea_set_text(ui_textareaWifiPassword, "");
}

void funcSaveMQTTCredentials(lv_event_t * e)
{
	// Get the credentials from the text areas
	const char *mqttServer = lv_textarea_get_text(ui_TextAreaMQTTServer);
	const char *mqttUser = lv_textarea_get_text(ui_TextAreaMQTTuser);
	const char *mqttPassword = lv_textarea_get_text(ui_TextAreaMQTTPassword);

	// Save to global variables
	strncpy(global_mqtt_server, mqttServer, sizeof(global_mqtt_server) - 1);
	strncpy(global_mqtt_user, mqttUser, sizeof(global_mqtt_user) - 1);
	strncpy(global_mqtt_password, mqttPassword, sizeof(global_mqtt_password) - 1);

	// Save to EEPROM
	EEPROM.begin(512); // Initialize EEPROM with a size of 512 bytes
	MQTT_Configured = true; // Indicate that MQTT is configured
	EEPROM.put(0, MQTT_Configured); // Save the configuration flag at the beginning
	EEPROM.put(1, global_mqtt_server); // Save MQTT server starting from offset 1
	EEPROM.put(65, global_mqtt_user); // Save MQTT user starting from offset 65
	EEPROM.put(129, global_mqtt_password); // Save MQTT password starting from offset 129

	EEPROM.commit(); // Commit changes to EEPROM
	EEPROM.end();

	Serial.println("MQTT credentials saved successfully.");
}

void funcForgetMQTTSettings(lv_event_t * e)
{
	// Clear MQTT settings
	memset(global_mqtt_server, 0, sizeof(global_mqtt_server));
	memset(global_mqtt_user, 0, sizeof(global_mqtt_user));
	memset(global_mqtt_password, 0, sizeof(global_mqtt_password));

	// Update MQTT_Configured flag
	MQTT_Configured = false;

	// Clear EEPROM
	EEPROM.begin(512); // Initialize EEPROM with a size of 512 bytes
	EEPROM.put(0, MQTT_Configured); // Save the configuration flag as false
	for (int i = 1; i < 512; i++) {
		EEPROM.write(i, 0); // Clear all other EEPROM data
	}
	EEPROM.commit(); // Commit changes to EEPROM
	EEPROM.end();

	Serial.println("MQTT settings forgotten and EEPROM cleared.");
}

void funcResetMinMaxDistance(lv_event_t * e)
{
	global_minDistance = 0; // Initialize to maximum possible value
	global_maxDistance = 0; // Initialize to minimum possible value 
}

void funcTankTypeChanged(lv_event_t * e)
{
	int selected_idx = lv_dropdown_get_selected(ui_DropdownParamTankType);
	static char selected[32];
	printf("Selected tank type: %d\n", selected_idx);
	//lv_dropdown_get_option(ui_DropdownParamTankType, selected_idx, selected, sizeof(selected));
	if (selected_idx == 0) {//Cilinder
		lv_obj_add_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	} else if (selected_idx == 1) {//Rectangle
		lv_obj_add_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	}
}

void funcParamRectangleWide(lv_event_t * e)
{
	lv_obj_add_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);
}

void funcParamRectangleDepth(lv_event_t * e)
{
	lv_obj_add_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);
}

void funcParamRectangleHeight(lv_event_t * e)
{
	lv_obj_add_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);
}

void funcParamCilinderDiameter(lv_event_t * e)
{
	lv_obj_add_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);
}

void funcParamCilinderHeight(lv_event_t * e)
{
	lv_obj_add_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);
}

void funcParamEmptyTank(lv_event_t * e)
{
	lv_obj_add_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);
}

void funcParamFullTank(lv_event_t * e)
{
	lv_obj_add_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);
}

void funcParamKeyboardOk(lv_event_t * e)
{
	// Your code here
	//ui_ContTankType
	//ui_ContRectangle
	//ui_ContCilinder
	//ui_ContMinMax
	//ui_ContButtons
	//ui_ParamKeyboard
	lv_obj_add_flag(ui_ParamKeyboard, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(ui_ContTankType, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContMinMax, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ContButtons, LV_OBJ_FLAG_HIDDEN);

	int selected_idx = lv_dropdown_get_selected(ui_DropdownParamTankType);
	static char selected[32];
	if (selected_idx == 0) {//Cilinder
		lv_obj_clear_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
	} else if (selected_idx == 1) {//Rectangle
		lv_obj_clear_flag(ui_ContRectangle, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui_ContCilinder, LV_OBJ_FLAG_HIDDEN);
	}
}

void funcParamSave(lv_event_t * e)
{
	// Read values from UI
	uint8_t tankType = lv_dropdown_get_selected(ui_DropdownParamTankType);
	uint16_t rectWide = atoi(lv_textarea_get_text(ui_TextAreaRectangleWide));
	uint16_t rectDepth = atoi(lv_textarea_get_text(ui_TextAreaRectangleDepth));
	uint16_t rectHeight = atoi(lv_textarea_get_text(ui_TextAreaRectangleHeight));
	uint16_t cilDiameter = atoi(lv_textarea_get_text(ui_TextAreaCilinderDiameter));
	uint16_t cilHeight = atoi(lv_textarea_get_text(ui_TextAreaCilinderHeight));
	uint16_t emptyTank = atoi(lv_textarea_get_text(ui_TextAreaEmptyTank));
	uint16_t fullTank = atoi(lv_textarea_get_text(ui_TextAreaFullTank));

	// Save to EEPROM (compatible with MQTT layout: tank params after MQTT block)
	// MQTT block: 0-192 (see: 0=flag, 1-64=server, 65-128=user, 129-192=pass)
	// Tank params start at 193
	const int tankParamBase = 193;
	EEPROM.begin(512); // Use same size as MQTT
	EEPROM.write(tankParamBase + 0, tankType);
	EEPROM.put(tankParamBase + 1, rectWide);
	EEPROM.put(tankParamBase + 3, rectDepth);
	EEPROM.put(tankParamBase + 5, rectHeight);
	EEPROM.put(tankParamBase + 7, cilDiameter);
	EEPROM.put(tankParamBase + 9, cilHeight);
	EEPROM.put(tankParamBase + 11, emptyTank);
	EEPROM.put(tankParamBase + 13, fullTank);
	EEPROM.commit();
	EEPROM.end();

	Serial.println("Tank parameters saved to EEPROM.");
}
