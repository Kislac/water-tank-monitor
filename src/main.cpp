#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include <WiFi.h>
#include <FS.h>     // Include the SPIFFS library for Version handling
#include <SPIFFS.h> // Include the SPIFFS library for Version handling
// put function declarations here:

//Set the screen brightness to 50% initially
#define SCREEN_INITIAL_BRIGHTNESS 50
ulong next_millis;
auto lv_last_tick = millis();
char text_buffer[32];

int64_t now = 0;
String security;

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

  int build_number = versionFile.parseInt();
  Serial.printf("Build_number: %d \n", build_number);
  versionFile.close();

  // Update the ui_VerValue with the code version
  char version[16];
  sprintf(version, "v1.0.%d", build_number);
  lv_label_set_text(ui_lblBuildVersionValue, version);
}


lv_obj_t * wifiDisconnectedImages[4];
lv_obj_t * wifiConnectedImages[4];
lv_obj_t * internetOKImages[4];
lv_obj_t * internetNOKImages[4];
void initWifiSignalImages(){
  wifiDisconnectedImages[0] = ui_imWifiDisconnected1;
  wifiDisconnectedImages[1] = ui_imWifiDisconnected2;
  wifiDisconnectedImages[2] = ui_imWifiDisconnected3;
  wifiDisconnectedImages[3] = ui_imWifiDisconnected4;
  wifiConnectedImages[0] = ui_imWifiConnected1;
  wifiConnectedImages[1] = ui_imWifiConnected2;
  wifiConnectedImages[2] = ui_imWifiConnected3;
  wifiConnectedImages[3] = ui_imWifiConnected4;
  internetOKImages[0] = ui_imInternetOK1;
  internetOKImages[1] = ui_imInternetOK2;
  internetOKImages[2] = ui_imInternetOK3;
  internetOKImages[3] = ui_imInternetOK4;
  internetNOKImages[0] = ui_imInternetNOK1;
  internetNOKImages[1] = ui_imInternetNOK2;
  internetNOKImages[2] = ui_imInternetNOK3;
  internetNOKImages[3] = ui_imInternetNOK4;
}

void funcWifiScan(lv_event_t * e){
  Serial.println("funcWifiScan");
  Serial.println("Starting WiFi scan...");

  lv_obj_clear_flag(ui_panelScanningWifi, LV_OBJ_FLAG_HIDDEN);
  //now = millis();
  //lv_tick_inc(now - lv_last_tick);
  //Serial.printf("now: %lld, lv_last_tick: %lld\n", now, lv_last_tick);
  //lv_last_tick = now;
  lv_timer_handler(); // Refresh the LVGL display to reflect the changes
  lv_refr_now(NULL);  // Azonnali frissítés az LVGL-ben


  lv_obj_clean(ui_PanelWifiList);
  WiFi.scanDelete(); // fontos, ha előzőleg futott
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
    // Create a label to display the number of WiFi networks found
    lv_obj_t *ui_LabelWifiCount = lv_label_create(ui_PanelWifiList);
    lv_label_set_text_fmt(ui_LabelWifiCount, "Found %d networks", n);
    //lv_obj_set_style_text_font(ui_LabelWifiCount, &lv_font_montserrat_12, 0); // Set font size to small
    lv_obj_set_style_text_align(ui_LabelWifiCount, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(ui_LabelWifiCount, LV_ALIGN_TOP_LEFT, 5, 5); // Position the label at the top-left corner

    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
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



      if (ui_PanelWifiList == nullptr) {
          Serial.println("Error: ui_PanelWifiList is not initialized.");
          // Initialize ui_PanelWifiList to avoid null pointer dereference
          ui_PanelWifiList = lv_obj_create(lv_scr_act());
          lv_obj_set_size(ui_PanelWifiList, lv_pct(100), lv_pct(100));
          lv_obj_set_align(ui_PanelWifiList, LV_ALIGN_CENTER);
      }

      // Create a button for each WiFi network
      lv_obj_t *ui_Button_WifiSSID = lv_btn_create(ui_PanelWifiList);
      lv_obj_set_width(ui_Button_WifiSSID, lv_pct(100));
      lv_obj_set_height(ui_Button_WifiSSID, LV_SIZE_CONTENT);
      lv_obj_set_align(ui_Button_WifiSSID, LV_ALIGN_CENTER);
      lv_obj_set_flex_flow(ui_Button_WifiSSID, LV_FLEX_FLOW_ROW);
      lv_obj_set_flex_align(ui_Button_WifiSSID, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

      // Create the first label for SSID
      lv_obj_t *ui_LabelSSID = lv_label_create(ui_Button_WifiSSID);
      lv_obj_set_width(ui_LabelSSID, lv_pct(70));
      lv_obj_set_height(ui_LabelSSID, LV_SIZE_CONTENT);
      lv_obj_set_align(ui_LabelSSID, LV_ALIGN_CENTER);
      lv_label_set_long_mode(ui_LabelSSID, LV_LABEL_LONG_SCROLL);
      lv_obj_set_style_text_align(ui_LabelSSID, LV_TEXT_ALIGN_LEFT, 0);
      lv_label_set_text(ui_LabelSSID, ssid.c_str()); // Set the SSID text dynamically



      // Create the second label for RSSI
      lv_obj_t *ui_LabelRSSI = lv_label_create(ui_Button_WifiSSID);
      lv_obj_set_width(ui_LabelRSSI, lv_pct(30));
      lv_obj_set_height(ui_LabelRSSI, LV_SIZE_CONTENT);
      lv_obj_set_align(ui_LabelRSSI, LV_ALIGN_RIGHT_MID);
      char rssi_text[16];
      snprintf(rssi_text, sizeof(rssi_text), "%d dBm", rssi);
      lv_label_set_text(ui_LabelRSSI, rssi_text);
      


      // Add an event callback to handle button clicks
      lv_obj_add_event_cb(ui_Button_WifiSSID, [](lv_event_t *e) {
        //lv_obj_t *btn = lv_event_get_target(e);
        lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e);
        lv_obj_t *label_ssid = lv_obj_get_child(btn, 0); // Get the first child (SSID label)
        const char *ssid = lv_label_get_text(label_ssid);
        lv_label_set_text(ui_lblWifiSSIDToBeConnect, ssid); // Set the SSID to the target label
        Serial.printf("Selected SSID: %s\n", ssid);
        lv_textarea_set_text(ui_textareaWifiPassword, "");
        // Change screen to "ConnectToWifi"
        lv_scr_load(ui_ConnectToWifi);
      }, LV_EVENT_CLICKED, nullptr);

    }
    Serial.println("WiFi scan completed");
  }
  Serial.println("WiFi scan finished");
  // Hide the "ScanningWifi" panel
  lv_obj_add_flag(ui_panelScanningWifi, LV_OBJ_FLAG_HIDDEN);
}

