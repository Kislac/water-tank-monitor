// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: WaterTank

#ifndef _WATERTANK_UI_H
#define _WATERTANK_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"
#include "ui_theme_manager.h"
#include "ui_themes.h"

// SCREEN: ui_Main_Screen
void ui_Main_Screen_screen_init(void);
extern lv_obj_t * ui_Main_Screen;
extern lv_obj_t * ui_TopInfoBar1;
extern lv_obj_t * ui_Spinner2;
extern lv_obj_t * ui_imWifiInternetOK1;
extern lv_obj_t * ui_imWifiDisconnected1;
extern lv_obj_t * ui_imWifiConnectedNoInternet1;
extern lv_obj_t * ui_lblDataNTime;
extern lv_obj_t * ui_MainTabView;
extern lv_obj_t * ui_Main;
extern lv_obj_t * ui_BarCurrentState;
extern lv_obj_t * ui_lblMaxValue;
extern lv_obj_t * ui_lblMinValue;
extern lv_obj_t * ui_lblMax;
extern lv_obj_t * ui_lblMin;
extern lv_obj_t * ui_lblCurrentLiter;
extern lv_obj_t * ui_THPanel;
extern lv_obj_t * ui_lblTempValue;
extern lv_obj_t * ui_lblHumValue;
extern lv_obj_t * ui_Chart2;
extern lv_obj_t * ui_Chart2_Xaxis;
extern lv_obj_t * ui_Chart2_Yaxis1;
extern lv_obj_t * ui_Chart2_Yaxis2;
extern lv_obj_t * ui_lblH;
extern lv_obj_t * ui_ChartActualDistance;
extern lv_obj_t * ui_ChartActualDistance_Xaxis;
extern lv_obj_t * ui_ChartActualDistance_Yaxis1;
extern lv_obj_t * ui_ChartActualDistance_Yaxis2;
extern lv_obj_t * ui_Statistic;
extern lv_obj_t * ui_Container5;
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui_lblActualDistance;
extern lv_obj_t * ui_lblActualDistanceValue;
extern lv_obj_t * ui_lblMinDistance;
extern lv_obj_t * ui_lblMinDistanceValue;
extern lv_obj_t * ui_lblMaxDistance;
extern lv_obj_t * ui_lblMaxDistanceValue;
extern lv_obj_t * ui_lblDistance;
void ui_event_Button1(lv_event_t * e);
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Label31;
extern lv_obj_t * ui_Param;
extern lv_obj_t * ui_ContTankType;
extern lv_obj_t * ui_Label32;
void ui_event_DropdownParamTankType(lv_event_t * e);
extern lv_obj_t * ui_DropdownParamTankType;
extern lv_obj_t * ui_ContRectangle;
extern lv_obj_t * ui_lblWide;
extern lv_obj_t * ui_lblDepth;
extern lv_obj_t * ui_lblHeight;
extern lv_obj_t * ui_Label35;
void ui_event_TextAreaRectangleWide(lv_event_t * e);
extern lv_obj_t * ui_TextAreaRectangleWide;
void ui_event_TextAreaRectangleDepth(lv_event_t * e);
extern lv_obj_t * ui_TextAreaRectangleDepth;
void ui_event_TextAreaRectangleHeight(lv_event_t * e);
extern lv_obj_t * ui_TextAreaRectangleHeight;
extern lv_obj_t * ui_ContCilinder;
extern lv_obj_t * ui_lblDiameter;
extern lv_obj_t * ui_lblHeight1;
extern lv_obj_t * ui_Label33;
void ui_event_TextAreaCilinderDiameter(lv_event_t * e);
extern lv_obj_t * ui_TextAreaCilinderDiameter;
void ui_event_TextAreaCilinderHeight(lv_event_t * e);
extern lv_obj_t * ui_TextAreaCilinderHeight;
extern lv_obj_t * ui_ContMinMax;
extern lv_obj_t * ui_lblDiameter1;
extern lv_obj_t * ui_lblHeight2;
extern lv_obj_t * ui_Label34;
void ui_event_TextAreaEmptyTank(lv_event_t * e);
extern lv_obj_t * ui_TextAreaEmptyTank;
void ui_event_TextAreaFullTank(lv_event_t * e);
extern lv_obj_t * ui_TextAreaFullTank;
extern lv_obj_t * ui_ContButtons;
extern lv_obj_t * ui_Button2;
extern lv_obj_t * ui_Label36;
void ui_event_Button3(lv_event_t * e);
extern lv_obj_t * ui_Button3;
extern lv_obj_t * ui_Label37;
void ui_event_ParamKeyboard(lv_event_t * e);
extern lv_obj_t * ui_ParamKeyboard;
extern lv_obj_t * ui_Settings;
extern lv_obj_t * ui_Container2;
extern lv_obj_t * ui_lblWifiSwitch;
void ui_event_btnWifi(lv_event_t * e);
extern lv_obj_t * ui_btnWifi;
extern lv_obj_t * ui_Label5;
void ui_event_btnMQTT(lv_event_t * e);
extern lv_obj_t * ui_btnMQTT;
extern lv_obj_t * ui_Label30;
extern lv_obj_t * ui_ContDarkMode;
extern lv_obj_t * ui_lblDarkMode;
void ui_event_Switch2(lv_event_t * e);
extern lv_obj_t * ui_Switch2;
extern lv_obj_t * ui_ContBackLigth;
extern lv_obj_t * ui_lblBackLight;
extern lv_obj_t * ui_switchManualAutomatic;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_lblLigthSensorValue;
void ui_event_LigthSensorSlider(lv_event_t * e);
extern lv_obj_t * ui_LigthSensorSlider;
extern lv_obj_t * ui_lblLigthSensorSliderValue;
extern lv_obj_t * ui_ContLanguage;
extern lv_obj_t * ui_lblLanguage;
extern lv_obj_t * ui_DropdownLanguage;
extern lv_obj_t * ui_ContRotateScreen;
extern lv_obj_t * ui_lblrotate;
void ui_event_btnRotate(lv_event_t * e);
extern lv_obj_t * ui_btnRotate;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui_ContSWReset;
extern lv_obj_t * ui_lblrotate1;
void ui_event_btnReset(lv_event_t * e);
extern lv_obj_t * ui_btnReset;
extern lv_obj_t * ui_Label29;
extern lv_obj_t * ui_About;
extern lv_obj_t * ui_ConBuildDate;
extern lv_obj_t * ui_lblBuildDate;
extern lv_obj_t * ui_lblBuildDateValue;
extern lv_obj_t * ui_ConBuildVersion;
extern lv_obj_t * ui_lblBuildVersion;
extern lv_obj_t * ui_lblBuildVersionValue;
extern lv_obj_t * ui_ConRunTime;
extern lv_obj_t * ui_lblRunTime;
extern lv_obj_t * ui_lblRunTimeValue;
extern lv_obj_t * ui_ConGitHub;
extern lv_obj_t * ui_lblGit;
extern lv_obj_t * ui_lblGitHub;
extern lv_obj_t * ui_ConAuth;
extern lv_obj_t * ui_lblGit1;
extern lv_obj_t * ui_lblGitHub1;
// SCREEN: ui_Wifi_Settings
void ui_Wifi_Settings_screen_init(void);
extern lv_obj_t * ui_Wifi_Settings;
extern lv_obj_t * ui_TopInfoBar2;
extern lv_obj_t * ui_Spinner4;
extern lv_obj_t * ui_Container3;
extern lv_obj_t * ui_Container9;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_lblWifiStatus;
extern lv_obj_t * ui_Container10;
extern lv_obj_t * ui_Label15;
extern lv_obj_t * ui_lblWifiSSID;
extern lv_obj_t * ui_Container11;
extern lv_obj_t * ui_Label17;
extern lv_obj_t * ui_lblWifiIP;
extern lv_obj_t * ui_Container12;
extern lv_obj_t * ui_Label20;
extern lv_obj_t * ui_lblWifiRSSI;
extern lv_obj_t * ui_Container13;
extern lv_obj_t * ui_Label22;
extern lv_obj_t * ui_lblWifiChannel;
extern lv_obj_t * ui_Container14;
extern lv_obj_t * ui_Label24;
extern lv_obj_t * ui_lblWifiSecurity;
extern lv_obj_t * ui_Container16;
extern lv_obj_t * ui_Label27;
extern lv_obj_t * ui_lblTime;
extern lv_obj_t * ui_lblTimeZone;
void ui_event_btnScanWifi(lv_event_t * e);
extern lv_obj_t * ui_btnScanWifi;
extern lv_obj_t * ui_Label11;
extern lv_obj_t * ui_Container15;
extern lv_obj_t * ui_Label14;
void ui_event_btnForgetWifi(lv_event_t * e);
extern lv_obj_t * ui_btnForgetWifi;
extern lv_obj_t * ui_Label25;
void ui_event_btnBack(lv_event_t * e);
extern lv_obj_t * ui_btnBack;
extern lv_obj_t * ui_Label28;
// SCREEN: ui_WifiScanResult
void ui_WifiScanResult_screen_init(void);
extern lv_obj_t * ui_WifiScanResult;
extern lv_obj_t * ui_TopInfoBar5;
extern lv_obj_t * ui_Spinner6;
extern lv_obj_t * ui_Container1;
extern lv_obj_t * ui_Label1;
void ui_event_funcWifiScan(lv_event_t * e);
extern lv_obj_t * ui_funcWifiScan;
extern lv_obj_t * ui_Label2;
void ui_event_btnback(lv_event_t * e);
extern lv_obj_t * ui_btnback;
extern lv_obj_t * ui_Label19;
extern lv_obj_t * ui_PanelWifiList;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_panelScanningWifi;
extern lv_obj_t * ui_Label26;
// SCREEN: ui_ConnectToWifi
void ui_ConnectToWifi_screen_init(void);
extern lv_obj_t * ui_ConnectToWifi;
extern lv_obj_t * ui_TopInfoBar3;
extern lv_obj_t * ui_Spinner3;
void ui_event_Keyboard1(lv_event_t * e);
extern lv_obj_t * ui_Keyboard1;
extern lv_obj_t * ui_Container4;
extern lv_obj_t * ui_Label8;
extern lv_obj_t * ui_lblWifiSSIDToBeConnect;
extern lv_obj_t * ui_Container6;
extern lv_obj_t * ui_Label10;
extern lv_obj_t * ui_textareaWifiPassword;
extern lv_obj_t * ui_Container7;
void ui_event_Button4(lv_event_t * e);
extern lv_obj_t * ui_Button4;
extern lv_obj_t * ui_Label12;
void ui_event_Button5(lv_event_t * e);
extern lv_obj_t * ui_Button5;
extern lv_obj_t * ui_Label13;
extern lv_obj_t * ui_panelConnectionSuccess;
extern lv_obj_t * ui_Label16;
void ui_event_Button6(lv_event_t * e);
extern lv_obj_t * ui_Button6;
extern lv_obj_t * ui_Label18;
extern lv_obj_t * ui_panelNotConnected;
extern lv_obj_t * ui_Label21;
void ui_event_Button7(lv_event_t * e);
extern lv_obj_t * ui_Button7;
extern lv_obj_t * ui_Label23;
extern lv_obj_t * ui_panelConnectingToWifi;
extern lv_obj_t * ui_Label9;
extern lv_obj_t * ui_lblAttemptNumber;
// SCREEN: ui_MQTTSettings
void ui_MQTTSettings_screen_init(void);
extern lv_obj_t * ui_MQTTSettings;
extern lv_obj_t * ui_TopInfoBar;
extern lv_obj_t * ui_Spinner1;
extern lv_obj_t * ui_ContMQTTServer;
extern lv_obj_t * ui_lblMQTTlbl;
void ui_event_TextAreaMQTTServer(lv_event_t * e);
extern lv_obj_t * ui_TextAreaMQTTServer;
extern lv_obj_t * ui_ContMQTTUser;
extern lv_obj_t * ui_lblMQTTuser;
void ui_event_TextAreaMQTTuser(lv_event_t * e);
extern lv_obj_t * ui_TextAreaMQTTuser;
extern lv_obj_t * ui_ContMQTTPassword;
extern lv_obj_t * ui_lblMQTTPassword;
void ui_event_TextAreaMQTTPassword(lv_event_t * e);
extern lv_obj_t * ui_TextAreaMQTTPassword;
void ui_event_Back(lv_event_t * e);
extern lv_obj_t * ui_Back;
extern lv_obj_t * ui_lblBack;
void ui_event_Save(lv_event_t * e);
extern lv_obj_t * ui_Save;
extern lv_obj_t * ui_lblBack1;
void ui_event_Forget(lv_event_t * e);
extern lv_obj_t * ui_Forget;
extern lv_obj_t * ui_lblBack2;
void ui_event_KeyboardMQTT(lv_event_t * e);
extern lv_obj_t * ui_KeyboardMQTT;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_wifiinternetok_png);    // assets/WifiInternetOK.png
LV_IMG_DECLARE(ui_img_wifidisconnected_png);    // assets/WifiDisconnected.png
LV_IMG_DECLARE(ui_img_wificonnectednointernet_png);    // assets/WifiConnectedNoInternet.png



LV_FONT_DECLARE(ui_font_DejaVuSansMono14);
LV_FONT_DECLARE(ui_font_MontserratRegular14ExtASCI);
LV_FONT_DECLARE(ui_font_MontserratRegular14ExtASCIBold);
LV_FONT_DECLARE(ui_font_MontserratRegular14ExtASCIMedium);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
