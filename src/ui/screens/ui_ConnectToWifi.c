// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: WaterTank

#include "../ui.h"

void ui_ConnectToWifi_screen_init(void)
{
    ui_ConnectToWifi = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_ConnectToWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TopInfoBar3 = lv_obj_create(ui_ConnectToWifi);
    lv_obj_remove_style_all(ui_TopInfoBar3);
    lv_obj_set_width(ui_TopInfoBar3, 318);
    lv_obj_set_height(ui_TopInfoBar3, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_TopInfoBar3, 1);
    lv_obj_set_y(ui_TopInfoBar3, 1);
    lv_obj_remove_flag(ui_TopInfoBar3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_TopInfoBar3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TopInfoBar3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TopInfoBar3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Spinner3 = lv_spinner_create(ui_TopInfoBar3);
    //lv_spinner_set_anim_params(ui_Spinner3, 1000, 90);
    lv_obj_set_width(ui_Spinner3, 20);
    lv_obj_set_height(ui_Spinner3, 20);
    lv_obj_set_align(ui_Spinner3, LV_ALIGN_RIGHT_MID);
    lv_obj_remove_flag(ui_Spinner3, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(ui_Spinner3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_Spinner3, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_Keyboard1 = lv_keyboard_create(ui_ConnectToWifi);
    lv_obj_set_height(ui_Keyboard1, 120);
    lv_obj_set_width(ui_Keyboard1, lv_pct(100));
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_BOTTOM_MID);

    ui_Container4 = lv_obj_create(ui_ConnectToWifi);
    lv_obj_remove_style_all(ui_Container4);
    lv_obj_set_width(ui_Container4, 318);
    lv_obj_set_height(ui_Container4, 30);
    lv_obj_set_x(ui_Container4, 0);
    lv_obj_set_y(ui_Container4, 21);
    lv_obj_set_align(ui_Container4, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_Container4, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_Container4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Container4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Container4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_Container4);
    lv_obj_set_width(ui_Label8, lv_pct(30));
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label8, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Label8, "Connect to:");

    ui_lblWifiSSIDToBeConnect = lv_label_create(ui_Container4);
    lv_obj_set_width(ui_lblWifiSSIDToBeConnect, lv_pct(70));
    lv_obj_set_height(ui_lblWifiSSIDToBeConnect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblWifiSSIDToBeConnect, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblWifiSSIDToBeConnect, "Wifi SSD Name HERE");
    lv_obj_set_style_text_align(ui_lblWifiSSIDToBeConnect, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container6 = lv_obj_create(ui_ConnectToWifi);
    lv_obj_remove_style_all(ui_Container6);
    lv_obj_set_width(ui_Container6, 318);
    lv_obj_set_height(ui_Container6, 36);
    lv_obj_set_x(ui_Container6, 0);
    lv_obj_set_y(ui_Container6, 50);
    lv_obj_set_align(ui_Container6, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_Container6, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_Container6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Container6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Container6, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label10 = lv_label_create(ui_Container6);
    lv_obj_set_width(ui_Label10, lv_pct(30));
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label10, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Label10, "Password:");

    ui_textareaWifiPassword = lv_textarea_create(ui_Container6);
    lv_obj_set_width(ui_textareaWifiPassword, lv_pct(70));
    lv_obj_set_height(ui_textareaWifiPassword, LV_SIZE_CONTENT);    /// 30
    lv_obj_set_align(ui_textareaWifiPassword, LV_ALIGN_RIGHT_MID);
    lv_textarea_set_max_length(ui_textareaWifiPassword, 128);
    lv_textarea_set_placeholder_text(ui_textareaWifiPassword, "Wifi SSD Password HERE");
    lv_obj_set_style_border_color(ui_textareaWifiPassword, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_textareaWifiPassword, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_textareaWifiPassword, 0, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_Container7 = lv_obj_create(ui_ConnectToWifi);
    lv_obj_remove_style_all(ui_Container7);
    lv_obj_set_width(ui_Container7, 318);
    lv_obj_set_height(ui_Container7, 36);
    lv_obj_set_x(ui_Container7, 0);
    lv_obj_set_y(ui_Container7, 85);
    lv_obj_set_align(ui_Container7, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_Container7, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_Container7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Container7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Container7, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button4 = lv_button_create(ui_Container7);
    lv_obj_set_width(ui_Button4, 100);
    lv_obj_set_height(ui_Button4, 30);
    lv_obj_set_x(ui_Button4, 30);
    lv_obj_set_y(ui_Button4, 0);
    lv_obj_set_align(ui_Button4, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_Button4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Button4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label12 = lv_label_create(ui_Button4);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "Connect");

    ui_Button5 = lv_button_create(ui_Container7);
    lv_obj_set_width(ui_Button5, 100);
    lv_obj_set_height(ui_Button5, 30);
    lv_obj_set_x(ui_Button5, -30);
    lv_obj_set_y(ui_Button5, 0);
    lv_obj_set_align(ui_Button5, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label13 = lv_label_create(ui_Button5);
    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label13, "Back");

    ui_panelConnectionSuccess = lv_obj_create(ui_ConnectToWifi);
    lv_obj_set_width(ui_panelConnectionSuccess, 282);
    lv_obj_set_height(ui_panelConnectionSuccess, 92);
    lv_obj_set_align(ui_panelConnectionSuccess, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_panelConnectionSuccess, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_panelConnectionSuccess, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label16 = lv_label_create(ui_panelConnectionSuccess);
    lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label16, 3);
    lv_obj_set_y(ui_Label16, -16);
    lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label16, "Connected to Wifi Successfully!");

    ui_Button6 = lv_button_create(ui_panelConnectionSuccess);
    lv_obj_set_width(ui_Button6, 100);
    lv_obj_set_height(ui_Button6, 27);
    lv_obj_set_x(ui_Button6, 0);
    lv_obj_set_y(ui_Button6, 19);
    lv_obj_set_align(ui_Button6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Button6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label18 = lv_label_create(ui_Button6);
    lv_obj_set_width(ui_Label18, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label18, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label18, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label18, "Ok");

    ui_panelNotConnected = lv_obj_create(ui_ConnectToWifi);
    lv_obj_set_width(ui_panelNotConnected, 282);
    lv_obj_set_height(ui_panelNotConnected, 92);
    lv_obj_set_align(ui_panelNotConnected, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_panelNotConnected, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_panelNotConnected, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label21 = lv_label_create(ui_panelNotConnected);
    lv_obj_set_width(ui_Label21, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label21, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label21, 3);
    lv_obj_set_y(ui_Label21, -16);
    lv_obj_set_align(ui_Label21, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label21, "Not able to connect\nWrong password");
    lv_obj_set_style_text_align(ui_Label21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button7 = lv_button_create(ui_panelNotConnected);
    lv_obj_set_width(ui_Button7, 100);
    lv_obj_set_height(ui_Button7, 27);
    lv_obj_set_x(ui_Button7, 0);
    lv_obj_set_y(ui_Button7, 19);
    lv_obj_set_align(ui_Button7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button7, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Button7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label23 = lv_label_create(ui_Button7);
    lv_obj_set_width(ui_Label23, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label23, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label23, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label23, "Retry");

    ui_panelConnectingToWifi = lv_obj_create(ui_ConnectToWifi);
    lv_obj_set_width(ui_panelConnectingToWifi, 282);
    lv_obj_set_height(ui_panelConnectingToWifi, 92);
    lv_obj_set_align(ui_panelConnectingToWifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_panelConnectingToWifi, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_panelConnectingToWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label9 = lv_label_create(ui_panelConnectingToWifi);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label9, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Label9, "Connecting to Wifi:");
    lv_obj_set_style_text_align(ui_Label9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblAttemptNumber = lv_label_create(ui_panelConnectingToWifi);
    lv_obj_set_width(ui_lblAttemptNumber, lv_pct(40));
    lv_obj_set_height(ui_lblAttemptNumber, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblAttemptNumber, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblAttemptNumber, "20/20");
    lv_obj_set_style_text_align(ui_lblAttemptNumber, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Keyboard1, ui_event_Keyboard1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button4, ui_event_Button4, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button5, ui_event_Button5, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button6, ui_event_Button6, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button7, ui_event_Button7, LV_EVENT_ALL, NULL);

}