void ConnectToWifiButtonPress(lv_event_t * e){
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


void RetryButtonWrongPassword(lv_event_t * e){
  lv_textarea_set_text(ui_textareaWifiPassword, "");
}





// Függvény a képek láthatóságának frissítésére
void updateStatusImages(bool wifiConnected, bool internetOK) {
    // WiFi Disconnected képek kezelése

    int wifiDisconnectedImagesCount = sizeof(wifiDisconnectedImages) / sizeof(wifiDisconnectedImages[0]);
    //Serial.printf("wifiDisconnectedImages has %d elements\n", wifiDisconnectedImagesCount);
    for (int i = 0; i < wifiDisconnectedImagesCount; i++) {
      if (wifiDisconnectedImages[i] == nullptr) {
        Serial.printf("wifiDisconnectedImages[%d] is nullptr\n", i);
      } else {
        //lv_obj_t* img = wifiDisconnectedImages[i];
        //if (img != nullptr) { // Ensure the pointer is not null
            if (wifiConnected) {
                lv_obj_add_flag(wifiDisconnectedImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
                lv_obj_clear_flag(wifiConnectedImages[i], LV_OBJ_FLAG_HIDDEN); // Megjelenítés
            } else {
                lv_obj_clear_flag(wifiDisconnectedImages[i], LV_OBJ_FLAG_HIDDEN); // Megjelenítés
                lv_obj_add_flag(wifiConnectedImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
            }
            if (internetOK) {
              lv_obj_add_flag(internetNOKImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
              lv_obj_clear_flag(internetOKImages[i], LV_OBJ_FLAG_HIDDEN); // Megjelenítés
            } else {
                lv_obj_clear_flag(internetNOKImages[i], LV_OBJ_FLAG_HIDDEN); // Megjelenítés
                lv_obj_add_flag(internetOKImages[i], LV_OBJ_FLAG_HIDDEN); // Elrejtés
            }
      }
    }

}


// Hívás a státusz frissítésére
void refreshStatus() {
    static ulong last_status_refresh_time = 0;

    if (millis() - last_status_refresh_time >= 1000) { // Refresh every second
      last_status_refresh_time = millis();

      bool wifiConnected = (WiFi.status() == WL_CONNECTED);
      bool internetOK = false;

      // Internet kapcsolat ellenőrzése
      WiFiClient client;
      if (wifiConnected && client.connect("www.google.com", 80)) {
        internetOK = true;
        client.stop();
      }

      // Frissítsd a képeket
      updateStatusImages(wifiConnected, internetOK);
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

      // Refresh Date and Time
      configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // Configure NTP servers
      struct tm timeinfo;
      if (getLocalTime(&timeinfo)) {
        char datetime_text[32];
        strftime(datetime_text, sizeof(datetime_text), "%Y.%m.%d %H:%M:%S", &timeinfo);
        lv_label_set_text(ui_lblTime, datetime_text);
        lv_label_set_text(ui_lblTime1, datetime_text);
      } else {
        lv_label_set_text(ui_lblTime, "Time Unavailable");
        lv_label_set_text(ui_lblTime1, "Time Unavailable");
      }
      // Determine timezone based on IP address
      // Fetch time and timezone without external libraries
      
        } else {
      // Clear labels if not connected
      lv_label_set_text(ui_lblWifiSSID, "N/A");
      lv_label_set_text(ui_lblWifiIP, "N/A");
      lv_label_set_text(ui_lblWifiRSSI, "N/A");
      lv_label_set_text(ui_lblWifiChannel, "N/A");
      lv_label_set_text(ui_lblWifiSecurity, "N/A");
      lv_label_set_text(ui_lblTimeZone, "N/A");
      lv_label_set_text(ui_lblTime, "N/A");
    }
  }
}


void funcResetWifi(lv_event_t * e){
  WiFi.disconnect(true); // Disconnect and erase WiFi credentials
  WiFi.mode(WIFI_OFF);   // Turn off WiFi to reset the state
  delay(100);            // Small delay to ensure the reset takes effect
  WiFi.mode(WIFI_STA);   // Set WiFi mode back to station mode
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
s
void AutoBacklight(){
  #ifdef BOARD_HAS_CDS
  static ulong last_AutoBacklight = 0;

  if (millis() - last_AutoBacklight >= 100) { // Refresh every 100ms
    last_AutoBacklight = millis();
        auto cdr = analogReadMilliVolts(CDS);
        sprintf(text_buffer, "%d", cdr);
        if (lv_tabview_get_tab_act(ui_TabView2) == 3) {
            lv_label_set_text(ui_lblLigthSensorValue, text_buffer);
        }
        
        if (lv_obj_get_state(ui_switchManualAutomatic) & LV_STATE_CHECKED) {
            float adaptive_brightness = smartdisplay_lcd_adaptive_brightness_cds();
            smartdisplay_lcd_set_backlight(adaptive_brightness);
            if (lv_tabview_get_tab_act(ui_TabView2) == 3) {
              int slider_value = (int)(adaptive_brightness * 100);
              lv_slider_set_value(ui_LigthSensorSlider, slider_value, LV_ANIM_OFF);
              sprintf(text_buffer, "%d%%", slider_value);
              lv_label_set_text(ui_lblLigthSensorSliderValue, text_buffer);
            }
        }
  }
  #endif
}

void funcRotateScreen(lv_event_t * e){
  static bool rotated = false;
  rotated = !rotated; // Toggle rotation state
  lv_disp_set_rotation(lv_disp_get_default(), rotated ? LV_DISPLAY_ROTATION_180 : LV_DISPLAY_ROTATION_0);
  Serial.printf("Screen rotated to %s\n", rotated ? "180°" : "0°");
}


void setup() {
  Serial.begin(115200);

  


  smartdisplay_init();

  __attribute__((unused)) auto disp = lv_disp_get_default();
   lv_disp_set_rotation(disp, LV_DISPLAY_ROTATION_90);
  // lv_disp_set_rotation(disp, LV_DISP_ROT_180);
  // lv_disp_set_rotation(disp, LV_DISP_ROT_270);
  ui_init();

  Serial.println("Starting the program...");

  // Set the screen brightness to 50% initially
  smartdisplay_lcd_set_backlight(max(((float)(SCREEN_INITIAL_BRIGHTNESS) / 100), 0.01f));
  // Update the ui_LigthSensorSlider to reflect the 50% brightness
  lv_slider_set_value(ui_LigthSensorSlider, SCREEN_INITIAL_BRIGHTNESS, LV_ANIM_OFF);
  sprintf(text_buffer, "%d%%", SCREEN_INITIAL_BRIGHTNESS);
  lv_label_set_text(ui_lblLigthSensorSliderValue, text_buffer);

  // Set the switch to manual mode initially
  lv_obj_add_state(ui_switchManualAutomatic, LV_STATE_DEFAULT);
  funcManualAutomatic(nullptr);    // Call the funcManualAutomatic function after setting the switch


  //wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  // Init the Wifi Signal images. Important to init after ui_init()
  initWifiSignalImages();


  initializeBuildInfo();

}

void loop() {
  // put your main code here, to run repeatedly:
    now = millis();
    runtimecalc();
    AutoBacklight();
    RefreshWifiParameters();
    refreshStatus();
      // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;
    // Update the UI
    lv_timer_handler();
}

